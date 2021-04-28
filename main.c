#include <stdio.h>
#include <world.h>
#include <country.h>




int main(int argc, char const *argv[])
{
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

    if(argc!=9){   
        printf("Please insert the required parameters");
        return 0;
        }

    int numOfIndividuals=charToInt(argv[0]);
    int numOfInfectedIndividuals=charToInt(argv[1]);
    int worldHeight=charToInt(argv[2]);
    int worldWidht=charToInt(argv[3]);
    int countryHeight=charToInt(argv[4]);
    int countryWidht=charToInt(argv[5]);
    int speed=charToInt(argv[6]);
    int maxDistance=charToInt(argv[7]);
    int time=charToInt(argv[8]);
    

    if(numOfIndividuals<0||
        numOfInfectedIndividuals<0||
        worldHeight<0||
        worldWidht<0||
        countryHeight<0||
        countryWidht<0||
        speed<0||
        maxDistance<0||
        time<0
        ){
        printf("All the values must be non negative");
        return 0;
    }
    if(numOfIndividuals<2){
        printf("the system must have at least 2 individuals");
        return 0;
    }

    if(numOfInfectedIndividuals<1){
        printf("the system must have at least 1 infected individual");
        return 0;
    }

    if(worldHeight==0){
        printf("the world's height has to be at least 1");
        return 0;
    }

    if(worldWidht==0){
        printf("the world's width has to be at least 1");
        return 0;
    }

    if(countryHeight==0){
        printf("the countries' height has to be at least 1");
        return 0;
    }

    if(countryWidht==0){
        printf("the countries' width has to be at least 1");
        return 0;
    }

    if(time==0){
        printf("please add an time interval greater than 0");
        return 0;
    }


    if(worldHeight<countryHeight){
        printf("the height of the countries cannot be higher than the world's height");
        return 0;
    }
    if(worldWidht<countryWidht){
        printf("the width of the countries cannot be longer than the world's width");
        return 0;
    }
    float rest= (worldHeight*worldWidht) % (countryWidht*countryHeight);

    if(rest!=0){
        printf("the area of the world have to be divisible by the area of the countries");
        return 0;
    }

    if(worldHeight%countryHeight!=0){
        printf("the height of the wolrd has to been divisible by the height of the countries");
        return 0;
    }

    if(worldWidht%countryWidht!=0){
        printf("the widht of the wolrd has to been divisible by the widht of the countries");
        return 0;
    }

     int numOfCountries= (worldHeight*worldWidht) / (countryWidht*countryHeight);
//---------------------------------------------------------------------------------------------------//




// creation of the world        
   World world=buildWorld(worldWidht,worldHeight,numOfCountries,countryWidht,countryHeight);
    return 0;

// add individuals to the world

    addIndividuals( world,  numOfIndividuals,  numOfInfectedIndividuals);
}


World buildWorld(int worldWidht,int worldHeight,int numOfCountries,int countryWidht,int countryHeight){

     /*
        y--------z  
        |        |
        x--------w
    */
 Point x= buildPoint(0,0);
 Point w= buildPoint(worldWidht,0);
 Point y= buildPoint(0,worldHeight);
 Point z= buildPoint(worldWidht,worldHeight); 

// now that the vertices of the map has been found we can place the countries

 /*
        yp------zp 
        |        |
        xp------wp
    */
Country *countries;
countries=malloc(numOfCountries*sizeof(Country));

int widhtOccupied=0; // the value of the widht covered by the countries placed on the map
int heightOccupied=0;  // the value of the height covered by the countries placed on the map


Point x,y,w,z;
   
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



        x= buildPoint(widhtOccupied,heightOccupied);
        y= buildPoint(widhtOccupied,heightOccupied+countryHeight);
        w= buildPoint(widhtOccupied+countryWidht,heightOccupied);
        z= buildPoint(widhtOccupied+countryWidht,heightOccupied+countryHeight); 

        countries[i]=addCountry(x,y,z,w,i);
    }



return createWorld(x,y,z,w,countries,numOfCountries);

}



int charToInt(char c){
    return c - '0';
}

