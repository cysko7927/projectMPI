#include <stdio.h>
#include <string.h>
#include "individual.h"


/**
 * @brief Create a Healthy Individual located in a point of the rectangle 
 * 
 * @param x base in the rectangle
 * @param y height in the rectangle
 * @return Individual created
 */
struct Individual createHealthyIndividual(int x,int y,int key)
{
    struct Individual individual;

    individual.point.x = x;
    individual.point.y = y;
    individual.counter = 0;
    individual.state = healthy;
    individual.hasAlreadyMoved=0;
    individual.key=key;
    

    return individual;
}

/**
 * @brief Create an Infected Individual located in a point of the rectangle 
 * 
 * @param x base in the rectangle
 * @param y height in the rectangle
 * @return Individual created
 */
struct Individual createInfectedIndividual(int x,int y,int key)
{
    struct Individual individual;

    individual.point.x = x;
    individual.point.y = y;
    individual.counter = 0;
    individual.state = infected;
    individual.hasAlreadyMoved=0;
    individual.key=key;
    

    return individual;
}

/**
 * @brief update the state of an individual based on its internal state 
 * and the number of its infected neighbors
 * 
 * @param neighborsInfected number of the infected close to the individual 
 * @param individual pointer to the individual with the state to update
 */
void updateState(unsigned int neighborsInfected, struct Individual * individual, int time)
{
    switch (individual->state)
    {
    case healthy:
        if (neighborsInfected == 0 ) //if there are no infected neighbors
        {
            individual->counter = 0;
        }else
        {
            individual->counter+=time;
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
            individual->counter+=time;
        }
        
        break;

    case infected:

        if (individual ->counter < secondsInADay*10) //if it's not been 10 days
        {
            individual->counter+=time;
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
                individual->counter+=time;
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
void setCoordinates(struct Individual *individual, int x,int y)
{
    individual->point.x = x;
    individual->point.y = y;
}
/**
 * Remove the individual from his country and move him in a new country
 * updating the data structure inside the individual and the structs of the countries
 * 
 * @param individual individual that moves in an other country
 * @param newCountry country in which the individual is moved
 */
void updateCountry(struct Individual *individual, struct Country *newCountry, struct Country *oldaCountry)
{
      struct Country *oldCountry;
     oldCountry=individual->country;
   
    printf("\n================================================\n");
    printf("\nIndividual: %d changes country",individual->key);
    printf("\nfrom country : %d",oldCountry->name);
    printf("\nto:\n country : %d",newCountry->name);
    printf("\n================================================\n");
  

    individual->country=newCountry;
   
   
    struct IndividualNode *individualNode;
    struct IndividualNode *head;
    struct IndividualNode *cur;
    struct IndividualNode *prec;
    struct IndividualNode *source;
    struct IndividualNode *dest;

     

    //if the oldCountry has no individual -> go back
    if(oldCountry->individuals==NULL||oldCountry->individuals->individual==NULL)
        return;
  
    //the first individual of the country change country
   if(oldCountry->individuals->individual->key==individual->key){

        cur=oldCountry->individuals;

        oldCountry->individuals=cur->next;

        //Add the individualNode in the list inside the new country
        addIndividualNode(newCountry,cur);
        
        return;
    }

    cur=oldCountry->individuals;

    //look for the IndividualNode corrisponding to the individual
    while(cur->next!=NULL&&cur->next->individual!=NULL&&cur->next->individual->key!=individual->key){
            cur=cur->next;
    }
    
    //if not found
    if(cur->next==NULL||cur->next->individual==NULL)
        return;

    //corresponding IndividualNode
    individualNode=cur->next;
    cur->next=individualNode->next;

    //Add the individual in the list inside the new country
    addIndividualNode(newCountry,individualNode); 


}



void printIndividual(struct Individual *individual){
    char status[21];
       
           if(individual->state==infected)
            strcpy(status,"infected");
           else if(individual->state==healthy) 
            strcpy(status,"healthy");
           else if(individual->state==immune) 
            strcpy(status,"immune");
           else if(individual->state==infectionsInProgress) 
            strcpy(status,"infectionsInProgress");
           else strcpy(status,"error");
           
       

   
       printf("\n================================================\n"); 
       printf("\nINDIVIDUAL INFO");
       printf("\nID: %d\ncountry: %d\n(x,y)=(%d,%d)\nstatus:%s\nspeed:%d",individual->key,individual->country->name,individual->point.x,individual->point.y,status,individual->movement.v);
       printf("\n================================================\n"); 
       
       
    
  


}
/**
 * Set the field hasAlreadyMoved to zero in order to allow the individual to move once again
 * @param individual individual that has to be allowed to move again
 */
void resetTheMovement(struct Individual *individual){
    individual->hasAlreadyMoved=0;
}

