/* Dimensions of the defined cube: 10x10x10
   co-ordinates of all the vertices of the cube: {(0,0,0),(10,0,0),(0,10,0),(10,10,0),(0,0,10),(0,10,10),(10,0,10),(10,10,10)}
*/ 

/* Assumptions:
1) All particles are point mass particles.
2) No external force acts on the system.
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

#define G 0.6673
#define NO_OF_PARTICLES 5
#define NO_OF_STEPS 500
#define STEP_SIZE .05
#define DIMENSION 10
#define R_CUT 2
#define R_COLLISION 2

float co_ordinates[NO_OF_PARTICLES][3],temp[3];
int mass[NO_OF_PARTICLES];
float x_displacement[NO_OF_PARTICLES][NO_OF_PARTICLES],y_displacement[NO_OF_PARTICLES][NO_OF_PARTICLES],
z_displacement[NO_OF_PARTICLES][NO_OF_PARTICLES];
float x_force[NO_OF_PARTICLES][NO_OF_PARTICLES],y_force[NO_OF_PARTICLES][NO_OF_PARTICLES],
z_force[NO_OF_PARTICLES][NO_OF_PARTICLES],resultant_force[NO_OF_PARTICLES][3];
float velocity[NO_OF_PARTICLES][3];

FILE *fd;


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


/** Method to check initial displacement between the particles
  * modifies contents of array storing the initial_displacement
  * return 1 if the generated co-ordinates are possible for the exixtence of a particle
  * else return -1
*/
int check_displacement(int counter)
{
	int iterator,flag;
	float x1,x2,y1,y2,z1,z2,r;
	if(counter==0) 
	{
		flag=1;
		return flag;
	}
	x1=temp[0];
	y1=temp[1];
	z1=temp[2];
	for(iterator=0;iterator<counter;iterator++)
	{
		x2=co_ordinates[iterator][0];
		y2=co_ordinates[iterator][1];
		z2=co_ordinates[iterator][2];
		r=((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2))+((z1-z2)*(z1-z2));
		if(r<(R_COLLISION*R_COLLISION))
		{
			flag=0;
			return flag;
		}
	}
	flag=1;
	return flag;
}


/** Method to generate random co-ordinates for the particles
  * modifies contents of the array storing the co-ordinates (2D array)
*/
void generate_random_coordinates()
{
	int counter,col_counter,flag;
	time_t timer;	
	srand((unsigned) time(&timer));			//initializing the random number generator

	/* loop to generate random x,y and z co-ordinates of the particles */
	for(counter=0;counter<NO_OF_PARTICLES;counter++)
	{		
		for(col_counter=0;col_counter<3;col_counter++)
		temp[col_counter]=((rand()%(DIMENSION-1))+1);
		flag=check_displacement(counter);
		if(flag)
		{
			for(col_counter=0;col_counter<3;col_counter++)			
			co_ordinates[counter][col_counter]=temp[col_counter];
		}
		else
		{
			while(flag!=1)
			{
				for(col_counter=0;col_counter<3;col_counter++)
				temp[col_counter]=((rand()%(DIMENSION-1))+1);
				flag=check_displacement(counter);
			}
			for(col_counter=0;col_counter<3;col_counter++)			
			co_ordinates[counter][col_counter]=temp[col_counter];
		}
	}

	/*for(counter=0;counter<NO_OF_PARTICLES;counter++)
	{
		for(col_counter=0;col_counter<3;col_counter++)
		{
			scanf("%f",&co_ordinates[counter][col_counter]);
		}
		printf("\n");
	}*/

	/* loop to display the value of the generated co-ordinates of the particles */
	printf("The value of the generated co-ordinates:\n");
	for(counter=0;counter<NO_OF_PARTICLES;counter++)
	{
		for(col_counter=0;col_counter<3;col_counter++)
		{
			printf("%.3f ",co_ordinates[counter][col_counter]);
		}
		printf("\n");
	}	
}


