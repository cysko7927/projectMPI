#include "country.h"
#include "world.h"
#include <stdio.h>

/**
 * @brief Create the map of the world
 * @param x base of the map
 * @param y height of the map
 * @return map
 */
World createWorld(int x,int y,Country countries[])
{
    World world;

    world.x=x;
    world.y=y;
    strcpy(world.countries,countries); 

    return world;
}


