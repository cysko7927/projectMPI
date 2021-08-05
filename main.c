#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "world.h"
#include "country.h"
#include "DistanceCalculation.h"
/*
    WARNINGS   

    1) PROBLEMA: richiesta se passare al giorno successivo compare solo dopo che si ha mandato una risposta!

    2) la remove a volte provoca un seg fault
        ---> caso 1 della remove da rifare --> 
    
    
*/
                          


int main(int argc, char const *argv[])
{
    MPI_Init(&argc, &argv);//mpi enviroment starts
    int my_rank, world_size;
    int numOfProc=1; 
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD,&world_size);

            //0 N of individuals
            //1 N of infected individuals
            //2 height of the world
            //3 width of the world 
            //4 height of the countries
            //5 widht of the countries
            //6 speed
            //7 max distance
            // t


    //-----------------------------------------------  check on the parameters --------------------------------------//
    int isparametersCorrects = 1;//Assume that the parameters are correct

    

    if(argc!=10){   
        if (my_rank == 0){printf("Please insert the required parameters");}
        return 0;
        }

    
    int numOfIndividuals= atoi(argv[1]);
    
    int numOfInfectedIndividuals= atoi(argv[2]);
    int worldHeight=atoi(argv[3]);
    int worldWidht=atoi(argv[4]);
    int countryHeight=atoi(argv[5]);
    int countryWidht=atoi(argv[6]);
    int speed=atoi(argv[7]);
    int minDistance=atoi(argv[8]);
    int time=atoi(argv[9]);
    
   


    if(numOfIndividuals<0||
        numOfInfectedIndividuals<0||
        worldHeight<0||
        worldWidht<0||
        countryHeight<0||
        countryWidht<0||
        speed<0||
        minDistance<0||
        time<0
        ){
        if (my_rank == 0){printf("All the values must be non negative");}
        return 0;
    }
    if(numOfIndividuals<2){
        if (my_rank == 0){printf("the system must have at least 2 individuals");}
        return 0;
    }

    if(numOfInfectedIndividuals<1){
        if (my_rank == 0){printf("the system must have at least 1 infected individual");}
        return 0;
    }

    if(worldHeight==0){
        if (my_rank == 0){printf("the world's height has to be at least 1");}
        return 0;
    }

    if(worldWidht==0){
        if (my_rank == 0){printf("the world's width has to be at least 1");}
        return 0;
    }

    if(countryHeight==0){
        if (my_rank == 0){printf("the countries' height has to be at least 1");}
        return 0;
    }

    if(countryWidht==0){
        if (my_rank == 0){printf("the countries' width has to be at least 1");}
        return 0;
    }

    if(time==0){
        if (my_rank == 0){printf("please add an time interval greater than 0");}
        return 0;
    }


    if(worldHeight<countryHeight){
        if (my_rank == 0){printf("the height of the countries cannot be higher than the world's height");}
        return 0;
    }
    if(worldWidht<countryWidht){
        if (my_rank == 0){printf("the width of the countries cannot be longer than the world's width");}
        return 0;
    }
    float rest= (worldHeight*worldWidht) % (countryWidht*countryHeight);

    if(rest!=0){
        if (my_rank == 0){printf("the area of the world have to be divisible by the area of the countries");}
        return 0;
    }

    if(worldHeight%countryHeight!=0){
        if (my_rank == 0){printf("the height of the wolrd has to been divisible by the height of the countries");}
        return 0;
    }

    if(worldWidht%countryWidht!=0){
        if (my_rank == 0){printf("the widht of the wolrd has to been divisible by the widht of the countries");}
        return 0;
    }

     int numOfCountries= (worldHeight*worldWidht) / (countryWidht*countryHeight);
    //---------------------------------------------------------------------------------------------------//




    //------------------------------------------creation of the world------------------------------------//        
  struct World world;
  
  buildWorld(&world,worldWidht,worldHeight,numOfCountries,countryWidht,countryHeight);

  if (my_rank == 0){printWorld(world);} 
  if (my_rank == 0){printCountries(world);} 
 
    //--------- add individuals to the world

 addIndividuals(&world, numOfIndividuals,  numOfInfectedIndividuals,speed);

  for(int i=0; i<world.numOfCountries;i++){

      struct Country country=getCountries(world)[i];
      if (my_rank == 0){printIndividuals(country.individuals);}

  }

  struct IndividualNode *individuals; 

  for(int i=0;i<numOfCountries;i++){
      individuals=world.countries[i].individuals;
      //for each individual of each contry do the movement and then print the individual and the directions
      while(individuals!=NULL&&individuals->individual!=NULL) {
       if(individuals->individual->hasAlreadyMoved==0){
         doMovement(individuals->individual,world,time);
     //     if (my_rank == 0){printIndividual(individuals->individual);}
     //     if (my_rank == 0){printDirection(individuals->individual->movement.direction);}
    }
        individuals=individuals->next;
     }
     
  }


 int elapsedSeconds=0;
 
 struct Individual **allIndividuals = malloc((numOfIndividuals)*sizeof(struct Individual*));
 struct Distance *distances=malloc((numOfIndividuals-1)*sizeof(struct Distance)); //Le distanze sono sempre N-1 perché va escluso sempre il primo punto che si prende per calcolare le distanze
 unsigned int bool=0;

 MPI_Barrier(MPI_COMM_WORLD);
 int j = 0;

