/* Dimensions of the defined cube: 10x10x10
   co-ordinates of all the vertices of the cube: {(0,0,0),(10,0,0),(0,10,0),(10,10,0),(0,0,10),(0,10,10),(10,0,10),(10,10,10)}
*/ 

/* Assumptions:
1) All particles are point mass particles.
2) Force always acts in positive x-direction.
3) All co-ordinates are integer values.
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

#define G 6.673
#define NO_OF_PARTICLES 5
#define NO_OF_STEPS 1
#define STEP_SIZE 1
#define DIMENSION 10
#define R_CUT 1

int co_ordinates[NO_OF_PARTICLES][3],mass[NO_OF_PARTICLES];
float x_displacement[NO_OF_PARTICLES][NO_OF_PARTICLES],y_displacement[NO_OF_PARTICLES][NO_OF_PARTICLES],
z_displacement[NO_OF_PARTICLES][NO_OF_PARTICLES];
float x_force[NO_OF_PARTICLES][NO_OF_PARTICLES],y_force[NO_OF_PARTICLES][NO_OF_PARTICLES],
z_force[NO_OF_PARTICLES][NO_OF_PARTICLES],resultant_force[NO_OF_PARTICLES][3];
float initial_velocity[NO_OF_PARTICLES][3],final_velocity[NO_OF_PARTICLES][3];


/** Method to initialise the mass of the particles
  * modifies content of array mass(1D array)
*/
void initialise_mass_of_particles()
{
	int counter;					// to iterate for all the particles

	/* loop to initialize the mass of the particles */
	for(counter=0;counter<NO_OF_PARTICLES;counter++)
	{
		mass[counter]=2;
	}

	/* loop to display the mass of the particles */
	printf("The mass of the particles are:\n");
	for(counter=0;counter<NO_OF_PARTICLES;counter++)
	printf("%d ",mass[counter]);
	printf("\n");
	
}


/** Method to generate random co-ordinates for the particles
  * modifies contents of the array storing the co-ordinates (2D array)
*/
void generate_random_coordinates()
{
	int counter,col_counter;
	time_t timer;	
	srand((unsigned) time(&timer));			//initializing the random number generator

	/* loop to generate random x,y and z co-ordinates of the particles */
	for(counter=0;counter<NO_OF_PARTICLES;counter++)
	{		
		for(col_counter=0;col_counter<3;col_counter++)
		co_ordinates[counter][col_counter]=(rand()%(DIMENSION+1));
		
	}

	/*for(counter=0;counter<NO_OF_PARTICLES;counter++)
	{
		for(col_counter=0;col_counter<3;col_counter++)
		{
			scanf("%d",&co_ordinates[(counter*NO_OF_PARTICLES)+col_counter]);
		}
		printf("\n");
	}

	/* loop to display the value of the generated co-ordinates of the particles */
	printf("The value of the generated co-ordinates:\n");
	for(counter=0;counter<NO_OF_PARTICLES;counter++)
	{
		for(col_counter=0;col_counter<3;col_counter++)
		{
			printf("%d ",co_ordinates[counter][col_counter]);
		}
		printf("\n");
	}	
}

/** Method to calculate the displacement in x direction between the particles
  * modifies contents of the array storing the displacement (2D array)
 */
void calculate_x_displacement()
{
	int row_counter,col_counter;
	int x0,x1;
	float dist;
	for(row_counter=0;row_counter<NO_OF_PARTICLES;row_counter++)
	{
		for(col_counter=0;col_counter<NO_OF_PARTICLES;col_counter++)
		{
			if(row_counter==col_counter)
				x_displacement[row_counter][col_counter]=0;
			else
			{
				x0=co_ordinates[row_counter][0];
				x1=co_ordinates[col_counter][0];	

				dist=abs((x0-x1));
				x_displacement[row_counter][col_counter]=dist;
			}
		}
	}

	/* loop to display the displacement in x direction between the particles */	
	printf("The values of the corresponding displacements in x direction:\n");
	for(row_counter=0;row_counter<NO_OF_PARTICLES;row_counter++)
	{
		for(col_counter=0;col_counter<NO_OF_PARTICLES;col_counter++)
		{
			printf("%.2f     ",x_displacement[row_counter][col_counter]); 				
		}
		printf("\n");
	}	
}


/** Method to calculate the displacement in y direction between the particles
  * modifies contents of the array storing the displacement (2D array)
  */
