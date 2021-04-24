#ifndef INDIVIDUAL
#define INDIVIDUAL

#include <stdio.h>
#include "movement.h"
#include "country.h"

#define secondsInAMinute 60
#define secondsInADay 86400
#define secondsInAMonth secondsInADay*30

typedef enum 
{
    healthy,
    infectionsInProgress,
    infected,
    immune
} StateIndividual;

typedef struct 
{
    unsigned int x;
    unsigned int y;
    unsigned int counter;
    StateIndividual state;
    Movement movement;
    Country *country;
} Individual;


void updateState(unsigned int neighbors, Individual * individual);

void updateCountry(Individual *individual, Country *newCountry);

Individual createHealthyIndividual(int x,int y);

void setCoordinates(Individual *individual,int x,int y);





#endif