/* method to handle collision between two particles */
void collision_of_particles(int row_counter, int col_counter)
{
	float xu1,xu2,xv1,xv2,yu1,yu2,yv1,yv2,zu1,zu2,zv1,zv2;
	int m1,m2;
	m1=mass[row_counter];
	m2=mass[col_counter];

	xu1=velocity[row_counter][0];
	xu2=velocity[col_counter][0];

	yu1=velocity[row_counter][1];
	yu2=velocity[col_counter][1];

	zu1=velocity[row_counter][2];
	zu2=velocity[col_counter][2];

	xv1=(xu1*(m1-m2)+2*(m2*xu2))/(m1+m2);
	xv2=(xu2*(m2-m1)+2*(m1*xu1))/(m1+m2);
	velocity[row_counter][0]=xv1;
	velocity[col_counter][0]=xv2;

	yv1=(yu1*(m1-m2)+2*(m2*yu2))/(m1+m2);
	yv2=(yu2*(m2-m1)+2*(m1*yu1))/(m1+m2);
	velocity[row_counter][1]=yv1;
	velocity[col_counter][1]=yv2;

	zv1=(zu1*(m1-m2)+2*(m2*zu2))/(m1+m2);
	zv2=(zu2*(m2-m1)+2*(m1*zu1))/(m1+m2);
	velocity[row_counter][2]=zv1;
	velocity[col_counter][2]=zv2;
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

	/* loop to display the displacement in x direction between the particles 	
	printf("The values of the corresponding displacements in x direction:\n");
	for(row_counter=0;row_counter<NO_OF_PARTICLES;row_counter++)
	{
		for(col_counter=0;col_counter<NO_OF_PARTICLES;col_counter++)
		{
			printf("%.2f     ",x_displacement[row_counter][col_counter]); 				
		}
		printf("\n");
	}*/	
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

	/* loop to display the displacement in y direction between the particles 	
	printf("The values of the corresponding displacements in y direction:\n");
	for(row_counter=0;row_counter<NO_OF_PARTICLES;row_counter++)
	{
		for(col_counter=0;col_counter<NO_OF_PARTICLES;col_counter++)
		{
			printf("%.2f     ",y_displacement[row_counter][col_counter]); 				
		}
		printf("\n");
	}*/	
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

	/* loop to display the displacement in z direction between the particles 	
	printf("The values of the corresponding displacements in z direction:\n");
	for(row_counter=0;row_counter<NO_OF_PARTICLES;row_counter++)
	{
		for(col_counter=0;col_counter<NO_OF_PARTICLES;col_counter++)
		{
			printf("%.2f     ",z_displacement[row_counter][col_counter]); 				
		}
		printf("\n");
	}*/	
}



/** Method to calculate the force between the particles acting along x direction
  * modifies contents of the array storing the x_force (2D array)
  */
void calculate_x_force()
{
	int row_counter,col_counter;
	float r,r1,r2;							// stores distance between the particles
	int m1,m2;							// stores mass of the two interacting particles;
	for(row_counter=0;row_counter<NO_OF_PARTICLES;row_counter++)
	{
		for(col_counter=0;col_counter<NO_OF_PARTICLES;col_counter++)
		{
			if(row_counter==col_counter)
				x_force[row_counter][col_counter]=0;
			else
			{
				r1=co_ordinates[row_counter][0];
				r2=co_ordinates[col_counter][0];				
				r=x_displacement[row_counter][col_counter];
				m1=mass[row_counter];
				m2=mass[col_counter];
				if(r<R_CUT)
				{
					x_force[row_counter][col_counter]=0;
					//collision_of_particles(row_counter,col_counter,0);
				}
				else
				x_force[row_counter][col_counter]=((G*m1*m2)/(r*r));
				if(r1>r2)
				x_force[row_counter][col_counter]=-x_force[row_counter][col_counter];
				
			}
		}
	}

	/* loop to display the force between the particles in x direction 
	printf("The values of the corresponding forces in x direction(of the order of 10^-11 N) :\n");
	for(row_counter=0;row_counter<NO_OF_PARTICLES;row_counter++)
	{
		for(col_counter=0;col_counter<NO_OF_PARTICLES;col_counter++)
		{
			printf("%.2f     ",x_force[row_counter][col_counter]); 				
		}
		printf("\n");
	}*/
}


/** Method to calculate the force between the particles acting along y direction
  * modifies contents of the array storing the y_force (2D array)
  */
void calculate_y_force()
{
	int row_counter,col_counter;
	float r,r1,r2;							// stores distance between the particles
	int m1,m2;							// stores mass of the two interacting particles;
	for(row_counter=0;row_counter<NO_OF_PARTICLES;row_counter++)
	{
		for(col_counter=0;col_counter<NO_OF_PARTICLES;col_counter++)
		{
			if(row_counter==col_counter)
				y_force[row_counter][col_counter]=0;
			else
			{
				r1=co_ordinates[row_counter][1];
				r2=co_ordinates[col_counter][1];
				r=y_displacement[row_counter][col_counter];
				m1=mass[row_counter];
				m2=mass[col_counter];
				if(r<R_CUT)
				{
					y_force[row_counter][col_counter]=0;
					//collision_of_particles(row_counter,col_counter,1);
				}
				else
				y_force[row_counter][col_counter]=((G*m1*m2)/(r*r));
				if(r1>r2)
				y_force[row_counter][col_counter]=-y_force[row_counter][col_counter];
				
			}
		}
	}

	/* loop to display the force between the particles in y direction 
	printf("The values of the corresponding forces in y direction(of the order of 10^-11 N) :\n");
	for(row_counter=0;row_counter<NO_OF_PARTICLES;row_counter++)
	{
		for(col_counter=0;col_counter<NO_OF_PARTICLES;col_counter++)
		{
			printf("%.2f     ",y_force[row_counter][col_counter]); 				
		}
		printf("\n");
	}*/
}


