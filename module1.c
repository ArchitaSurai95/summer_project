/* Dimensions of the defined cube: 10x10x10
   co-ordinates of all the vertices of the cube: {(0,0,0),(10,0,0),(0,10,0),(10,10,0),(0,0,10),(0,10,10),(10,0,10),(10,10,10)}
*/ 

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

#define G 6.673
#define NO_OF_PARTICLES 5


/** Method to initialise the mass of the particles
  * @param: pointer to the array storing the mass of the particles
  * modifies content of array mass(1D array)
  * returns: pointer to the array storng the mass of the particles
*/
int* initialise_mass_of_particles(int *mass)
{
	int counter;					// to iterate for all the particles

	/* loop to initialize the mass of the particles */
	for(counter=0;counter<NO_OF_PARTICLES;counter++)
	{
		mass[counter]=counter+1;
	}
	printf("The mass of the particles are:\n");
	for(counter=0;counter<NO_OF_PARTICLES;counter++)
	printf("%d ",mass[counter]);
	printf("\n");
}


/** Method to generate random co-ordinates for the particles
  * @param: *co_ordinates: a pointer to the array storing the co-ordinates
  * modifies contents of the array storing the co-ordinates (2D array)
  * returns: a pointer to the array storing the co-ordinates
*/
int* generate_random_coordinates(int *co_ordinates)
{
	int counter,col_counter;
	time_t timer;	
	srand((unsigned) time(&timer));			//initializing the random number generator

	/* loop to generate random x,y and z co-ordinates of the particles */
	for(counter=0;counter<NO_OF_PARTICLES;counter++)
	{		
		co_ordinates[counter*NO_OF_PARTICLES]=rand()%11;
		co_ordinates[(counter*NO_OF_PARTICLES)+1]=rand()%11;
		co_ordinates[(counter*NO_OF_PARTICLES)+2]=rand()%11;
	}

	/* loop to display the value of the generated co-ordinates of the particles */
	printf("The value of the generated co-ordinates:\n");
	for(counter=0;counter<NO_OF_PARTICLES;counter++)
	{
		for(col_counter=0;col_counter<3;col_counter++)
		{
			printf("%d ",co_ordinates[(counter*NO_OF_PARTICLES)+col_counter]);
		}
		printf("\n");
	}	
	return co_ordinates;
}

/** Method to initialise the distance between the particles
  * @param: *distance,*co_ordinates: a pointer to the array storing the distance,ponter to array storing the co-ordinates
  * modifies contents of the array storing the distance (2D array)
  * returns: a pointer to the array storing the distance
*/
float* initialise_distance(float* distance, int* co_ordinates)
{
	int row_counter,col_counter;
	int x0,x1,y0,y1,z0,z1;
	float dist;
	for(row_counter=0;row_counter<NO_OF_PARTICLES;row_counter++)
	{
		for(col_counter=0;col_counter<NO_OF_PARTICLES;col_counter++)
		{
			if(row_counter==col_counter)
				distance[(row_counter*NO_OF_PARTICLES)+col_counter]=0;
			else
			{
				x0=co_ordinates[(row_counter*NO_OF_PARTICLES)];
				x1=co_ordinates[(col_counter*NO_OF_PARTICLES)];	

				y0=co_ordinates[(row_counter*NO_OF_PARTICLES)+1];
				y1=co_ordinates[(col_counter*NO_OF_PARTICLES)+1];

				z0=co_ordinates[(row_counter*NO_OF_PARTICLES)+2];
				z1=co_ordinates[(col_counter*NO_OF_PARTICLES)+2];

				dist=((x0-x1)*(x0-x1))+((y0-y1)*(y0-y1))+((z0-z1)*(z0-z1));
				dist=sqrt(dist);
				distance[(row_counter*NO_OF_PARTICLES)+col_counter]=dist;
			}
		}
	}

	printf("The values of the corresponding distances:\n");
	for(row_counter=0;row_counter<NO_OF_PARTICLES;row_counter++)
	{
		for(col_counter=0;col_counter<NO_OF_PARTICLES;col_counter++)
		{
			printf("%.2f ",distance[(row_counter*NO_OF_PARTICLES)+col_counter]); 				
		}
		printf("\n");
	}
}

/* Driver function for all the above methods */
int main()
{
	int *co_ordinates,*mass;
	float *distance;
	int counter,col_counter;
	time_t timer;

	co_ordinates=(int*)malloc(3*NO_OF_PARTICLES*sizeof(int));		// allocating space for the co_ordinates array
	co_ordinates=generate_random_coordinates(co_ordinates);			// method called to generate co-ordinates

	mass=(int*)malloc(NO_OF_PARTICLES*sizeof(int));				// allocating space for the mass array
	mass=initialise_mass_of_particles(mass);				// method called to initialise the mass of the particles

	distance=(float*)malloc(NO_OF_PARTICLES*NO_OF_PARTICLES*sizeof(float));	// allocating space for the distance array
	distance=initialise_distance(distance,co_ordinates);			// method called to initialize the distance
	/*initialise_force_on_particles();					// method called to initialise the force on the particles
*/
	return 0;
}