struct IndividualNode *individuals2; 


    //
        //save all the individuals into a list


       
 
    printf("Inizio creazione array individui\n");
    for(int i=0;i<numOfCountries;i++){
        individuals2=world.countries[i].individuals;
        while(individuals2!=NULL&&individuals2->individual!=NULL)
        {
            printIndividual(individuals2->individual);
            allIndividuals[j] = individuals2->individual;
            j++;
            individuals2=individuals2->next;
        }
    }

    printf("Fine creazione array individui\n");





    //-------------------each process manages part of all the individuals

    int answer;
    int exit = 0;
 
  //dummy method for time management //TODO

    struct IndividualNode *cur; 
    
    while (exit==0)
    {
        int step = 1;
        int stepTotal = secondsInADay/time;
        elapsedSeconds=0;

     while (elapsedSeconds<secondsInADay)
      {
        if(my_rank == 0){printf("Step in a day: %d / %d\n",step,stepTotal);}
      

        for(int i=0;i<numOfIndividuals;i++){
            allIndividuals[i]->hasAlreadyMoved=0;
        //here we've to reset all the movements
        }

         for(int i=0;i<numOfIndividuals;i++){
 //the two  cycles can't be unified otherwise when an individual changes country it could move another time in the same turn
      
            if( allIndividuals[i]->hasAlreadyMoved==0)
                doMovement( allIndividuals[i],world,time);
                
         
    }

      for(int i=0;i<numOfIndividuals;i++)
        {
          
           calculateDistance(allIndividuals,distances,numOfIndividuals,i);
            
            //Solo il processo 0 deve calcolare il numero di vicini e poi inviare bool a tutti gli
            //altri processi con un broadcast
            
            if(my_rank == 0){bool = checkIfNearInfected(distances,minDistance,numOfIndividuals);}
            

            MPI_Bcast(&bool,1,MPI_INT,0,MPI_COMM_WORLD);

            MPI_Barrier(MPI_COMM_WORLD);

            updateState(bool,allIndividuals[i],time);

        }
        
        MPI_Barrier(MPI_COMM_WORLD);
        elapsedSeconds+=time;
        step++;
      }
      MPI_Barrier(MPI_COMM_WORLD);
        if (my_rank == 0)
        {
            printf("Do you wish to emulate another day? if so digit 1 ");
            scanf("%d",&answer);
        }

        MPI_Barrier(MPI_COMM_WORLD);

        MPI_Bcast(&answer,1,MPI_INT,0,MPI_COMM_WORLD);
        
        if(answer!=1)
        {

            if (my_rank == 0)
            {
                for(int i=0;i<numOfCountries;i++)
                    countryStatistics(getCountries(world)[i]);
            }

            exit = 1;
        }
            
     
    }

    MPI_Finalize();

}


