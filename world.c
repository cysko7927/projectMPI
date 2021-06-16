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
    struct Point w,struct Country *countries,int numOfCountries,struct World *world)
{
    

    world->x=x;
    world->y=y;
    world->z=z;
    world->w=w;
    world->countries=countries;

   
    world->numOfCountries=numOfCountries;

    
}

struct Country *getCountries(struct World world){
    return world.countries;
}

void printWorld(struct World world){
    
   printf(
       "\n world coordinates : x=( %d,%d)  y=(%d,%d) w=(%d,%d) z=(%d,%d)",
            world.x.x,world.x.y,world.y.x,world.y.y,world.w.x,world.w.y,world.z.x,world.z.y
   );
    
}

void printCountries(struct World world){

    for(int i=0; i<world.numOfCountries;i++){
       printf(
       "\n country #%d coordinates : x=( %d,%d)  y=(%d,%d) w=(%d,%d) z=(%d,%d)\n",getCountries(world)[i].name,
            getCountries(world)[i].x.x,getCountries(world)[i].x.y,getCountries(world)[i].y.x,
            getCountries(world)[i].y.y, getCountries(world)[i].w.x,
            getCountries(world)[i].w.y,getCountries(world)[i].z.x,getCountries(world)[i].z.y
   );
    }
}

void statistics(struct World world){
    int maxi=world.numOfCountries;
    for(int i=0;i<maxi;i++){

        countryStatistics(world.countries[i]);
    }
}



