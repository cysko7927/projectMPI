#include <stdio.h>
#include "country.h"
#include "world.h"


/**
 * @brief Create the map of the world
 * @param x,y,z,w vertix of the map
 * @param countries contains all the countries that have to be added to the world
 * @return map
 */
void createWorld(struct Point x,struct Point y,struct Point z,
    struct Point w,struct Country *countries,int numOfCountries,struct World world)
{
    

    world.x=x;
    world.y=y;
    world.z=z;
    world.w=w;
    world.countries=countries;
    world.numOfCountries=numOfCountries;

    
}

struct Country *getCountries(struct World world){
    return world.countries;
}

void printWorld(struct World world){
   printf(

       "world coordinates :\n x=( %d,%d) , y=(%d,%d), w=(%d,%d), z=(%d,%d)",
            &world.x.x,&world.x.y,&world.y.x,&world.y.y,&world.w.x,&world.w.y,&world.z.x,&world.z.y
   );
    
}
