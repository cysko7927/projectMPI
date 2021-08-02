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
    StateIndividual state;
    double distance;
};

void calculateDistance(struct Individual *allIndividual[],struct Distance allDistance[],unsigned int nTotalIndividual,unsigned int keyIndividual);
int checkIfNearInfected(struct Distance *distances,int minDistance,int nTotalIndividual);
MPI_Datatype defineDistanceForMPI();
#endif