#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void func(int *array)
{
	for(int i=0;i<5;i++)
	array[i]+=1;
}
int main(int argc, char * argv[])
{
	int *array,num[argc-1],i,j,value=0,count1,count2,dummy,len;
	FILE *fd_read[argc-1];
	char c[4]="A",ch='a',a;
	float x,y,z;
	int n=5,arr[2][3]={{11,2,3},{4,5,6}};
	FILE *fd_write;
	array=(int*)malloc(5*sizeof(int));
	for(int i=0;i<5;i++)
	array[i]=1;
	func(array);
	for(int i=0;i<5;i++)
	printf("%d  ",array[i]);
	printf("\n");
	fd_write = fopen("test.xyz","w");
	if(fd_write==NULL)
	{
		printf("error");
		exit(1);
	}
	/*fprintf(fd,"%d\n",n);
	fprintf(fd,"A %d %d %d\n",arr[0][0],arr[0][1],arr[0][2]);
	fprintf(fd,"B %d %d %d\n",arr[1][0],arr[1][1],arr[1][2]);
	printf("done");*/
	
	for(i=0;i<argc-1;i++)
	{
		fd_read[i]=fopen(argv[i+1],"r");
		if(fd_read[i]==NULL)
		{
			printf("error2  %d \n",i);
			exit(1);
		}
	}
	for(i=0;i<argc-1;i++)
	{
		fscanf(fd_read[i],"%d",&num[i]);
		value+=num[i];
		printf("%d \n\n",num[i]);
	}
	printf("\nvalue = %d\n",value);
	for(i=0;i<argc-1;i++)
	fseek(fd_read[i], 0, SEEK_SET );
	//ch=fgetc(fd_read[argc-2]);
	count1=1;count2=0;
	while(1)
	{
		count1=1;count2=0;
		fprintf(fd_write,"%d\n",value);
		
		for(i=0;i<argc-1;i++)
		{
			fscanf(fd_read[i],"%d",&dummy);
			ch=getc(fd_read[i]);
			j=num[i];
			while(j--)
			{
								
				fscanf(fd_read[i],"%c %f %f %f",&ch,&x,&y,&z);
				//printf("%f %f %f \n\n\n",x,y,z);
				ch=getc(fd_read[i]);
				fprintf(fd_write,"%s %f %f %f\n",c,x,y,z);
				len=strlen(c);
				c[len-1]++;
				count1++;
				if(count1==(count2*26+1))
				{
					if(count2==0)   strcpy(c,"A");
					if(count2==1)   strcpy(c,"AA");
					if(count2>1)    c[1]++;
					if(count2==26)	strcpy(c,"AAA");
					if(count2>26)	c[0]++;
				}
				if(count1==((count2+1)*26))
				count2++;		
			}
		}
		ch=fgetc(fd_read[argc-2]);
		if(ch==EOF)
			break;
		else
			fseek(fd_read[argc-2], -sizeof(char), SEEK_CUR);
	}
	printf("done\n");
	return 0;
}
	
