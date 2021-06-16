#ifndef DISTANCE_CALCULATION
#define DISTANCE_CALCULATION
#include <stdio.h>
#include "individual.h"
#include <mpi.h>


struct Distance 
{
    unsigned int x;
    unsigned int y;
    unsigned int key;
    double distance;
};

void calculateDistance(struct Individual allIndividual[],struct Distance allDistance[],unsigned int nTotalIndividual,unsigned int keyIndividual);
unsigned int checkIfNearInfected(struct Distance *distances,struct IndividualNode *allIndividuals,int minDistance,int indexIndividual);
MPI_Datatype defineDistanceForMPI();
#endif