#include <iostream>
#include <stdio.h>
#include <algorithm>
#define n 10
#define l 6
#define k 5
#define cons 64

using namespace std;
void toBinary(int x,int binary[])
{
	int ind=5;
	while(x!=0)
	{
		binary[ind]=x%2;
		x/=2;
		ind--;
	}
	while(ind>=0)
	{
		binary[ind]=0;
		ind--;
	}
}

int getFitness(int x)
{	
	return x*x;
}


int main()
{
	int i,j,chromosome[n][6],tournament[k],mating_pool[l],ind,x,fitness[n],total_fitness=0,xam;
	srand(time(NULL));
	for(i=0;i<n;i++)
	{
		x=rand()%cons;
		fitness[i]=getFitness(x);
		total_fitness+=fitness[i];
		toBinary(x,chromosome[i]);
		for(j=0;j<6;j++)
			printf("%d",chromosome[i][j]);
		printf(" %d\n",x);
	}
	ind=0;
	for(i=0;i<l;i++)
	{
		printf("\n---Tournament %d---\n",i+1);
		for(j=0;j<k;j++)
		{
			tournament[j]=rand()%n;
			printf("%d ",tournament[j]+1);
		}
		printf("\n");
		xam=0;
		for(j=1;j<k;j++)
			xam=(fitness[tournament[j]]>fitness[tournament[xam]])?j:xam;
		mating_pool[ind++]=tournament[xam];
		printf("Selected-%d\n",mating_pool[ind-1]+1);
	}	
	printf("\n---The mating pool is---\n");
	printf("\nIndex Representation Fitness\n");
	for(i=0;i<l;i++)
	{
		printf("  %d\t",mating_pool[i]+1);
		for(j=0;j<6;j++)
			printf("%d",chromosome[mating_pool[i]][j]);
		printf("  \t%d\n",fitness[mating_pool[i]]);
	}
	return 0;
}	














