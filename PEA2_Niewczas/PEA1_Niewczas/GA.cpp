#include "GA.h"
#include "Matrix.h"
#include <iostream>
#include <climits>


void GA::shuffle(int* arr)
{
	int k, temp;
	for (int i = 1; i < size; i++)
	{
		temp = arr[i];
		k = g.generateRandomInt(1, size - 1);
		arr[i] = arr[k];
		arr[k] = temp;
	}
}

void GA::init2Darray(int **array)
{
	if (size > 0)
	{
		array = new int* [population]; //tablica wskaŸników
		for (int i = 0; i < size; i++)
		{
			array[i] = new int[size];
		}
	}
}

int GA::calculateCost(int* perm, int** mat)
{
	int cost = 0;
	for (int i = 0; i < size - 1; i++)
	{

		cost += mat[perm[i + 1]][perm[i]];
	}
	cost += mat[perm[0]][perm[size - 1]];
	return cost;
}
int GA::calculateAllChromosomes(int **populationArray, int **mat)
{
	int cost = 0;
	for (int i = 0; i < population; i++)
	{
		cost += calculateCost(populationArray[i], mat);
	}
	return cost;
}

void GA::copy(int* src, int* des)
{
	for (int i = 0; i < size; i++)
	{
		des[i] = src[i];
	}
}


//parA, parB- rodzice, child- potomek
void GA::crossover(int* parA, int* parB, int* child)
{
	int* temp = new int[size];
	int* freq = new int[size];

	for (int i = 0; i < size; i++)
	{
		freq[i] = 0;
	}

	for (int i = 0; i <= size / 2; i++)
	{
		temp[i] = parA[i];
		freq[parA[i]] = 1;
	}
	int k = 0;
	for (int i = size / 2 + 1; i < size; i++)
	{
		while (freq[parB[k]] == 1)
		{
			k++;
		}
		temp[i] = parB[k];
		k++;
	}

	copy(temp, child);
	delete[]temp;
	delete[]freq;
}
void GA::orderCrossover(int* parA, int* parB, int* child)
{
	int* freq = new int[size];
	for (int i = 0; i < size; i++)
	{
		freq[i] = 0;
	}

	int randA, randB;
	randA = g.generateRandomInt(1, size - 2);
	randB = g.generateRandomInt(randA+1, size - 1);
	//std::cout << "A- " << randA << "\n";
	//std::cout << "B- " << randB << "\n";

	for (int i = randA; i <= randB; i++)
	{
		child[i] = parA[i];
		freq[parA[i]] = 1;
	}
	
	int bIndeks = 0;
	for (int i = 0; i < randA; i++)
	{
		//std::cout << i << " ";
		if (freq[parB[bIndeks]] == 0)
		{
			child[i] = parB[bIndeks];
			freq[parB[bIndeks]] = 1;
		}
		else
			i--;
			bIndeks++;
	}

	for (int i = randB + 1; i < size; i++)
	{
		if (freq[parB[bIndeks]] == 0)
		{
			child[i] = parB[bIndeks];
			freq[parB[bIndeks]] = 1;
		}
		else
			i--;
			bIndeks++;
	}

	delete[]freq;
}



void GA::swap(int* src)
{
	int temp;
	int ind1 = g.generateRandomInt(1, size - 1);
	int ind2 = g.generateRandomInt(1, size - 1);
	do
	{
		ind2 = g.generateRandomInt(1, size - 1);
	} while (ind1 == ind2);
	temp=src[ind1];
	src[ind1] = src[ind2];
	src[ind2] = temp;
}

void GA::calculateWeight(int* costOfChromosome,int costOfAllChromosomes, int* weightArray)
{
	int weight = 0;

	for (int i = 0; i < population; i++)
	{
		weightArray[i] = costOfAllChromosomes - costOfChromosome[i];
	}
	
}
int GA::calculateAllWeights(int* weightArray)
{

	int weight = 0;
	for (int i = 0; i < population; i++)
	{
		weight += weightArray[i];
		//std::cout << weight << "\n";
	}
	//std::cout<<"***\n";
	return weight;
}
void GA::swap2DArrays(int** pop, int** gen)
{
	int* temp = new int[size];
	for (int i = 0; i < population; i++)
	{
		copy(pop[i], temp);
		copy(gen[i], pop[i]);
		copy(temp, gen[i]);
	}
	temp = nullptr;
	delete[] temp;

}



