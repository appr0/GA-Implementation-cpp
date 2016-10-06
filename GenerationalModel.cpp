#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define mp 0.25
#define cp 1
#define cons 64

using namespace std;

void toBinary(int n,int binary[])
{
	int ind=5;
	while(n!=0)
	{
		binary[ind]=n%2;
		n/=2;
		ind--;
	}
	while(ind>=0)
	{
		binary[ind]=0;
		ind--;
	}
}
int toDecimal(int a[])
{
	int n=0;
	for(int i=5;i>=0;i--)
		n+=a[i]*pow(2,5-i);
	return n;

}
int getFitness(int n)
{	
	return n*n*n;
}

int main()
{
	int gen_count=4,population_size=5,fitness[5],chromosome[5][6],most_fit[4],least_fit[4],mating_pool[5][6];
	int i,j,exp_count=0,total_fitness,ind,c1,c2,temp,k,n;
	double mut_val;
	srand(time(NULL));
	for(i=0;i<gen_count;i++)
	{
		most_fit[i]=INT_MIN;
		least_fit[i]=INT_MAX;
	}
	//First Generation produced randomly
	total_fitness=0;
	cout<<"Generation 1\n";
	for(j=0;j<population_size;j++)
	{
		n=rand()%cons;
		fitness[j]=getFitness(n);
		total_fitness+=fitness[j];
		most_fit[0]=max(most_fit[0],fitness[j]);
		least_fit[0]=min(least_fit[0],fitness[j]);
		toBinary(n,chromosome[j]);
		for(k=0;k<=5;k++)
			printf("%d",chromosome[j][k]);
		printf(" %d\n",n);
	}
	for(i=1;i<gen_count;i++)
	{
		cout<<"\nGeneration"<<i+1<<endl;
		ind=0;
		//Selection in mating pool
		for(j=0;j<population_size;j++)
		{
			exp_count=round(((fitness[j]*1.0)/total_fitness)*population_size);
			while(exp_count--)
			{
				k=0;
				while(k<6)
				{
					mating_pool[ind][k]=chromosome[j][k];
					k++;
				}
				ind++;
				if(ind>=population_size)
					break;
			}
			if(ind>=population_size)
				break;		
		}
		if(ind<population_size)
		{
			while(ind<population_size)
			{
				for(k=0;k<6;k++)
					mating_pool[ind][k]=chromosome[rand()%5][k];
				ind++;
			}		
		}
		total_fitness=0;
		
		//Apply Crossover|Crossover Probablity is 1
		ind=0;
		c1=rand()%population_size;
		c2=(c1+1)%population_size;
		for(j=0;j<3;j++)
		{
			k=rand()%5;		   //Generate Random index after which values would be swapped mod 5 to swap atleast 1 value
			for(int x=0;x<=k;x++)
			{
				chromosome[ind][x]=mating_pool[c1][x];
				if(j==2)
					break;
				chromosome[ind+1][x]=mating_pool[c2][x];
			}			
			for(int x=k+1;x<6;x++)		   //Index for a chromosome varies from 0-5
			{
				chromosome[ind][x]=mating_pool[c2][x];
				if(j==2)
					break;
				chromosome[ind+1][x]=mating_pool[c1][x];		
			}
			ind+=2;
			c1=rand()%population_size;
			c2=(c1+1)%population_size;
		}
		//Apply Mutation
		for(j=0;j<population_size;j++)
		{
			mut_val= (double)(rand())/RAND_MAX;
			if(mut_val<=mp)
			{
				k=rand()%6;
				if(chromosome[j][k]==1)
					chromosome[j][k]=0;
				else
					chromosome[j][k]=1;
			}
			//Compute the required values
			n=toDecimal(chromosome[j]);
			fitness[j]=getFitness(n);
			total_fitness+=fitness[j];
			most_fit[i]=max(most_fit[i],fitness[j]);
			least_fit[i]=min(least_fit[i],fitness[j]);
			for(k=0;k<=5;k++)
				cout<<chromosome[j][k];
			cout<<" "<<n;
			cout<<endl;
		}				
	}
	cout<<"Generation-Most Fit  Least Fit\n";
	for(i=0;i<gen_count;i++)
		printf("%d\t   %d\t%d\n",i+1,most_fit[i],least_fit[i]);
	return 0;
}






