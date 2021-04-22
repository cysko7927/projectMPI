#ifndef MOVEMENT
#define MOVEMENT

#include <stdio.h>


typedef enum 
{
    UP,DOWN,LEFT,RIGHT,DIAGONAL
} Direction;

typedef struct 
{
    unsigned int v;
    Direction direction;
} Movement;


void updateDirection(Movement * movement);
void updateVelocity(Movement * movement);



#endif