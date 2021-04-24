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



return createWorld(x,y,z,w,countries);

}



int charToInt(char c){
return c - '0';
}
