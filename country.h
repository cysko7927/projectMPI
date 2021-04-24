#ifndef COUNTRY
#define COUNTRY

#include <stdio.h>
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

    char name;
    
} Country;



Country addCountry(Point x,Point y,Point z,Point w,char name[]);


#endif