void  buildWorld(struct World *world,int worldWidht,int worldHeight,int numOfCountries,int countryWidht,int countryHeight){

     /*
        y--------z  
        |        |
        x--------w
    */
 struct Point x= buildPoint(0,0);
 struct Point w= buildPoint(worldWidht,0);
 struct Point y= buildPoint(0,worldHeight);
 struct Point z= buildPoint(worldWidht,worldHeight); 

// now that the vertices of the map has been found we can place the countries

 /*
        yp------zp 
        |        |
        xp------wp
    */
struct Country *countries;
countries=malloc(numOfCountries*sizeof(struct Country));

int widhtOccupied=0; // the value of the widht covered by the countries placed on the map
int heightOccupied=0;  // the value of the height covered by the countries placed on the map

struct Point xp,wp,yp,zp;

   
   for(int i=0;i<numOfCountries;i++){


       if(widhtOccupied+countryWidht>worldWidht)
       {
            /* y--------z  
               |        |
               |     ---|--
               x-----|--w--|
            */ 
           //in this case i've to increase the y coordinate and start to occupy the upper region of the map
           heightOccupied=heightOccupied+countryHeight;
           widhtOccupied=0;
       }


        xp= buildPoint(widhtOccupied,heightOccupied);
        yp= buildPoint(widhtOccupied,heightOccupied+countryHeight);
        wp= buildPoint(widhtOccupied+countryWidht,heightOccupied);
        zp= buildPoint(widhtOccupied+countryWidht,heightOccupied+countryHeight); 

        addCountry(xp,yp,zp,wp,i,&countries[i]);
        widhtOccupied=widhtOccupied+countryWidht;
    }

   
 createWorld(x,y,z,w,countries,numOfCountries, world);

 

}




void addIndividuals(struct World*world, int numOfIndividuals, int numOfInfectedIndividuals,int speed){

   
    int numberOfCountries=world->numOfCountries;
    int i=0;
    int restOfPeople=numOfIndividuals;
    int restOfHealthyPeople=numOfIndividuals-numOfInfectedIndividuals;
    int restOfInfectedPeople=numOfInfectedIndividuals;
    int amountPerCountry;

//start scan of the countries
    while (i<=numberOfCountries && restOfPeople>0)
    {
        //in order to distribute the individuals around the world
        if(i<numberOfCountries-1)
            amountPerCountry=getAmountPerCountry(restOfPeople);
        else
            amountPerCountry=restOfPeople;
        printf("amount #%d : %d\n",i,amountPerCountry);
        //in order to place individuals inside the designated country
        while(amountPerCountry>0){

            if(restOfPeople>0){

                struct Individual *individual;
                individual=malloc(sizeof(struct Individual));
                if(restOfInfectedPeople<=0)
                *individual=createHealthyIndividual(pickvaluex(world->countries,i),pickvaluey(world->countries,i),restOfPeople);
               
    
                else
                {
                    //to choose if the individual is healthy
                    int bool=healthyOrSick(restOfHealthyPeople,restOfInfectedPeople);
                    //if the individual is infected we've to decrease the number of infected that needs to be placed
                    if(bool==1){
                        individual->state==infected;
                        *individual=createInfectedIndividual(pickvaluex(world->countries,i),pickvaluey(world->countries,i),restOfPeople);
                
                        restOfInfectedPeople--;
                    
                    }
                    else{
                        *individual=createHealthyIndividual(pickvaluex(world->countries,i),pickvaluey(world->countries,i),restOfPeople);
                        restOfHealthyPeople--;
                    }
                }

                

               addIndividual(world->countries[i].individuals,individual);
               struct  Country *punCountry=malloc(sizeof(struct Country));
                *punCountry=world->countries[i];
                individual->country=punCountry;
                individual->movement=setInitialMovement(speed);


                restOfPeople--;
                amountPerCountry--;
                
                
                
            }


            else return;
             

        }

    i++;

    }

}

