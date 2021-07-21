#include <stdio.h>
#include "individual.h"
#include "DistanceCalculation.h"
#include <stdlib.h>
#include "country.h"
#include <math.h>

/**
 * @brief calculate the distance between an individual and all the others
 * @param allIndividual list of individuals
 * @param allDistance distance of the individual from allIndividual
 * @param nTotalIndividual number of individual to check
 * @param keyIndividual index of the individual of which the method find the distance from allIndividual 
 */

void calculateDistance(struct Individual allIndividual[],struct Distance allDistance[],unsigned int nTotalIndividual,unsigned int keyIndividual)
{
    
    int my_rank, world_size; 
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    unsigned int elements_per_proc = (nTotalIndividual-1)/(world_size);

    long int xFirstPoint = (long int) allIndividual[keyIndividual].point.x;
    long int yFirstPoint = (long int) allIndividual[keyIndividual].point.y;

    /*for (size_t i = 0; i < nTotalIndividual; i++)
    {
        printf("Process:%u x= %u,y = %u\n", my_rank, allIndividual[i].point.x, allIndividual[i].point.y);
    }*/


    MPI_Datatype mpi_distance = defineDistanceForMPI();

    struct Distance * distanceGlobal = NULL;
    if (my_rank == 0) //Create the array that will contain the distance and the data to send to the thread
    {
        distanceGlobal = malloc(sizeof(struct Distance)*(nTotalIndividual-1));

        int i = 0;
        int j = 0;

        while(j < nTotalIndividual-1)
        {
            if (i != keyIndividual)
            {
                distanceGlobal[j].x = allIndividual[i].point.x;
                distanceGlobal[j].y = allIndividual[i].point.y;
                distanceGlobal[j].key = i;
                distanceGlobal[j].distance = 0;
                j++;
            }
            i++;
        }
    }
    
    
    struct Distance * localDistances = malloc(sizeof(struct Distance)*elements_per_proc);

    MPI_Scatter(distanceGlobal, elements_per_proc,mpi_distance, localDistances,elements_per_proc,mpi_distance,0,MPI_COMM_WORLD);
    
    for (size_t i = 0; i < elements_per_proc; i++)
    {
        long int xSecondPoint = (long int) localDistances[i].x;
        long int ySecondPoint = (long int) localDistances[i].y;
        double distanceSquare = (double) (xSecondPoint -xFirstPoint)*(xSecondPoint-xFirstPoint) + (ySecondPoint - yFirstPoint)*(ySecondPoint-yFirstPoint);
        localDistances[i].distance = sqrt(distanceSquare);


        printf("Process:%d x= %ld,y = %ld i = %u\n", my_rank, xSecondPoint, ySecondPoint,i);
        
    }

    /*for (size_t i = 0; i < elements_per_proc; i++)
    {
        printf("Process:%u x= %u,y = %u ,dist= %lf\n", my_rank, localDistances[i].x, localDistances[i].y,localDistances[i].distance);
    }*/
    

    MPI_Gather(localDistances,elements_per_proc, mpi_distance, distanceGlobal, elements_per_proc,mpi_distance,0,MPI_COMM_WORLD);  

    MPI_Barrier(MPI_COMM_WORLD);    
    if (my_rank == 0)
    {   
        unsigned int rest = nTotalIndividual -1 - elements_per_proc*world_size;

        if (rest != 0) //if there are some points with distance not calculate
        {
            //Calculate the residual distance for the other points

            printf("Process: rest = %u\n", rest);

            for (size_t i = 0; i < rest; i++)
            {
                long int xSecondPoint = distanceGlobal[nTotalIndividual-2 -i].x;
                long int ySecondPoint = distanceGlobal[nTotalIndividual-2 -i].y;
                double distanceSquare = (double) (xSecondPoint -xFirstPoint)*(xSecondPoint-xFirstPoint) + (ySecondPoint - yFirstPoint)*(ySecondPoint-yFirstPoint);
                distanceGlobal[nTotalIndividual-2 -i].distance = sqrt(distanceSquare);
                printf("Process:%d x= %ld,y = %ld ,dist= %lf\n", my_rank, xSecondPoint, ySecondPoint,distanceGlobal[nTotalIndividual-2 -i].distance);
            }
            
        }

        for (size_t i = 0; i < nTotalIndividual -1; i++)
        {
            allDistance[i].key = distanceGlobal[i].key;
            allDistance[i].x = distanceGlobal[i].x;
            allDistance[i].y = distanceGlobal[i].y;
            allDistance[i].distance = distanceGlobal[i].distance;
        }

        free(distanceGlobal);
        
    }

    free(localDistances);
    
}


MPI_Datatype defineDistanceForMPI()
{
    struct Distance distance;
    MPI_Datatype mpi_distance;
    int struct_len = 4;
    int block_lens[struct_len];
    MPI_Datatype types[struct_len];
    // We need to compute the displacement to be really portable
    // (different compilers might align structures differently)
    MPI_Aint displacements[struct_len];
    MPI_Aint current_displacement = 0;
    // Add one unsigned
    block_lens[0] = 1;
    types[0] = MPI_UNSIGNED;
    displacements[0] = (size_t) &(distance.x) - (size_t) &distance;
    // Add one Unsigned
    block_lens[1] = 1;
    types[1] = MPI_UNSIGNED;
    displacements[1] = (size_t) &(distance.y) - (size_t) &distance;
    // Add one Unsigned
    block_lens[2] = 1;
    types[2] = MPI_UNSIGNED;
    displacements[2] = (size_t) &(distance.key) - (size_t) &distance;
    // Add one Double
    block_lens[3] = 1;
    types[3] = MPI_DOUBLE;
    displacements[3] = (size_t) &(distance.distance) - (size_t) &distance;
    // Create and commit the data structure
    MPI_Type_create_struct(struct_len, block_lens, displacements, types, &mpi_distance);
    MPI_Type_commit(&mpi_distance);

    return mpi_distance;
}

/**
 * @brief check if the individual is near an infected individual
 * @param allIndividual list of individuals
 * @param distance distance of the individual from allIndividual
 * @param minDistance distance to keep in order to not being infected by an infected individual
 * @param indexIndividual index of the individual to be considered
 * @return 1 if near an infected 0 otherwise
 */

int checkIfNearInfected(struct Distance *distances,struct IndividualNode *allIndividuals,int minDistance,int indexIndividual){
    int i=0;
    struct IndividualNode *cur=allIndividuals;

        //scan all the individuals
    while(cur!=NULL&&cur->individual!=NULL){
        //--if the counter is equal to indexIndividual then we have to skip the confront
            //we can't compare the indidividual with itself
        if(indexIndividual!=i){
            //compare distances 
            if(distances[i].distance<=minDistance&&cur->individual->state==infected){
            //then the individual is near an infected and we can stop here
                return 1;
                }
        }
            //update di i
            i=i++;
            //update di cur
           cur=cur->next;
        
    }
    //the individual isn't near to any infected individual
    return 0;
}