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


void addCountry(struct Point x,struct Point y,struct Point z,struct Point w,int name,struct Country *country);

void addIndividual(struct IndividualNode *individuals,struct Individual *individual);
void addIndividualNode(struct Country *newCountry,struct IndividualNode *individual);

struct IndividualNode * removeIndividual(struct Country *country,struct Individual *individual);

void printIndividuals(struct IndividualNode *individuals);
void countryStatistics(struct Country country);

#endif