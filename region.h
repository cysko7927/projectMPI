#ifndef REGION
#define REGION

#include <stdio.h>


typedef struct 
{
    unsigned int x;
    unsigned int y;
    char name[10];
    
} Region;



Region addRegion(int x,int y,char name[10]);


#endif