#include "country.h"
#include <stdio.h>

/**
 * @brief Create a country on the map 
 * @param x,y,z,w vertix of the country
 * @return country 
 */
Country addCountry(Point x,Point y,Point z,Point w,char name[])
{
    Country country;

    country.x=x;
    country.y=y;
    country.w=w;
    country.z=z;
    strcpy(country.name,name); 
    return country;
}


