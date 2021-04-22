#ifndef COUNTRY
#define COUNTRY

#include <stdio.h>


typedef struct 
{
    unsigned int x;
    unsigned int y;
    char name;
    
} Country;



Country addCountry(int x,int y,char name);


#endif