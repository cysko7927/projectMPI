#include "movement.h"



/**
 * @brief Update the direction of the individual
 * @param movement movement that have to change its direction
 * @param dir the desired direction
 */

void updateDirection(Movement * movement, Direction dir)
{ movement->direction=dir;}


/**
 * @brief Update the velocity of the individual
 * @param movement movement that have to change its velocity
 * @param dir the desired velocity
 */
void updateVelocity(Movement * movement, unsigned int v)
{ movement->v=v;}

