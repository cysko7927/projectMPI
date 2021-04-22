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
            //6 velocity
            //7 max distance
            // t

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
    int velocity=charToInt(argv[6]);
    int maxDistance=charToInt(argv[7]);
    int time=charToInt(argv[8]);
    

    if(numOfIndividuals<0||
        numOfInfectedIndividuals<0||
        worldHeight<0||
        worldWidht<0||
        countryHeight<0||
        countryWidht<0||
        velocity<0||
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

     int numOfCountries= (worldHeight*worldWidht) / (countryWidht*countryHeight);

    Country *countries;
    countries=malloc(numOfCountries*sizeof(Country));


    for(int i=0;i<numOfCountries;i++){
        countries[i].name=i;
        countries->x=countryWidht;
        countries->y=countryHeight;
    }
        
   World world=createWorld(worldWidht,worldHeight,countries);
    return 0;



}

int charToInt(char c){
return c - '0';
}