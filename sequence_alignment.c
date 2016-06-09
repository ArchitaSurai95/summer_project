#include<stdio.h>
#include<time.h>
#include<string.h>
#include<limits.h>
#define MATCH 1
#define MISMATCH 0
#define GAP 0
int max(int var1,int var2,int var3)
{
	if(var1>var2)
	{
		if(var1>var3)
			return var1;
		else
			return var3;
	}
	else
	{
		if(var2>var3)
			return var2;
		else
			return var3;
	}
}
int main()
{
	char str1[100],str2[100];
	int len1,len2,row_counter,col_counter;	
	printf("Enter sequence 1 and sequence 2:\n");
	scanf("%s %s",str1,str2);
	len1=strlen(str1);
	len2=strlen(str2);
	int dp[len1+1][len2+1];
	for(row_counter=0;row_counter<=len1;row_counter++)
	for(col_counter=0;col_counter<=len2;col_counter++)
	dp[row_counter][col_counter]=0;

	for(row_counter=1;row_counter<=len1;row_counter++)
	for(col_counter=1;col_counter<=len2;col_counter++)
	{
		if(str1[row_counter-1]==str2[col_counter-1])
		dp[row_counter][col_counter]=max(dp[row_counter-1][col_counter-1]+MATCH,dp[row_counter-1][col_counter]+GAP,dp[row_counter]
		[col_counter-1]+GAP);
		else
		dp[row_counter][col_counter]=max(dp[row_counter-1][col_counter-1]+MISMATCH,dp[row_counter-1][col_counter]+GAP,
		dp[row_counter][col_counter-1]+GAP);
	}
	for(row_counter=0;row_counter<=len1;row_counter++)
	{
		for(col_counter=0;col_counter<=len2;col_counter++)
			printf("%d ",dp[row_counter][col_counter]);
		printf("\n");
	}
	return 0;
}
