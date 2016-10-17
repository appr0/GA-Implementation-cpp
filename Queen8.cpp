/*
8-Queen Problem Implementation.
Population Size=200
Fitness Function=1/(2+x^2),x is the total number of conflicts
Chromosome Length=8,each index(0-7) represents a row and each element(1-8)represents the column of the queens
Position Mapped Crossover and Swap Mutation are used.
Terminating Condition-either we have got a solution or reached the 200th generation
*/

#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define n 8
#define eps 2
#define pm 0.8

using namespace std;

double getFitness(int chromosome[])
{
	int collisions=0,j,x,y,k;
	for(j=0;j<n;j++)
	{
		x=j;
		y=chromosome[j];
		for(k=1;k<n;k++)
		{
			if(x+k>=n||y+k>=n)
				;
			else if(chromosome[x+k]==y+k)						
				collisions++;			
			if(x+k>=n||y-k<0)
				;
			else if(chromosome[x+k]==y-k)						
				collisions++;				
		}
	}	
	return (1/((double)eps+collisions));	
}

void swap(int c[],int i,int j)
{
	int temp=c[i];
	c[i]=c[j];
	c[j]=temp;
}
//Selection in mating pool.Total=10
void selection(int mating_pool[][8],int chromosome[][8],double fitness[],int population_size)
{
	int j,a[10],ind,xam,k;
	for(j=0;j<10;j+=2)
	{
		a[0]=rand()%population_size;
		xam=0;
		for(k=1;k<5;k++)
		{
			a[k]=rand()%population_size;
			if(fitness[k]>fitness[a[xam]])
				xam=k;
		}
		ind=xam;		
		for(k=0;k<n;k++)
			mating_pool[j][k]=chromosome[a[xam]][k];
		if(xam==0)
			xam=1;
		else
			xam=0;
		for(k=0;k<5;k++)
			if(k!=ind&&fitness[k]>fitness[a[xam]])
				xam=k;
		for(k=0;k<n;k++)
			mating_pool[j+1][k]=chromosome[a[xam]][k];
	}
}

//Position mapped Crossover(PMX)
void crossover(int mating_pool[][8],int chromosome[200][8],int population_size)
{
	int j,k,count,x,y,ind,parent1,parent2,l,vis1[n],vis2[n];
	for(j=0;j<population_size;j++)
	{
		count=0;
		//Parents Selection from mating pool randomly
		parent1=rand()%10;
		parent2=rand()%10;
		x=rand()%n;
		y=rand()%n;
		ind=max(x,y);
		x=min(x,y);	
		y=ind;
		for(k=0;k<n+1;k++)
			vis1[k]=vis2[k]=0;
		for(k=x;k<=y;k++)
		{
			chromosome[j][k]=mating_pool[parent1][k];
			vis1[mating_pool[parent1][k]]=1;
			chromosome[j+1][k]=mating_pool[parent2][k];
			vis2[mating_pool[parent2][k]]=1;
		}
		//For the 1st of 2 children
		for(k=x;k<=y;k++)
		{
			ind=k;
			while(vis1[mating_pool[parent2][k]]!=1)
			{
				for(l=0;l<=n;l++)
					if(mating_pool[parent1][ind]==mating_pool[parent2][l])
						break;
				if(l<=y&&l>=x)
					ind=l;
				else
				{
					chromosome[j][l]=mating_pool[parent2][k];
					vis1[mating_pool[parent2][k]]=1;	
				}	
			}	
		}
		for(k=0;k<n;k++)
			if(vis1[mating_pool[parent2][k]]==0)
				chromosome[j][k]=mating_pool[parent2][k];
		//For the 2nd of 2 children
		j++;
		for(k=x;k<=y;k++)
		{
			ind=k;
			while(vis2[mating_pool[parent1][k]]!=1)
			{
				for(l=0;l<=n;l++)
					if(mating_pool[parent2][ind]==mating_pool[parent1][l])
						break;
				if(l<=y&&l>=x)
					ind=l;
				else
				{
					chromosome[j][l]=mating_pool[parent1][k];
					vis2[mating_pool[parent1][k]]=1;	
				}	
			}	
		}
		for(k=0;k<n;k++)
			if(vis2[mating_pool[parent1][k]]==0)
				chromosome[j][k]=mating_pool[parent1][k];
	}
	return;
}

//Swap Mutation
void mutation(int chromosome[][8],int population_size)
{
	double mutation_value[n];
	int i,j;
	for(i=0;i<population_size;i++)
	{
		for(j=0;j<n;j++)
		mutation_value[j]=((double)rand())/RAND_MAX;

		for(j=0;j<n-1;j++)
			if(mutation_value[j]>=pm&&mutation_value[j+1]>=pm)
				swap(chromosome[i],j,j+1);
	}
}
int main()
{
	int i,j,r,k,gen_count=200,population_size=200,found=-1,mating_pool[10][n],chromosome[200][n],temp[n];
	double fitness[200];
	srand(time(NULL));
	printf("8-Queen Problem Solution!Fitness Function:1/(2+conflicts)\n");
	//Initial Population Generation
	for(i=0;i<n;i++)
	{
		chromosome[0][i]=i+1;
		temp[i]=i+1;
	}
	for(i=1;i<population_size;i++)
	{
		for(j=0;j<n;j++)
		{
			r=rand()%(n-j);
			chromosome[i][j]=temp[r];
			for(k=r;k<n-j-1;k++)
				temp[k]=temp[k+1];
		}
		for(j=0;j<n;j++)
			temp[j]=j+1;
	}
	//Get the fitness value and display  all chromosomes.
	printf("----Initial Population----\n\n");
	for(i=0;i<population_size;i++)
	{
		for(j=0;j<n;j++)
			printf("%d",chromosome[i][j]);
		fitness[i]=getFitness(chromosome[i]);	
		printf(" %0.5lf\n",fitness[i]);
		if(fitness[i]==((double)1)/2)
			found=i;
	}
	for(i=1;i<gen_count&&found<0;i++)
	{
		//Mating pool selection.Randomly select 5 and get the best 2 among them. Total=10

		selection(mating_pool,chromosome,fitness,population_size);

		//Crossover

		crossover(mating_pool,chromosome,population_size);

		//Mutation

		mutation(chromosome,population_size);

		printf("\n---Generation %d---\n\n",i+1);
		for(j=0;j<population_size;j++)
		{
			for(k=0;k<n;k++)
				printf("%d",chromosome[j][k]);
			fitness[j]=getFitness(chromosome[j]);			
			printf(" %0.5lf\n",fitness[j]);	
			if(fitness[i]==((double)1)/2)
				found=i;
		}			
	}
	if(found>=0)
	{
		printf("\nFound a solution :)\n");
		for(j=0;j<n;j++)
			printf("%d",chromosome[found][j]);
	}
	else
		printf("\nUnable to find the solution! :( \n");
	return 0;
}
