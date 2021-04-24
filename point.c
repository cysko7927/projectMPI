
#include "point.h"
#include <stdio.h>


/**
 * @brief Create a point
 * @param x,y point coordinates
 * @return Point
 */
Point buildPoint(int x,int y){
    Point p;
    p.x=x;
    p.y=y;
    return p;
}