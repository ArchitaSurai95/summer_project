/* Dimensions of the defined cube: 10x10x10
   co-ordinates of all the vertices of the cube: {(0,0,0),(10,0,0),(0,10,0),(10,10,0),(0,0,10),(0,10,10),(10,0,10),(10,10,10)}
*/ 

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

#define G 6.673
#define NO_OF_PARTICLES 5
#define NO_OF_STEPS 5
#define STEP_SIZE .5
#define DIMENSION 10


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

	/* loop to display the mass of the particles */
	printf("The mass of the particles are:\n");
	for(counter=0;counter<NO_OF_PARTICLES;counter++)
	printf("%d ",mass[counter]);
	printf("\n");
	return mass;
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
		co_ordinates[counter*NO_OF_PARTICLES]=rand()%(DIMENSION+1);
		co_ordinates[(counter*NO_OF_PARTICLES)+1]=rand()%(DIMENSION+1);
		co_ordinates[(counter*NO_OF_PARTICLES)+2]=rand()%(DIMENSION+1);
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

/** Method to calculate the distance between the particles
  * @param: *distance,*co_ordinates: a pointer to the array storing the distance,ponter to array storing the co-ordinates
  * modifies contents of the array storing the distance (2D array)
  * returns: a pointer to the array storing the distance
*/
float* calculate_distance(float* distance, int* co_ordinates)
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

	/* loop to display the distance between the particles */	
	printf("The values of the corresponding distances:\n");
	for(row_counter=0;row_counter<NO_OF_PARTICLES;row_counter++)
	{
		for(col_counter=0;col_counter<NO_OF_PARTICLES;col_counter++)
		{
			printf("%.2f     ",distance[(row_counter*NO_OF_PARTICLES)+col_counter]); 				
		}
		printf("\n");
	}	
	return distance;
}


/** Method to calculate the force between the particles
  * @param: *force,*distance,*mass: pointer to array storing force,a pointer to the array storing the distance,pointer to array storing 
  * the mass
  * modifies contents of the array storing the force (2D array)
  * returns: a pointer to the array storing the force
*/
float* calculate_force(float* force,float* distance,int* mass)
{
	int row_counter,col_counter;
	float r;							// stores distance between the particles
	int m1,m2;							// stores mass of the two interacting particles;
	for(row_counter=0;row_counter<NO_OF_PARTICLES;row_counter++)
	{
		for(col_counter=0;col_counter<NO_OF_PARTICLES;col_counter++)
		{
			if(row_counter==col_counter)
				force[(row_counter*NO_OF_PARTICLES)+col_counter]=0;
			else
			{
				r=distance[(row_counter*NO_OF_PARTICLES)+col_counter];
				m1=mass[row_counter];
				m2=mass[col_counter];
				force[(row_counter*NO_OF_PARTICLES)+col_counter]=((G*m1*m2)/(r*r));
				
			}
		}
	}

	/* loop to display the force between the particles */
	printf("The values of the corresponding forces (of the order of 10^-11 N) :\n");
	for(row_counter=0;row_counter<NO_OF_PARTICLES;row_counter++)
	{
		for(col_counter=0;col_counter<NO_OF_PARTICLES;col_counter++)
		{
			printf("%.2f     ",force[(row_counter*NO_OF_PARTICLES)+col_counter]); 				
		}
		printf("\n");
	}
	return force;
}


/** Method to calculate the resultant force between the particles
  * @param: *resultant_force,*force: pointer to array storing the resultant force,a pointer to the array storing the force
  * modifies contents of the array storing the resultant force (1D array)
  * returns: a pointer to the array storing the resultant force
*/
float* calculate_resultant_force(float* resultant_force,float* force)
{
	int row_counter,col_counter;
	for(row_counter=0;row_counter<NO_OF_PARTICLES;row_counter++)
	{
		resultant_force[row_counter]=0;
		for(col_counter=0;col_counter<NO_OF_PARTICLES;col_counter++)
		{
			resultant_force[row_counter]+=force[(row_counter*NO_OF_PARTICLES)+col_counter];
		}
	}

	/* loop to display the resultant force acting on the particles */
	printf("The resultant force on the particles are (of the order of 10^-11 N) :\n");
	for(row_counter=0;row_counter<NO_OF_PARTICLES;row_counter++)
	printf("%.2f     ",resultant_force[row_counter]);
	printf("\n");
	return resultant_force;
}


/** Method to initialise the initial velocity of the particles
  * @param: *initial_velocity: pointer to array storing the initial velocity
  * modifies contents of the array storing the initial velocity (1D array)
  * returns: a pointer to the array storing the initial velocity
*/
float* initialise_initial_velocity(float* initial_velocity)
{
	int counter;
	for(counter=0;counter<NO_OF_PARTICLES;counter++)
	initial_velocity[counter]=0;
	return initial_velocity;
}


/** Method to initialise the final velocity of the particles
  * @param: *final_velocity: pointer to array storing the final velocity
  * modifies contents of the array storing the final velocity (1D array)
  * returns: a pointer to the array storing the final velocity
*/
float* initialise_final_velocity(float* final_velocity)
{
	int counter;
	for(counter=0;counter<NO_OF_PARTICLES;counter++)
	final_velocity[counter]=0;
	return final_velocity;
}


