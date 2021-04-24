#include "country.h"
#include "world.h"
#include <stdio.h>

/**
 * @brief Create the map of the world
 * @param x,y,z,w vertix of the map
 * @param countries contains all the countries that have to be added to the world
 * @return map
 */
World createWorld(Point x,Point y,Point z,Point w,Country *countries)
{
    World world;

    world.x=x;
    world.y=y;
    world.z=z;
    world.w=w;
    world.countries=countries;

    return world;
}


