#include "movement.h"
#include "individual.h"


/**
 * @brief Update the direction of the individual
 * @param movement movement that have to change its direction
 * @param dir the desired direction
 */

void updateDirection(struct Movement * movement, Direction dir)
{ 
    
    movement->direction=dir;}


/**
 * @brief Update the velocity of the individual
 * @param movement movement that have to change its velocity
 * @param dir the desired velocity
 */
void updateVelocity(struct Movement * movement,  int v)
{ movement->v=v;}

/**
 * @brief Initially all the individuals don't move
 * @param speed speed of the movement
 */
struct Movement setInitialMovement(int speed){
    struct Movement movement;
    movement.direction=STOP;
    movement.v=speed;
    return movement;
}


void printDirection(Direction dir){
    switch (dir)
    {
    case STOP:printf("\ndirection: STOP");
        return;
    case UP:printf("\ndirection: UP");
        return;
    case DOWN:printf("\ndirection: DOWN");
        return;
    case LEFT:printf("\ndirection: LEFT");
        return;
    case RIGHT:printf("\ndirection: RIGHT");
        return;
    case UPLEFT:printf("\ndirection: UPLEFT");
        return;
    case UPRIGHT:printf("\ndirection: UPRIGHT");
        return;
    case DOWNLEFT:printf("\ndirection: DOWNLEFT");
        return;
    case DOWNRIGHT:printf("\ndirection: DOWNRIGHT");
        return;
    default:
        break;
    }
    
    printf("\nassigned direction: %d" , (int) dir);
}


