#ifndef MOVEMENT
#define MOVEMENT

#include <stdio.h>


typedef enum 
{
    UP,DOWN,LEFT,RIGHT,UPLEFT,UPRIGHT,DOWNLEFT,DOWNRIGHT,STOP
} Direction;

 struct Movement 
{
     int v;
     Direction direction;
} ;


void updateDirection(struct Movement * movement,Direction dir);
void updateVelocity(struct Movement * movement,int v);
struct Movement setInitialMovement(int speed);



#endif