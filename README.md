Project #4: A Simple Model for Virus Spreading

------------ Configurations  -------------

Insert the command:
  mpirun -np 1 ./a.out numOfIndividuals numOfInfectedIndividuals worldHeight worldWidht countryHeight countryWidht speed minDistance time

  inside the executable directory

numOfIndividuals= number of individuals to check.
numOfInfectedIndividuals= initial infected individuals.  
worldHeight and worldWidht = dimension of the considered world.
countryHeight and countryWidht = dimension of a country.
speed= movement speed of an individual.
minDistance= limit distance in order to infect an healthy individual.
time= slice of time between system updates.

There are some constraint on these values:
    1) all the values have to be positive
    2) the system requires at least 2 individual and at least one of them has to be infected
    3) the dimension of a country cannot be greater than the dimension of the world itself