/** Method to calculate the velocity and co-ordinates of the particles after every time step
  * @param: 
  * 1)*inital_velocity: pointer to array storing the inital velocity
  * 2)*final_velocity: pointer to array storing the final velocity
  * 3)*resultant_force: pointer to the array storing the resultant force between the particles
  * 4)*co_ordinates: pointer to the array storing the co-ordinates
  * 5)*mass: pointer to the array storing the mass of the particles
  * 6)*force: pointer to the array storing the force between the particles
  * 7)*distance: pointer to the array storing the distance between the particles
  * modifies contents of the array storing the initial velocity, final velocity, force, resultant force, co-ordinates, distance.
  * returns: void
*/
void velocity_verlet_function(float* initial_velocity,float* final_velocity,float* resultant_force,int* co_ordinates,int* mass,
float* force,float* distance)
{
	int counter,step_counter;
	for(step_counter=0;step_counter<NO_OF_STEPS;step_counter++)
	{
		for(counter=0;counter<NO_OF_PARTICLES;counter++)
		final_velocity[counter]=initial_velocity[counter]+((resultant_force[counter]*STEP_SIZE)/(2*mass[counter]));

		for(counter=0;counter<NO_OF_PARTICLES;counter++)
		{
		co_ordinates[counter*NO_OF_PARTICLES]=(int)co_ordinates[counter*NO_OF_PARTICLES]+(final_velocity[counter]*STEP_SIZE);
		if(co_ordinates[counter*NO_OF_PARTICLES]>DIMENSION)
		co_ordinates[counter*NO_OF_PARTICLES]=DIMENSION-(co_ordinates[counter*NO_OF_PARTICLES]-DIMENSION);
		}

		distance=calculate_distance(distance,co_ordinates);
		force=calculate_force(force,distance,mass);
		resultant_force=calculate_resultant_force(resultant_force,force);
			
		for(counter=0;counter<NO_OF_PARTICLES;counter++)
		initial_velocity[counter]=final_velocity[counter];

		for(counter=0;counter<NO_OF_PARTICLES;counter++)
		final_velocity[counter]=initial_velocity[counter]+((resultant_force[counter]*STEP_SIZE)/(2*mass[counter]));
	}
}	
	

/* Driver function for all the above methods */
int main()
{
	int *co_ordinates,*mass;
	float *distance,*force,*resultant_force;
	float *initial_velocity,*final_velocity;
	int counter,col_counter,row_counter;;


	co_ordinates=(int*)malloc(3*NO_OF_PARTICLES*sizeof(int));		// allocating space for the co_ordinates array
	if(co_ordinates==NULL)
	{
		printf("Error in memory allocation");
		exit(1);
	}
	co_ordinates=generate_random_coordinates(co_ordinates);			// method called to generate co-ordinates

	mass=(int*)malloc(NO_OF_PARTICLES*sizeof(int));				// allocating space for the mass array
	if(mass==NULL)
	{
		printf("Error in memory allocation");
		exit(1);
	}
	mass=initialise_mass_of_particles(mass);				// method called to initialise the mass of the particles

	distance=(float*)malloc(NO_OF_PARTICLES*NO_OF_PARTICLES*sizeof(float));	// allocating space for the distance array
	if(distance==NULL)
	{
		printf("Error in memory allocation");
		exit(1);
	}
	distance=calculate_distance(distance,co_ordinates);			// method called to initialize the distance
		
	force=(float*)malloc(NO_OF_PARTICLES*NO_OF_PARTICLES*sizeof(float));	// allocating space for the force array
	if(force==NULL)
	{
		printf("Error in memory allocation");
		exit(1);
	}	
	force=calculate_force(force,distance,mass);				// method called to initialize the force
	
	resultant_force=(float*)malloc(NO_OF_PARTICLES*sizeof(float));		// allocating space for the resultant_force array
	if(resultant_force==NULL)
	{
		printf("Error in memory allocation");
		exit(1);
	}	
	resultant_force=calculate_resultant_force(resultant_force,force);	// method called to initialize the resultant force

	initial_velocity=(float*)malloc(NO_OF_PARTICLES*sizeof(float));		// allocating space for the initial_velocity array
	if(initial_velocity==NULL)
	{
		printf("Error in memory allocation");
		exit(1);
	}	
	initial_velocity=initialise_initial_velocity(initial_velocity);		// method called to initialize the initial velocity

	final_velocity=(float*)malloc(NO_OF_PARTICLES*sizeof(float));		// allocating space for the final_velocity array
	if(final_velocity==NULL)
	{
		printf("Error in memory allocation");
		exit(1);
	}	
	final_velocity=initialise_final_velocity(final_velocity);		// method called to initialize the final velocity
	
	velocity_verlet_function(initial_velocity,final_velocity,resultant_force,co_ordinates,mass,force,distance);

	printf("The updated values of velocity are:\n\n");
	for(counter=0;counter<NO_OF_PARTICLES;counter++)
	printf("%.2f    ",final_velocity[counter]);
	printf("\n");

	return 0;
}
