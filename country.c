#include <stdio.h>
#include "country.h"
#include "individual.h"

/**
 * @brief Create a country on the map 
 * @param x,y,z,w vertix of the country
 * @return country 
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

void addIndividual(struct IndividualNode *individuals,struct Individual *individual){

struct IndividualNode *newIndividual=(struct IndividualNode*)malloc(sizeof(struct IndividualNode));
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
        struct IndividualNode *current = individuals;
        while(current->next != NULL)
        {
        current = current->next;
        }
      
        current->next = newIndividual;
               
            
    }


    
}

void removeIndividual(struct IndividualNode *individuals,struct Individual *individual){

     struct IndividualNode *cur=individuals;

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
    struct IndividualNode *current;
    struct IndividualNode *prev;
    struct IndividualNode *hop;
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

void printIndividuals(struct IndividualNode *individuals){
    if(individuals==NULL||individuals->individual==NULL)
        {
            printf("no individual");
            return;
        }

       printf("\nstate: %d\nx: %d\ny: %d\n#: %d\n",(int) individuals->individual->state,
       individuals->individual->point.x,
       individuals->individual->point.y,
       individuals->individual->country->name);
    
    while(individuals->next!=NULL){
    printf("\nstate: %d\nx: %d\ny: %d\n#: %d\n",(int) individuals->next->individual->state,
       individuals->next->individual->point.x,
       individuals->next->individual->point.y,
       individuals->next->individual->country->name);

       individuals->next=individuals->next->next;
    }


}