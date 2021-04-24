#include "country.h"
#include <stdio.h>
#include<individual.h>

/**
 * @brief Create a country on the map 
 * @param x,y,z,w vertix of the country
 * @return country 
 */
Country addCountry(Point x,Point y,Point z,Point w,int name)
{
    Country country;

    country.x=x;
    country.y=y;
    country.w=w;
    country.z=z;
    country.name=name;
    IndividualNode *node;
    node->individual=NULL;
    node->next=NULL;
    country.individuals=node;
    return country;
}

void addIndividual(IndividualNode *individuals,Individual *individual){

IndividualNode *newIndividual=(IndividualNode*)malloc(sizeof(IndividualNode));
if(newIndividual==NULL){
    printf("Unable to allocate memory for the new node");
    return;
}


newIndividual->individual=individual;
newIndividual->next=NULL;


if(individuals->individual == NULL){
        individuals->individual = newIndividual;
        individuals->next=NULL;
    }
    else
    {
        IndividualNode *current = individuals;
        while(current->next != NULL)
        {
        current = current->next;
        }
      
        current->next = newIndividual;
               
            
    }


    
}

void removeIndividual(IndividualNode *individuals,Individual *individual){

     IndividualNode *cur=individuals;

     if(individuals==NULL||individuals->individual==NULL)
        return;
   

    if(individuals->individual==individual)
        {
            if (individuals->next!=NULL){
                individuals->individual=individuals->next;
                return ;
            }
            else{
                individuals->individual=NULL;
                return;
            }

        }
else if(individuals->individual!=individual && individuals->next == NULL) {
      return;
}
    IndividualNode *current;
    IndividualNode *prev;
    IndividualNode *hop;
    current= individuals;
   
   while(current->next != NULL && (current->individual!=individual)) {
      prev = current;
      current = current->next;
   }        

   if(current->individual==individual) {
       hop=prev->next;
      prev->next = hop->next;
      free(current);
   } 
     

}
