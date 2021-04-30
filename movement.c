#include "movement.h"



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
}

