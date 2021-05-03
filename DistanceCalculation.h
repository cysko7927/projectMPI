#ifndef DISTANCE_CALCULATION
#define DISTANCE_CALCULATION
#include <stdio.h>
#include "individual.h"

typedef struct 
{
    unsigned int x;
    unsigned int y;
    unsigned int key;
    double distance;
} Distance;

void calculateDistance(Individual allIndividual[],Distance allDistance[],unsigned int nTotalIndividual,unsigned int keyIndividual);
#endif