#include <stdio.h>
#include <stdlib.h>
#include "country.h"
#include "individual.h"

/**
 * @brief Create a country on the map 
 * @param x @param y @param z @param w vertix of the country
 * @param name name assigned to the contry in order to be identificable
 * @param country the country pointer that it's used in order to build the Country
 */
void addCountry(struct Point x,struct Point y,struct Point z,struct Point w,int name,struct Country *country)
{
   // struct Country country;

    country->x=x;
    country->y=y;
    country->w=w;
    country->z=z;
    country->name=name;
    struct IndividualNode *node=malloc(sizeof(struct IndividualNode));
    node->individual=NULL;
    node->next=NULL;
    country->individuals=node;
    
}


/**
 * @brief Add a new individual to an individuals list, if the list doesn't exists then it builds one   
 * @param individuals list of individuals
 * @param individual individual that needs to be added to the individuals list 
 */
void addIndividual(struct IndividualNode *individuals,struct Individual *individual){

struct IndividualNode *newIndividual=(struct IndividualNode*)malloc(sizeof(struct IndividualNode));
if(newIndividual==NULL){
    printf("Unable to allocate memory for the new node");
    return;
}


newIndividual->individual=individual;
newIndividual->next=NULL;

if(individuals==NULL){
    individuals=malloc(sizeof(struct IndividualNode));
    individuals->individual=individual;
    individuals->next=NULL;
    return;
}


else if(individuals->individual == NULL){
    
        individuals->individual=individual;
        individuals->next=NULL;
         return;
    }
    
else
    {
       
        struct IndividualNode *current;
        current=individuals;
        while(current->next != NULL)
            current = current->next;
        
        current->next=newIndividual;
         return;
               
    }
  
}
/**
 * @brief Add an existing individual to the country individuals list, if the list doesn't exists then it builds one   
 * @param individuals list of individuals
 * @param individual individual node that needs to be added to the individuals list 
 */
void addIndividualNode(struct Country *newCountry,struct IndividualNode *individual){

if(individual==NULL){
    printf("Invalid IndividualNode");
    return;
}

struct IndividualNode *old;
old=newCountry->individuals;
newCountry->individuals=individual;
individual->next=old;



}

/**
 * @brief remove an individual from an individuals list
 * @param individuals list of individuals
 * @param individual individual that needs to removed from the individuals list 
 */

struct IndividualNode* removeIndividual(struct Country *country,struct Individual *individual){
    struct IndividualNode *individualNode;
        
        if(country->individuals->individual->key==individual->key){
            individualNode=country->individuals;
            country->individuals=(country->individuals)->next;    
            return individualNode;
        }
       
     
  

  }
     



/**
 * @brief method used for end-day statistics
 * @param individuals list of individuals
 */

void printIndividuals(struct IndividualNode *individuals){
    struct IndividualNode *ind=individuals; 

     while(ind!=NULL&&ind->individual!=NULL)
        {
            printIndividual(ind->individual);
           
            ind=ind->next;
        }


}

/**
 * @brief method used for end-day statistics reguarding country sick/healthy/nsusceptible collected intel
 * @param country the country that has the info that the program is going to print at end-day statistics
 */

void countryStatistics(struct Country *country){

    int healthyCount=0;
    int suceptibleCount=0;
    int immuneCount=0;
    int infectedCount=0;

    struct IndividualNode *individuals=country->individuals;
    if(individuals==NULL||individuals->individual==NULL)
        return;
    printf("\n---------------------------------------------------------STAMPO PAESE # %d",country->name);
    printIndividuals(individuals);

    while (individuals!=NULL&&individuals->individual!=NULL)
    {
        switch (individuals->individual->state)
        {
        case healthy:healthyCount++;
            break;
        case immune:immuneCount++;
            break;
        case infectionsInProgress:suceptibleCount++;
            break;
        case infected: infectedCount++;
            break;
        default:
            break;
        }

        individuals=individuals->next;
    }

    printf("\n---------COUNTRY #%d ----------------\n\nhealthy individuals: %d\ninfected individuals: %d\nsusceptible individuals: %d\nimmune individuals: %d\n-------------------------------------\n"
        ,country->name,healthyCount,infectedCount,suceptibleCount,immuneCount);
    
}