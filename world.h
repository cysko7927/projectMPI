#ifndef WORLD
#define WORLD

#include <stdio.h>
#include <country.h>


typedef struct 
{
    unsigned int x;
    unsigned int y;
    Country  countries[];
    
} World;



World createWorld(int x,int y,Country *countries);


#endif