void addIndividuals(World world, int numOfIndividuals, int numOfInfectedIndividuals){

    Country *country=world.countries;
    int numberOfCountries=world.numOfCountries;
    int i=0;
    int restOfPeople=numOfIndividuals;
    int restOfInfectedPeople=numOfInfectedIndividuals;
    int amountPerCountry;

//start scan of the countries
    while (i<=numberOfCountries && restOfPeople>0)
    {
        //in order to distribute the individuals around the world
        amountPerCountry=getAmountPerCountry(restOfPeople);
        
        //in order to place individuals inside the designated country
        while(amountPerCountry>0){

            if(restOfPeople>0){

                Individual *individual;
                if(restOfInfectedPeople<=0)
                individual->state=healthy;
    
                else
                {
                    //choose if the individual is healthy
                    individual->state=healthyOrSick();
                    //if the individual is infected we've to decrease the number of infected that needs to be placed
                    if(individual->state==infected)
                        restOfInfectedPeople--;
                }

                addIndividual(country[i].individuals,individual);
                restOfPeople--;
                amountPerCountry--;
            }

            else return; //all the individuals have been distributed

        }

    i++;

    }

}

StateIndividual healthyOrSick(){
    int randomnumber = rand() % 2;
    if(randomnumber==0){
        return healthy;
    }
    return infected;
}

int getAmountPerCountry(restOfPeople){
    int randomnumber = rand() % restOfPeople;
    return randomnumber;
}

void doMovement(Individual individual,World world){

    //1st randomically choose a direction
    individual.movement.direction=pickADirection(world,individual);

}

Direction pickADirection(World world,Individual individual){

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
    dir=checkIfPossibleOtherwiseChange(dir,0,world,individual);
return dir;

}

Direction checkIfPossibleOtherwiseChange(Direction dir,int attempts,World world,Individual individual){
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
       if(individual.movement.v+individual.point.y<=world.y.y) //if so the movement is possible
            return dir;
       return checkIfPossibleOtherwiseChange(DOWN,numberOfAttemps++,world,individual);     
            
    case DOWN:
        /*
        the individual moves along its y coordinate by decreasing it 
            -> check if the movement can push the individual out the lower border of the world
        */
        if(individual.point.y-individual.movement.v>=world.x.y) //if so the movement is possible
            return dir;
       return checkIfPossibleOtherwiseChange(UP,numberOfAttemps++,world,individual);    

    case LEFT:
        /*
        the individual moves along its x coordinate by decreasing it 
            -> check if the movement can push the individual out the left border of the world
        */
       if(individual.point.x-individual.movement.v>=world.x.x) //if so the movement is possible
            return dir;
       return checkIfPossibleOtherwiseChange(RIGHT,numberOfAttemps++,world,individual);     

    case RIGHT:
        /*
        the individual moves along its x coordinate by increasing it 
            -> check if the movement can push the individual out the right border of the world
        */
       if(individual.movement.v+individual.point.x<=world.w.x) //if so the movement is possible
            return dir;
       return checkIfPossibleOtherwiseChange(DOWN,numberOfAttemps++,world,individual);     

    case UPLEFT:
        /*
        individual x -> decreased   individual y -> increased
        */
       if(individual.point.x-individual.movement.v>=world.x.x&&individual.movement.v+individual.point.y<=world.y.y)
            return dir;
       return checkIfPossibleOtherwiseChange(DOWNRIGHT,numberOfAttemps++,world,individual);

    case UPRIGHT:
        /*
        individual x -> increased   individual y -> increased
        */
        if(individual.movement.v+individual.point.x<=world.w.x&&individual.movement.v+individual.point.y<=world.y.y)
            return dir;
        return checkIfPossibleOtherwiseChange(DOWNLEFT,numberOfAttemps++,world,individual);
    
    case DOWNLEFT:
        /*
        individual x -> decreased   individual y -> decreased
        */
        if(individual.point.x-individual.movement.v>=world.x.x&&individual.point.y-individual.movement.v>=world.x.y)
            return dir;
        return checkIfPossibleOtherwiseChange(UPRIGHT,numberOfAttemps++,world,individual);

    case DOWNRIGHT:
        /*
        individual x -> increased   individual y -> decreased
        */
        if(individual.movement.v+individual.point.x<=world.w.x&&individual.point.y-individual.movement.v>=world.x.y)
            return dir;
        return checkIfPossibleOtherwiseChange(UPLEFT,numberOfAttemps++,world,individual);


    default:
        return STOP;
    }
    }

    else return STOP; //if both direction and the oppesed direction are not possible then the individual is stooped for the round
}