void calculate_y_displacement()
{
	int row_counter,col_counter;
	int y0,y1;
	float dist;
	for(row_counter=0;row_counter<NO_OF_PARTICLES;row_counter++)
	{
		for(col_counter=0;col_counter<NO_OF_PARTICLES;col_counter++)
		{
			if(row_counter==col_counter)
				y_displacement[row_counter][col_counter]=0;
			else
			{
				y0=co_ordinates[row_counter][1];
				y1=co_ordinates[col_counter][1];	

				dist=abs((y0-y1));
				y_displacement[row_counter][col_counter]=dist;
			}
		}
	}

	/* loop to display the displacement in y direction between the particles */	
	printf("The values of the corresponding displacements in y direction:\n");
	for(row_counter=0;row_counter<NO_OF_PARTICLES;row_counter++)
	{
		for(col_counter=0;col_counter<NO_OF_PARTICLES;col_counter++)
		{
			printf("%.2f     ",y_displacement[row_counter][col_counter]); 				
		}
		printf("\n");
	}	
}


/** Method to calculate the displacement in y direction between the particles
  * modifies contents of the array storing the displacement (2D array)
*/
void calculate_z_displacement()
{
	int row_counter,col_counter;
	int z0,z1;
	float dist;
	for(row_counter=0;row_counter<NO_OF_PARTICLES;row_counter++)
	{
		for(col_counter=0;col_counter<NO_OF_PARTICLES;col_counter++)
		{
			if(row_counter==col_counter)
				z_displacement[row_counter][col_counter]=0;
			else
			{
				z0=co_ordinates[row_counter][2];
				z1=co_ordinates[col_counter][2];	

				dist=abs((z0-z1));
				z_displacement[row_counter][col_counter]=dist;
			}
		}
	}

	/* loop to display the displacement in z direction between the particles */	
	printf("The values of the corresponding displacements in z direction:\n");
	for(row_counter=0;row_counter<NO_OF_PARTICLES;row_counter++)
	{
		for(col_counter=0;col_counter<NO_OF_PARTICLES;col_counter++)
		{
			printf("%.2f     ",z_displacement[row_counter][col_counter]); 				
		}
		printf("\n");
	}	
}



/** Method to calculate the force between the particles acting along x direction
  * modifies contents of the array storing the x_force (2D array)
  */
void calculate_x_force()
{
	int row_counter,col_counter;
	float r;							// stores distance between the particles
	int m1,m2;							// stores mass of the two interacting particles;
	for(row_counter=0;row_counter<NO_OF_PARTICLES;row_counter++)
	{
		for(col_counter=0;col_counter<NO_OF_PARTICLES;col_counter++)
		{
			if(row_counter==col_counter)
				x_force[row_counter][col_counter]=0;
			else
			{
				r=x_displacement[row_counter][col_counter];
				m1=mass[row_counter];
				m2=mass[col_counter];
				if(r<R_CUT)
				x_force[row_counter][col_counter]=0;
				else
				x_force[row_counter][col_counter]=((G*m1*m2)/(r*r));
				
			}
		}
	}

	/* loop to display the force between the particles in x direction */
	printf("The values of the corresponding forces in x direction(of the order of 10^-11 N) :\n");
	for(row_counter=0;row_counter<NO_OF_PARTICLES;row_counter++)
	{
		for(col_counter=0;col_counter<NO_OF_PARTICLES;col_counter++)
		{
			printf("%.2f     ",x_force[row_counter][col_counter]); 				
		}
		printf("\n");
	}
}


/** Method to calculate the force between the particles acting along y direction
  * modifies contents of the array storing the y_force (2D array)
  */
void calculate_y_force()
{
	int row_counter,col_counter;
	float r;							// stores distance between the particles
	int m1,m2;							// stores mass of the two interacting particles;
	for(row_counter=0;row_counter<NO_OF_PARTICLES;row_counter++)
	{
		for(col_counter=0;col_counter<NO_OF_PARTICLES;col_counter++)
		{
			if(row_counter==col_counter)
				y_force[row_counter][col_counter]=0;
			else
			{
				r=y_displacement[row_counter][col_counter];
				m1=mass[row_counter];
				m2=mass[col_counter];
				if(r<R_CUT)
				y_force[row_counter][col_counter]=0;
				else
				y_force[row_counter][col_counter]=((G*m1*m2)/(r*r));
				
			}
		}
	}

	/* loop to display the force between the particles in y direction */
	printf("The values of the corresponding forces in y direction(of the order of 10^-11 N) :\n");
	for(row_counter=0;row_counter<NO_OF_PARTICLES;row_counter++)
	{
		for(col_counter=0;col_counter<NO_OF_PARTICLES;col_counter++)
		{
			printf("%.2f     ",y_force[row_counter][col_counter]); 				
		}
		printf("\n");
	}
}


