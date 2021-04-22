#include "country.h"
#include <stdio.h>

/**
 * @brief Create a country on the map 
 * @param x base of the country
 * @param y height of the country
 * @return country 
 */
Country addCountry(int x,int y,char name[10])
{
    Country country;

    country.x=x;
    country.y=y;
    strcpy(country.name,name); 
    return country;
}