/** Method to calculate the force between the particles acting along z direction
  * modifies contents of the array storing the z_force (2D array)
  */
void calculate_z_force()
{
	int row_counter,col_counter;
	float r,r1,r2;							// stores distance between the particles
	int m1,m2;							// stores mass of the two interacting particles;
	for(row_counter=0;row_counter<NO_OF_PARTICLES;row_counter++)
	{
		for(col_counter=0;col_counter<NO_OF_PARTICLES;col_counter++)
		{
			if(row_counter==col_counter)
				z_force[row_counter][col_counter]=0;
			else
			{
				r1=co_ordinates[row_counter][2];
				r2=co_ordinates[col_counter][2];
				r=z_displacement[row_counter][col_counter];
				m1=mass[row_counter];
				m2=mass[col_counter];
				if(r<R_CUT)
				{
					z_force[row_counter][col_counter]=0;
					//collision_of_particles(row_counter,col_counter,2);
				}
				else
				z_force[row_counter][col_counter]=((G*m1*m2)/(r*r));
				if(r1>r2)
				z_force[row_counter][col_counter]=-z_force[row_counter][col_counter];
				
			}
		}
	}

	/* loop to display the force between the particles in z direction 
	printf("The values of the corresponding forces in z direction(of the order of 10^-11 N) :\n");
	for(row_counter=0;row_counter<NO_OF_PARTICLES;row_counter++)
	{
		for(col_counter=0;col_counter<NO_OF_PARTICLES;col_counter++)
		{
			printf("%.2f     ",z_force[row_counter][col_counter]); 				
		}
		printf("\n");
	}*/
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

	/* loop to display the resultant force acting on the particles 
	printf("The resultant force on the particles are (of the order of 10^-11 N) :\n");
	for(row_counter=0;row_counter<NO_OF_PARTICLES;row_counter++)
	{
		printf("%.2f i  %.2f j  %.2f k",resultant_force[row_counter][0],
		resultant_force[row_counter][1],resultant_force[row_counter][2]);
		printf("\n");
	}*/
}


/** Method to initialise the velocity of the particles
  * modifies contents of the array storing the velocity (1D array)
*/
void initialise_velocity()
{
	int row_counter,col_counter;
	for(row_counter=0;row_counter<NO_OF_PARTICLES;row_counter++)
	for(col_counter=0;col_counter<3;col_counter++)
	velocity[row_counter][col_counter]=0;
}

/* method to write the co-ordinates in a .xyz file */
void write_xyz_file()
{
	int counter;
	
	fprintf(fd,"%d\n",NO_OF_PARTICLES);
	for(counter=0;counter<NO_OF_PARTICLES;counter++)
	{
		fprintf(fd,"%c %.3f %.3f %.3f\n",(65+counter),co_ordinates[counter][0],co_ordinates[counter][1],co_ordinates[counter][2]);
	}
}


