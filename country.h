#ifndef COUNTRY
#define COUNTRY

#include <stdio.h>
#include <point.h>
#include <individual.h>


typedef struct 
{

    /*
        y--------z
        |        |
        x--------w
    */

    Point x;
    Point y;
    Point z;
    Point w;               

    int name;

    IndividualNode *individuals;
    
} Country;

typedef struct {
    Individual *individual;
    IndividualNode *next;

}IndividualNode;


Country addCountry(Point x,Point y,Point z,Point w,int name);

void addIndividual(IndividualNode *individuals,Individual *individual);

void removeIndividual(IndividualNode *individuals,Individual *individual);

#endif