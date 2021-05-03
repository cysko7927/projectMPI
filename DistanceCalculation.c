#include <stdio.h>
#include "individual.h"
#include "DistanceCalculation.h"
#include <math.h>


void calculateDistances(Individual allIndividual[],Distance allDistance[],unsigned int nTotalIndividual,unsigned int keyIndividual)
{

    MPI_Init(NULL, NULL);
    int my_rank, world_size; 
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    unsigned int elements_per_proc = nTotalIndividual/(world_size);

    unsigned int xFirstPoint = allIndividual[keyIndividual].point.x;
    unsigned int yFirstPoint = allIndividual[keyIndividual].point.y;


    MPI_Datatype mpi_distance = MPdefineDistanceForMPI();

    Distance * distanceGlobal = NULL;
    if (my_rank == 0) //Create the array that will contain the distance and the data to send to the thread
    {
        distanceGlobal = malloc(sizeof(Distance)*(nTotalIndividual-1));

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
    
    
    Distance * localDistances = malloc(sizeof(Distance)*elements_per_proc);

    MPI_Scatter(distanceGlobal, elements_per_proc,mpi_distance, localDistances,elements_per_proc,mpi_distance,0,MPI_COMM_WORLD);
    
    for (size_t i = 0; i < elements_per_proc; i++)
    {
        unsigned int xSecondPoint = localDistances[i].x;
        unsigned int ySecondPoint = localDistances[i].y;
        double distanceSquare = (double) (xSecondPoint -xFirstPoint)*(xSecondPoint-xFirstPoint) + (ySecondPoint - yFirstPoint)*(ySecondPoint-yFirstPoint);
        localDistances[i].distance = sqrt(distanceSquare);
    }

    MPI_Gather(localDistances,elements_per_proc, mpi_distance, distanceGlobal, elements_per_proc,mpi_distance,0,MPI_COMM_WORLD);  
        
    if (my_rank == 0)
    {
        if (nTotalIndividual%(world_size) != 0) //if there are some points with distance not calculate
        {
            //Calculate the residual distance for the other points

            unsigned int rest = nTotalIndividual%(world_size);

            for (size_t i = 0; i < rest; i++)
            {
                unsigned int xSecondPoint = distanceGlobal[rest -1 -i].x;
                unsigned int ySecondPoint = distanceGlobal[rest -1 -i].y;
                double distanceSquare = (double) (xSecondPoint -xFirstPoint)*(xSecondPoint-xFirstPoint) + (ySecondPoint - yFirstPoint)*(ySecondPoint-yFirstPoint);
                distanceGlobal[rest-1 - i].distance = sqrt(distanceSquare);
            }
            
        }
        
    }
        

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    

    
}


MPI_Datatype defineDistanceForMPI()
{
    Distance distance;
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
    // Add one Unsigned
    block_lens[3] = 1;
    types[3] = MPI_UNSIGNED;
    displacements[3] = (size_t) &(distance.distance) - (size_t) &distance;
    // Create and commit the data structure
    MPI_Type_create_struct(struct_len, block_lens, displacements, types, &mpi_distance);
    MPI_Type_commit(&mpi_distance);

    return mpi_distance;
}