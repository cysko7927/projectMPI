#include "region.h"
#include <stdio.h>

/**
 * @brief Create a region on the map 
 * @param x base of the region
 * @param y height of the region
 * @return Region 
 */
Region addRegion(int x,int y,char name[10])
{
    Region region;

    region.x=x;
    region.y=y;
    strcpy(region.name,name); 
    return region;
}


