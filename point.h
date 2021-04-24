#ifndef POINT
#define POINT

#include <stdio.h>


typedef struct 
{
    unsigned int x;
    unsigned int y;
    
} Point;



Point buildPoint(int x,int y);


#endif