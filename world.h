#ifndef WORLD
#define WORLD

#include <stdio.h>
#include <country.h>
#include <point.h>

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
    Country  *countries;
    
} World;



World createWorld(Point x,Point y,Point z,Point w,Country *countries);


#endif