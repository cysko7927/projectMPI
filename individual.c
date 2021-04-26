#include "individual.h"
#include <stdio.h>

/**
 * @brief Create a Healthy Individual located in a point of the rectangle 
 * 
 * @param x base in the rectangle
 * @param y height in the rectangle
 * @return Individual created
 */
Individual createHealthyIndividual(int x,int y)
{
    Individual individual;

    individual.point.x = x;
    individual.point.y = y;
    individual.counter = 0;
    individual.state = healthy;
    

    return individual;
}

/**
 * @brief update the state of an individual based on its internal state 
 * and the number of its infected neighbors
 * 
 * @param neighborsInfected number of the infected close to the individual 
 * @param individual pointer to the individual with the state to update
 */
void updateState(unsigned int neighborsInfected, Individual * individual)
{
    switch (individual->state)
    {
    case healthy:
        if (neighborsInfected == 0 ) //if there are no infected neighbors
        {
            individual->counter = 0;
        }else
        {
            individual->counter++;
            individual->state = infectionsInProgress; //Start the infection in the individual
        }
        break;

    case infectionsInProgress:

        if (individual->counter >= secondsInAMinute * 10 && neighborsInfected > 0) //if there are infected neighbors and 10 minutes have passed
        {
            individual->counter = 0;
            individual->state = infected; //The individual becomes infected
        }
        else if(neighborsInfected == 0) //Else if there are no more infected neighbors the individual become healthy
        {
            individual->counter = 0;
            individual->state = healthy;
        }
        else// If there are infected neighbors and it's not been 10 minutes
        {
            individual->counter++;
        }
        
        break;

    case infected:

        if (individual ->counter < secondsInADay*10) //if it's not been 10 days
        {
            individual->counter++;
        }
        else //Else if 10 days have passed
        {
            individual->counter = 0;
            individual->state = immune; //the individual becomes immune
        }
        
        break;

        case immune:

            if (individual ->counter < secondsInAMonth*3)//if it's not been 3 months
            {
                individual->counter++;
            }
            else //Else if 3 months have passed
            {
                individual->counter = 0;
                individual->state = healthy;
            }
            break;        
    
    default:
        break;
    }
}

/**
 * @brief Change the location of an individual in the rectangle
 * 
 * @param individual pointer to the individual to move
 * @param x base in the rectangle
 * @param y height in the rectangle
 */
void setCoordinates(Individual *individual, int x,int y)
{
    individual->point.x = x;
    individual->point.y = y;
}
/**
 * Remove the individual from his country and move him in a new country
 * updating the data structure inside the individual and the structs of the countries
 * 
 * @param individual individual to move in an other country
 * @param newCountry country where the individual is moved
 */
void updateCountry(Individual *individual, Country *newCountry)
{
    removeIndividual(individual->country->individuals,individual); // remove the individual from the list inside the old country
    individual->country = newCountry;//Update the reference to the country inside the individual

    addIndividual(newCountry->individuals,individual); //Add the individual in the list inside the new country


}
