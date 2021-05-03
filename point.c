

#include <stdio.h>
#include "point.h"

/**
 * @brief Create a point
 * @param x,y point coordinates
 * @return Point
 */
struct Point buildPoint(int x,int y){
    struct Point p;
    p.x=x;
    p.y=y;
    return p;
}