#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define size 16

int* add(int *a, int *b, int *c)
{
	for(int i=0;i<size;i++)
	c[i]=a[i]+b[i];
	return c;
}

int main()
{
	clock_t begin,end;
	double time_taken;
	int *a,*b,*c,i;
	begin=clock();
	a=(int*)malloc(size*sizeof(int));
	if(a==NULL)
	{
		printf("Error in memory allocation\n");
		exit(1);
	}
	b=(int*)malloc(size*sizeof(int));
	if(b==NULL)
	{
		printf("Error in memory allocation\n");
		exit(1);
	}
	c=(int*)malloc(size*sizeof(int));
	if(c==NULL)
	{
		printf("Error in memory allocation\n");
		exit(1);
	}
	for(i=0;i<size;i++)
	{
		a[i]=1;
		b[i]=i+1;
	}
	c=add(a,b,c);
	for(i=0;i<size;i++)
	printf("%d  ",c[i]);
	printf("\n");
	end=clock();
	time_taken=end-begin;
	printf("The time of execution is : %f\n",time_taken);
	return 0;
}