//in order to choose a set of coordinates for the individual
int pickvaluex(struct Country *country,int i){
     /*
        y------z 
        |      |
        x------w
    */

    int num = (rand() % (country[i].w.x - country[i].x.x + 1)) + country[i].x.x;
    
    return num;
}

int pickvaluey(struct Country *country,int i){
     /*
        y------z 
        |      |
        x------w
    */

   int num = (rand() % (country[i].y.y - country[i].x.y + 1)) + country[i].x.y;
    
    return num;
}



int healthyOrSick(int healthyToAssign,int sickToAssign){
    if(healthyToAssign==0) //can't have other healthy individuals
        return 1;
    if(sickToAssign==0)//can't have other infected individuals
        return 0;
    int randomnumber = rand() % 2;
    
    return randomnumber;
}

int getAmountPerCountry(restOfPeople){
    
    int randomnumber = rand() % restOfPeople;
    return randomnumber;
}


void doMovement(struct Individual *individual,struct World world,int time){
 printf("\n -- movimento effettuato da:  %d     \n",individual->key);   
 
 individual->hasAlreadyMoved=1;

 Direction dir;
  //UP,DOWN,LEFT,RIGHT,UPLEFT,UPRIGHT,DOWNLEFT,DOWNRIGHT,STOP
 int randomnumber = rand() % 9;
 switch (randomnumber)
 {
     case 0: dir=UP;
     break;
     case 1: dir=DOWN;
     break;  
     case 2: dir=LEFT;
     break;  
     case 3: dir=RIGHT;
     break;  
     case 4: dir=UPLEFT;
     break;  
     case 5: dir=UPRIGHT;
     break;
     case 6: dir=DOWNLEFT;
     break;
     case 7: dir=DOWNRIGHT;
     break;
     case 8: dir=STOP;
     break;  
 
 default: dir=STOP;
     break;
 }

if(dir!=STOP)
    checkIfPossibleOtherwiseChange(dir,0,world,individual);
if(dir!=STOP)
    checkIfCountryHasBeenChanged(individual,world);   
printIndividual(individual);
if(dir==STOP)
    {printf("\nThe individual does not move in this turn\n");
    }


}