/** Method to calculate the force between the particles acting along z direction
  * modifies contents of the array storing the z_force (2D array)
  */
void calculate_z_force()
{
	int row_counter,col_counter;
	float r;							// stores distance between the particles
	int m1,m2;							// stores mass of the two interacting particles;
	for(row_counter=0;row_counter<NO_OF_PARTICLES;row_counter++)
	{
		for(col_counter=0;col_counter<NO_OF_PARTICLES;col_counter++)
		{
			if(row_counter==col_counter)
				z_force[row_counter][col_counter]=0;
			else
			{
				r=z_displacement[row_counter][col_counter];
				m1=mass[row_counter];
				m2=mass[col_counter];
				if(r<R_CUT)
				z_force[row_counter][col_counter]=0;
				else
				z_force[row_counter][col_counter]=((G*m1*m2)/(r*r));
				
			}
		}
	}

	/* loop to display the force between the particles in z direction */
	printf("The values of the corresponding forces in y direction(of the order of 10^-11 N) :\n");
	for(row_counter=0;row_counter<NO_OF_PARTICLES;row_counter++)
	{
		for(col_counter=0;col_counter<NO_OF_PARTICLES;col_counter++)
		{
			printf("%.2f     ",z_force[row_counter][col_counter]); 				
		}
		printf("\n");
	}
}

/** Method to calculate the resultant force between the particles
  * modifies contents of the array storing the resultant force (1D array)
  */
void calculate_resultant_force()
{
	int row_counter,col_counter;
	for(row_counter=0;row_counter<NO_OF_PARTICLES;row_counter++)
	{
		resultant_force[row_counter][0]=0;
		for(col_counter=0;col_counter<NO_OF_PARTICLES;col_counter++)
		{
			resultant_force[row_counter][0]+=x_force[row_counter][col_counter];
		}
	}

	for(row_counter=0;row_counter<NO_OF_PARTICLES;row_counter++)
	{
		resultant_force[row_counter][1]=0;
		for(col_counter=0;col_counter<NO_OF_PARTICLES;col_counter++)
		{
			resultant_force[row_counter][1]+=y_force[row_counter][col_counter];
		}
	}

	for(row_counter=0;row_counter<NO_OF_PARTICLES;row_counter++)
	{
		resultant_force[row_counter][2]=0;
		for(col_counter=0;col_counter<NO_OF_PARTICLES;col_counter++)
		{
			resultant_force[row_counter][2]+=z_force[row_counter][col_counter];
		}
	}

	/* loop to display the resultant force acting on the particles */
	printf("The resultant force on the particles are (of the order of 10^-11 N) :\n");
	for(row_counter=0;row_counter<NO_OF_PARTICLES;row_counter++)
	{
		printf("%.2fi   %.2fj   %.2fk",resultant_force[row_counter][0],
		resultant_force[row_counter][1],resultant_force[row_counter][2]);
		printf("\n");
	}
}


/** Method to initialise the initial velocity of the particles
  * modifies contents of the array storing the initial velocity (1D array)
*/
void initialise_initial_velocity()
{
	int row_counter,col_counter;
	for(row_counter=0;row_counter<NO_OF_PARTICLES;row_counter++)
	for(col_counter=0;col_counter<3;col_counter++)
	initial_velocity[row_counter][col_counter]=0;
	printf("initial velocity\n");
	for(row_counter=0;row_counter<NO_OF_PARTICLES;row_counter++)
	{
		for(col_counter=0;col_counter<3;col_counter++)
		printf("%.2f    ",initial_velocity[row_counter][col_counter]);
		printf("\n");
	}
}