void GA::findChromosome(int **array, int vertex)
{
	size = vertex;
	path = new int[size + 1];							//minimalna sciezka
	int minCost;
	int currentCost;
	int sumOfWeight;

	int costOfPopulation= 0;							//koszt calej populacji
	//int numberOfChilds = 0;
	int parentA = 0, parentB = 0;						//chromosomy wykorzystywane do krzyzowek
	
	int* costOfChromosome = new int[population];		//poszczegolne koszty chromosomow
	int* weightArray = new int[population];
	int** populationArray;
	int** generationArray;
	int* child = new int[size];

	//int numberOfCrossOver = (population * crossOverPercent)/100;
	//int numberOfMutation = (population * mutationPercent)/100;



	//inicjalizacja 2d tablic populacji i generacji
	populationArray = new int* [population];
	generationArray= new int* [population]; //tablica wskaŸników
	for (int i = 0; i < population; i++)
	{
		populationArray[i] = new int[size];
		generationArray[i] = new int[size];

		for (int j = 0; j < size; j++)
		{
			populationArray[i][j] = j;
		}
	}
	
	minCost = INT_MAX;

	for (int i = 0; i < population; i++)
	{
		shuffle(populationArray[i]);								//losowe wymieszanie chromosomu
		currentCost= calculateCost(populationArray[i], array);		//koszt chromosomu
		costOfChromosome[i] = currentCost;
			if(currentCost < minCost)
			{
				copy(populationArray[i], path);
				minCost = costOfChromosome[i];
			}
	}
	costOfPopulation = calculateAllChromosomes(populationArray, array);
	calculateWeight(costOfChromosome, costOfPopulation, weightArray);
	sumOfWeight = calculateAllWeights(weightArray);
	int randWeight;
	int currentWeight = 0;
	int rand;
	

	int ilekrzyz = 0;
	int ilemut = 0;
	int ileminuw = 1;

	int L = 10;
	
	for (int h = 0; h < L; h++)
	{

		for(int numberOfChilds=0;numberOfChilds<population; numberOfChilds++)
			{
			//wybor rodzica A
			randWeight = g.generateRandomInt(0, sumOfWeight);

			for (int i = 0; i < population; i++)
			{
			std::cout << sumOfWeight << "\n";
				currentWeight += weightArray[i];
				if (currentWeight >= randWeight)
				{
					parentA = i;
					break;
				}
			
			}
			currentWeight = 0;
			randWeight = g.generateRandomInt(0, sumOfWeight);
			//wybor rodzica B
			for (int i = 0; i < population; i++)
			{
				currentWeight += weightArray[i];
				if (currentWeight >= randWeight)
				{
					parentB = i;
					break;
				}

			}
			//robienie krzyzowek lub kopiowanie rodzica
			

			if (g.generateRandomInt(0, 100)<=crossOverPercent)
			{
				ilekrzyz++;
				orderCrossover(populationArray[parentA], populationArray[parentB], child);
				copy(child, generationArray[numberOfChilds]);
			

			}
			else
			{
				if (costOfChromosome[parentA] > costOfChromosome[parentB])
				{
					copy(populationArray[parentB], generationArray[numberOfChilds]);
				}
				else
					copy(populationArray[parentA], generationArray[numberOfChilds]);

			}
			currentWeight = 0;
		}


		//tworzenie mutacji
		for (int i = 0; i < population; i++)
		{
			if (g.generateRandomInt(0, 100) <= mutationPercent)
			{
			ilemut++;
				swap(generationArray[i]);

			}
		}

		
		swap2DArrays(populationArray, generationArray);


		for (int i = 0; i < population; i++)
		{
			currentCost = calculateCost(populationArray[i], array);		//koszt chromosomu
			costOfChromosome[i] = currentCost;
			if (currentCost < minCost)
			{
				copy(populationArray[i], path);
				minCost = costOfChromosome[i];
				ileminuw++;
			}
		}
		costOfPopulation = calculateAllChromosomes(populationArray, array);
		calculateWeight(costOfChromosome,costOfPopulation, weightArray);
		sumOfWeight = calculateAllWeights(weightArray);

	}


	path[size] = 0;
	cost = minCost;
	std::cout << "***\nkrzyzowek: " << ilekrzyz << "\nmutacji: " << ilemut << "\nminimalnych zamian: " << ileminuw << "\n";

	
	for (int i = 0; i < population; i++)
	{
		delete[] populationArray[i];
		delete[] generationArray[i];
	}

	delete[] child;
	delete[] weightArray;
	delete[] populationArray;
	delete[] generationArray;
	delete[] costOfChromosome;

}
void GA::displaySolution()
{
	std::cout << "path: ";
	for (int i = 0; i < size + 1; i++)
	{
		std::cout << path[i] << " ";
	}
	std::cout << "\ncost: " << cost << std::endl;
}
void GA::displayArray(int* array)
{
	std::cout << "testPath: ";
	for (int i = 0; i < size; i++)
	{
		std::cout << array[i] << " ";
	}

	std::cout << "\n";
}

GA::~GA()
{
	delete[]path;
}