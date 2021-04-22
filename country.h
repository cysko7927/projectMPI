#ifndef COUNTRY
#define COUNTRY

#include <stdio.h>


typedef struct 
{
    unsigned int x;
    unsigned int y;
    char name[10];
    
} Country;



Country addCountry(int x,int y,char name[10]);


#endif