/** Method to initialise the final velocity of the particles
  * modifies contents of the array storing the final velocity (1D array)
*/
void initialise_final_velocity()
{
	int row_counter,col_counter;
	for(row_counter=0;row_counter<NO_OF_PARTICLES;row_counter++)
	for(col_counter=0;col_counter<3;col_counter++)
	final_velocity[row_counter][col_counter]=0;
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
void velocity_verlet_function()
{
	int counter,step_counter,row_counter,col_counter;
	for(step_counter=0;step_counter<NO_OF_STEPS;step_counter++)
	{	
		for(counter=0;counter<NO_OF_PARTICLES;counter++)
		final_velocity[counter][0]=initial_velocity[counter][0]+((resultant_force[counter][0]*STEP_SIZE)/(2*mass[counter]));

		for(counter=0;counter<NO_OF_PARTICLES;counter++)
		final_velocity[counter][1]=initial_velocity[counter][1]+((resultant_force[counter][1]*STEP_SIZE)/(2*mass[counter]));

		for(counter=0;counter<NO_OF_PARTICLES;counter++)
		final_velocity[counter][2]=initial_velocity[counter][2]+((resultant_force[counter][2]*STEP_SIZE)/(2*mass[counter]));
		printf("final velocity\n");
		for(row_counter=0;row_counter<NO_OF_PARTICLES;row_counter++)
		{
		for(col_counter=0;col_counter<3;col_counter++)
		printf("%.2f    ",final_velocity[row_counter][col_counter]);
		printf("\n");
		}

		for(counter=0;counter<NO_OF_PARTICLES;counter++)
		{
		co_ordinates[counter][0]=(int)co_ordinates[counter][0]+(final_velocity[counter][0]*STEP_SIZE);
		if(co_ordinates[counter][0]>DIMENSION)
		co_ordinates[counter][0]=DIMENSION-(co_ordinates[counter][0]-DIMENSION);
		}

		for(counter=0;counter<NO_OF_PARTICLES;counter++)
		{
		co_ordinates[counter][1]=(int)co_ordinates[counter][1]+(final_velocity[counter][1]*STEP_SIZE);
		if(co_ordinates[counter][1]>DIMENSION)
		co_ordinates[counter][1]=DIMENSION-(co_ordinates[counter][1]-DIMENSION);
		}

		for(counter=0;counter<NO_OF_PARTICLES;counter++)
		{
		co_ordinates[counter][2]=(int)co_ordinates[counter][2]+(final_velocity[counter][2]*STEP_SIZE);
		if(co_ordinates[counter][2]>DIMENSION)
		co_ordinates[counter][2]=DIMENSION-(co_ordinates[counter][2]-DIMENSION);
		}

		calculate_x_displacement();
		calculate_y_displacement();
		calculate_z_displacement();


		calculate_x_force();
		calculate_y_force();
		calculate_z_force();
 
		calculate_resultant_force();
			
		for(row_counter=0;row_counter<NO_OF_PARTICLES;row_counter++)
		for(col_counter=0;col_counter<3;col_counter++)
		initial_velocity[row_counter][col_counter]=final_velocity[row_counter][col_counter];

		for(counter=0;counter<NO_OF_PARTICLES;counter++)
		final_velocity[counter][0]=initial_velocity[counter][0]+((resultant_force[counter][0]*STEP_SIZE)/(2*mass[counter]));

		for(counter=0;counter<NO_OF_PARTICLES;counter++)
		final_velocity[counter][1]=initial_velocity[counter][1]+((resultant_force[counter][1]*STEP_SIZE)/(2*mass[counter]));

		for(counter=0;counter<NO_OF_PARTICLES;counter++)
		final_velocity[counter][2]=initial_velocity[counter][2]+((resultant_force[counter][2]*STEP_SIZE)/(2*mass[counter]));


	}
}	
	

/* Driver function for all the above methods */
int main()
{
	
	int row_counter,col_counter;

	generate_random_coordinates();			// method called to generate co-ordinates
	initialise_mass_of_particles();			// method called to initialise the mass of the particles
	calculate_x_displacement();			// method called to initialize the x_displacement
	calculate_y_displacement();			// method called to initialize the y_displacement
	calculate_z_displacement();			// method called to initialize the z_displacement	
	calculate_x_force();				// method called to initialize the x_force	
	calculate_y_force();				// method called to initialize the y_force	
	calculate_z_force();				// method called to initialize the z_force	
	calculate_resultant_force();			// method called to initialize the resultant force	
	initialise_initial_velocity();			// method called to initialize the initial velocity	
	initialise_final_velocity();			// method called to initialize the final velocity
			
	velocity_verlet_function();

	printf("The updated values of velocity are:\n\n");
	for(row_counter=0;row_counter<NO_OF_PARTICLES;row_counter++)
	{
		for(col_counter=0;col_counter<3;col_counter++)
		printf("%.2f    ",final_velocity[row_counter][col_counter]);
		printf("\n");
	}

	return 0;
}
