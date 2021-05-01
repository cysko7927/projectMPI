#ifndef INDIVIDUAL
#define INDIVIDUAL

#include <stdio.h>
#include "movement.h"
#include "country.h"
#include "point.h"

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

 struct Individual
{
    struct Point point;
    unsigned int counter;
    StateIndividual state;
    struct Movement movement;
    struct Country *country;
} ;


void updateState(unsigned int neighbors,  struct Individual * individual);

void updateCountry(struct Individual *individual, struct Country *newCountry);//todo fare implementazione

struct Individual createHealthyIndividual(int x,int y);
struct Individual createInfectedIndividual(int x,int y);

void setCoordinates(struct Individual *individual,int x,int y);
void printIndividual(struct Individual *individual);





#endif