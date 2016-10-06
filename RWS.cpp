#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#define n 10
#define cons 63
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
	int i,c_member=0,mating_pool[n],sum=0,x,fitness[n],j,total_fitness=0,chromosome[n][6];
	double select_prob[n],cum_prob[n],r;
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
	//Selection Probablity Generation | Individuals with higher selection probablity are more fit.
	for(i=0;i<n;i++)
		select_prob[i]=(double)fitness[i]/total_fitness;
	//Set cumulative values
	cum_prob[0]=select_prob[0];	
	for(i=1;i<n;i++)
		cum_prob[i]=select_prob[i]+cum_prob[i-1];
	printf("\n---Selection Probablities---\n");
	for(i=0;i<n;i++)
		printf("%0.2lf ",select_prob[i]);
	printf("\n");
	printf("\n---Cumulative Probablities---\n");
	for(i=0;i<n;i++)
		printf("%0.2lf ",cum_prob[i]);
	printf("\n");
	while(c_member<n)
	{
		i=0;
		r=(double)(rand())/RAND_MAX;
		while(r>cum_prob[i])	
			i++;
		mating_pool[c_member]=i;
		c_member++;
	}
	printf("\n---The mating pool is---\n");
	printf("\nIndex Representation Fitness\n");
	for(i=0;i<n;i++)
	{
		printf("  %d\t",mating_pool[i]+1);
		for(j=0;j<6;j++)
			printf("%d",chromosome[mating_pool[i]][j]);
		printf("  \t%d\n",fitness[mating_pool[i]]);
	}
}
