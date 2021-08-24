#ifndef WORLD
#define WORLD

#include <stdio.h>
#include "country.h"
#include "point.h"

 struct World
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
    struct Country  *countries;
    int numOfCountries;
    
} ;



void createWorld(struct Point x,struct Point y,struct Point z,
struct Point w,struct Country *countries,int numOfCountries,struct World *world);
struct Country *getCountries(struct World world);
void printWorld(struct World world);
void printCountries(struct World world);


    

#endif