//nb if the individual is on the line between two countries it doesn't change its country value
// until it doesn't surpass the line
void checkIfCountryHasBeenChanged(struct Individual *individual,struct World world)  {
   
    struct Country *country=individual->country;
    if(individual->point.x>country->w.x||individual->point.x<country->x.x||individual->point.y>country->y.y||individual->point.y<country->x.y)
    {
         printf("\n l'individuo %d ha cambiato stato\n",individual->key);
        //then the country must be changed
        struct Country *countries=getCountries(world);
        int i=0;
        int imax=world.numOfCountries;
        while(i<imax){
           //when the choice about the new country happens on the line between the two -> pick the first one in the array of countries
         if(countries[i].x.x<=individual->point.x&&countries[i].w.x>=individual->point.x&&countries[i].x.y<=individual->point.y&&countries[i].y.y>=individual->point.y)
            {
                 printf("\n l'individuo %d ha richiesto l'update dello stato allo stato %d\n",individual->key,countries[i].name);
                //then we've found the right country
                
                updateCountry(individual,&countries[i]);
                
                
               return;

        
            }

         i++;
        }
    }
}
//if the direction is possible then change the indidiual's coordinates
void  checkIfPossibleOtherwiseChange(Direction dir,int attempts,struct World world,struct Individual *individual){
       //UP,DOWN,LEFT,RIGHT,UPLEFT,UPRIGHT,DOWNLEFT,DOWNRIGHT,
    int numberOfAttemps=attempts;

    if(attempts<2){

    switch (dir)
    {
    case UP:
        /*
        the individual moves along its y coordinate by increasing it 
            -> check if the movement can push the individual out the upper border of the world
        */
       if(individual->movement.v+individual->point.y<=world.y.y) //if so the movement is possible
        {
            individual->movement.direction=dir;
            setCoordinates(individual,individual->point.x,individual->point.y+individual->movement.v);
            return;
        }
       return checkIfPossibleOtherwiseChange(DOWN,numberOfAttemps++,world,individual);     
            
    case DOWN:
        /*
        the individual moves along its y coordinate by decreasing it 
            -> check if the movement can push the individual out the lower border of the world
        */
        if(individual->point.y-individual->movement.v>=world.x.y) //if so the movement is possible
           {
            individual->movement.direction=dir;
            setCoordinates(individual,individual->point.x,individual->point.y-individual->movement.v);
            return;
        }
       return checkIfPossibleOtherwiseChange(UP,numberOfAttemps++,world,individual);    

    case LEFT:
        /*
        the individual moves along its x coordinate by decreasing it 
            -> check if the movement can push the individual out the left border of the world
        */
       if(individual->point.x-individual->movement.v>=world.x.x) //if so the movement is possible
           {
            individual->movement.direction=dir;
            setCoordinates(individual,individual->point.x-individual->movement.v,individual->point.y);
            return;
        }
       return checkIfPossibleOtherwiseChange(RIGHT,numberOfAttemps++,world,individual);     

    case RIGHT:
        /*
        the individual moves along its x coordinate by increasing it 
            -> check if the movement can push the individual out the right border of the world
        */
       if(individual->movement.v+individual->point.x<=world.w.x) //if so the movement is possible
            {
            individual->movement.direction=dir;
            setCoordinates(individual,individual->movement.v+individual->point.x,individual->point.y);
            return;
        }
       return checkIfPossibleOtherwiseChange(DOWN,numberOfAttemps++,world,individual);     

    case UPLEFT:
        /*
        individual x -> decreased   individual y -> increased
        */
       if(individual->point.x-individual->movement.v>=world.x.x&&individual->movement.v+individual->point.y<=world.y.y)
            {
            individual->movement.direction=dir;
            setCoordinates(individual,individual->point.x-individual->movement.v,individual->movement.v+individual->point.y);
            return;
        }
       return checkIfPossibleOtherwiseChange(DOWNRIGHT,numberOfAttemps++,world,individual);

    case UPRIGHT:
        /*
        individual x -> increased   individual y -> increased
        */
        if(individual->movement.v+individual->point.x<=world.w.x&&individual->movement.v+individual->point.y<=world.y.y)
            {
            individual->movement.direction=dir;
            setCoordinates(individual,individual->movement.v+individual->point.x,individual->movement.v+individual->point.y);
            return;
        }
        return checkIfPossibleOtherwiseChange(DOWNLEFT,numberOfAttemps++,world,individual);
    
    case DOWNLEFT:
        /*
        individual x -> decreased   individual y -> decreased
        */
        if(individual->point.x-individual->movement.v>=world.x.x&&individual->point.y-individual->movement.v>=world.x.y)
             {
            individual->movement.direction=dir;
            setCoordinates(individual,individual->point.x-individual->movement.v,individual->point.y-individual->movement.v);
            return;
        }
        return checkIfPossibleOtherwiseChange(UPRIGHT,numberOfAttemps++,world,individual);

    case DOWNRIGHT:
        /*
        individual x -> increased   individual y -> decreased
        */
        if(individual->movement.v+individual->point.x<=world.w.x&&individual->point.y-individual->movement.v>=world.x.y)
            {
            individual->movement.direction=dir;
            setCoordinates(individual,individual->movement.v+individual->point.x,individual->point.y-individual->movement.v);
            return;
        }
        return checkIfPossibleOtherwiseChange(UPLEFT,numberOfAttemps++,world,individual);


    default:individual->movement.direction=STOP;
        return;
    }
    }

    else individual->movement.direction=STOP; //if both direction and the oppesed direction are not possible then the individual is stooped for the round

    return;
}