/** Method to calculate the velocity and co-ordinates of the particles after every time step
  * modifies contents of the array storing the velocity, force, resultant force, co-ordinates, distance.
  * returns: void
*/
void velocity_verlet_function()
{
	int counter,step_counter,row_counter,col_counter;
	float x1,x2,y1,y2,z1,z2,r;
	for(step_counter=0;step_counter<NO_OF_STEPS;step_counter++)
	{	
		for(counter=0;counter<NO_OF_PARTICLES;counter++)
		velocity[counter][0]=velocity[counter][0]+((resultant_force[counter][0]*STEP_SIZE)/(2*mass[counter]));

		for(counter=0;counter<NO_OF_PARTICLES;counter++)
		velocity[counter][1]=velocity[counter][1]+((resultant_force[counter][1]*STEP_SIZE)/(2*mass[counter]));

		for(counter=0;counter<NO_OF_PARTICLES;counter++)
		velocity[counter][2]=velocity[counter][2]+((resultant_force[counter][2]*STEP_SIZE)/(2*mass[counter]));
		/*printf("velocity\n");
		for(row_counter=0;row_counter<NO_OF_PARTICLES;row_counter++)
		{
		for(col_counter=0;col_counter<3;col_counter++)
		printf("%.2f    ",velocity[row_counter][col_counter]);
		printf("\n");
		}*/

		for(counter=0;counter<NO_OF_PARTICLES;counter++)
		{
		co_ordinates[counter][0]=co_ordinates[counter][0]+(velocity[counter][0]*STEP_SIZE);
		if(co_ordinates[counter][0]>DIMENSION)
		{
			co_ordinates[counter][0]=DIMENSION-(co_ordinates[counter][0]-DIMENSION);
			velocity[counter][0]=-velocity[counter][0];
		}
		if(co_ordinates[counter][0]<0)
		{
			co_ordinates[counter][0]=abs(co_ordinates[counter][0]);
			velocity[counter][0]=abs(velocity[counter][0]);
		}
		}

		for(counter=0;counter<NO_OF_PARTICLES;counter++)
		{
		co_ordinates[counter][1]=co_ordinates[counter][1]+(velocity[counter][1]*STEP_SIZE);
		if(co_ordinates[counter][1]>DIMENSION)
		{
			co_ordinates[counter][1]=DIMENSION-(co_ordinates[counter][1]-DIMENSION);
			velocity[counter][1]=-velocity[counter][1];
		}
		if(co_ordinates[counter][1]<0)
		{
			co_ordinates[counter][1]=abs(co_ordinates[counter][1]);
			velocity[counter][1]=abs(velocity[counter][1]);
		}
		}

		for(counter=0;counter<NO_OF_PARTICLES;counter++)
		{
		co_ordinates[counter][2]=co_ordinates[counter][2]+(velocity[counter][2]*STEP_SIZE);
		if(co_ordinates[counter][2]>DIMENSION)
		{
			co_ordinates[counter][2]=DIMENSION-(co_ordinates[counter][2]-DIMENSION);
			velocity[counter][2]=-velocity[counter][2];
		}
		if(co_ordinates[counter][2]<0)
		{
			co_ordinates[counter][2]=abs(co_ordinates[counter][2]);
			velocity[counter][2]=abs(velocity[counter][2]);
		}
		}

		for(row_counter=0;row_counter<NO_OF_PARTICLES;row_counter++)
		{
			for(col_counter=row_counter+1;col_counter<NO_OF_PARTICLES;col_counter++)
			{
				x1=co_ordinates[row_counter][0];
				x2=co_ordinates[col_counter][0];

				y1=co_ordinates[row_counter][1];
				y2=co_ordinates[col_counter][1];	

				z1=co_ordinates[row_counter][2];
				z2=co_ordinates[col_counter][2];

				r=((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2))+((z1-z2)*(z1-z2));
				//r=sqrt(r);
				if(r<(R_COLLISION*R_COLLISION))
				{//printf("collision\n\n\n%d\n\n\n",step_counter);
				collision_of_particles(row_counter,col_counter);
				}
			}
		}

		write_xyz_file();

		calculate_x_displacement();
		calculate_y_displacement();
		calculate_z_displacement();


		calculate_x_force();
		calculate_y_force();
		calculate_z_force();
 
		calculate_resultant_force();

		for(counter=0;counter<NO_OF_PARTICLES;counter++)
		velocity[counter][0]=velocity[counter][0]+((resultant_force[counter][0]*STEP_SIZE)/(2*mass[counter]));

		for(counter=0;counter<NO_OF_PARTICLES;counter++)
		velocity[counter][1]=velocity[counter][1]+((resultant_force[counter][1]*STEP_SIZE)/(2*mass[counter]));

		for(counter=0;counter<NO_OF_PARTICLES;counter++)
		velocity[counter][2]=velocity[counter][2]+((resultant_force[counter][2]*STEP_SIZE)/(2*mass[counter]));


	}
}	
	

/* Driver function for all the above methods */
int main()
{
	
	int row_counter,col_counter;

	fd = fopen("result1.xyz","w");
	if(fd==NULL)
	{
		printf("Error in opening file\n");
		exit(1);
	}

	generate_random_coordinates();			// method called to generate co-ordinates
	write_xyz_file();
	initialise_mass_of_particles();			// method called to initialise the mass of the particles
	calculate_x_displacement();			// method called to initialize the x_displacement
	calculate_y_displacement();			// method called to initialize the y_displacement
	calculate_z_displacement();			// method called to initialize the z_displacement	
	calculate_x_force();				// method called to initialize the x_force	
	calculate_y_force();				// method called to initialize the y_force	
	calculate_z_force();				// method called to initialize the z_force	
	calculate_resultant_force();			// method called to initialize the resultant force		
	initialise_velocity();				// method called to initialize the velocity
			
	velocity_verlet_function();			// method called to keep track of change in velocity

	printf("The updated values of velocity are:\n\n");
	for(row_counter=0;row_counter<NO_OF_PARTICLES;row_counter++)
	{
		for(col_counter=0;col_counter<3;col_counter++)
		printf("%.2f    ",velocity[row_counter][col_counter]);
		printf("\n");
	}
	fclose(fd);
	return 0;
}
