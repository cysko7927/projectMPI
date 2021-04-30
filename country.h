#ifndef COUNTRY
#define COUNTRY

#include <stdio.h>
#include "point.h"
#include "individual.h"


struct Country
{
    /*
        y--------z
        |        |
        x--------w
    */
    struct Point x;
    struct Point y;
    struct Point z;
    struct Point w;               
    int name;
    struct IndividualNode *individuals;
    
} ;

 struct IndividualNode{
    struct Individual *individual;
    struct IndividualNode *next;

};


struct Country addCountry(struct Point x,struct Point y,struct Point z,struct Point w,int name);

void addIndividual(struct IndividualNode *individuals,struct Individual *individual);

void removeIndividual(struct IndividualNode *individuals,struct Individual *individual);

#endif