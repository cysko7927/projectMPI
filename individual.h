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
    int hasAlreadyMoved; //=0 if the individual has not moved in the turn
    int key;
} ;


void updateState(unsigned int neighbors,  struct Individual * individual);

void updateCountry(struct Individual *individual, struct Country *newCountry);//todo fare implementazione

struct Individual createHealthyIndividual(int x,int y,int key);
struct Individual createInfectedIndividual(int x,int y,int key);

void setCoordinates(struct Individual *individual,int x,int y);
void printIndividual(struct Individual *individual);
void resetTheMovement(struct Individual *individual);










#endif