#include "GA.h"
#include "Matrix.h"
#include <iostream>
#include <climits>

using namespace std;

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
void GA::swapInTable(int* src)
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
int GA::calculateWeight(int* costOfChromosomes, int* weightArray)
{
	int sumOfWeight = 0;
	int maxCost = costOfChromosomes[0];
	for (int i = 1; i < population; i++)
	{
		if (maxCost < costOfChromosomes[i])
			maxCost = costOfChromosomes[i];
	}
	for (int i = 0; i < population; i++)
	{
		weightArray[i] = maxCost - costOfChromosomes[i];
		sumOfWeight += weightArray[i];
	}
	return sumOfWeight;
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

void GA::setSize(int vertex)
{
	size = vertex;
	path = new int[size + 1];

}
void GA::displayPopulation(int **array)
{
	for (int i = 0; i < population; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << array[i][j] << " ";
		}
		cout << endl;
	}
}
void GA::inverionMutation(int* src)
{
	int a = g.generateRandomInt(1, size - 2);
	int b = g.generateRandomInt(a+1, size - 1);
	int temp;
	
	while (a <= b)
	{
		temp = src[a];
		src[a] = src[b];
		src[b] = temp;
		a++;
		b--;
	}
}


void GA::findChromosome(int **matrix)
{
	int minCost = INT_MAX;		//minimalny koszt
	int currentCost;
	int** populationArray;
	int** generationArray;
	int* costOfChromosomes= new int [population];		//poszcegolne koszty chromosomu
	int* weightArray = new int[population];
	int* child = new int[size];
	int costOfAllChromosomes = 0;
	int sumOfWeights, currentWeight;

	int rand;
	int parentA, parentB;

	populationArray = new int* [population];
	generationArray = new int* [population];

	for (int i = 0; i < population; i++)
	{
		populationArray[i] = new int[size];
		generationArray[i] = new int[size];
		
		for (int j = 0; j < size; j++)
		{
			populationArray[i][j] = j;
		}
		shuffle(populationArray[i]);
		currentCost = calculateCost(populationArray[i], matrix);
		costOfChromosomes[i] = currentCost;
		if (currentCost > minCost)
		{
			minCost = currentCost;
			copy(populationArray[i], path);
		}
		
	}


	//petla trwajaca ilosc pokolen
	for (int h = 0; h < L; h++)
	{

		
		//selekcja
		sumOfWeights = calculateWeight(costOfChromosomes, weightArray);
		rand = g.generateRandomInt(0, sumOfWeights);
		currentWeight = 0;

		//wybranie rodzica A
		for (int i = 0; i < population; i++)
		{
			if (rand <= currentWeight)
			{
				parentA = i;
			}
			else
			{
				currentWeight += weightArray[i];
			}
		}

	//wybranie rodzica B
		rand = g.generateRandomInt(0, sumOfWeights);
		currentWeight = 0;
		for (int i = 0; i < population; i++)
		{
			if (rand <= currentWeight)
			{
				parentB = i;
			}
			else
			{
				currentWeight += weightArray[i];
			}
		}
		if (parentB == parentA)
		{
			if (parentB > population - 2)
			{
				parentB--;
			}
			else
			parentB++;
		}
		for (int i = 0; i < population; i++)
		{
			
			//krzyzowanie
			if (g.generateRandomFloat(0, 100) <= crossOverPercent)
			{
				
				if (order)
				{
					orderCrossover(populationArray[parentA], populationArray[parentB], child);
				}
				else
					crossover(populationArray[parentA], populationArray[parentB], child);

				copy(child, generationArray[i]);
				
			}
			else
			{
				
				
				if (costOfChromosomes[parentA] <= costOfChromosomes[parentB])
				{
					copy(populationArray[parentA], generationArray[i]);
				}
				else
				{
					copy(populationArray[parentB], generationArray[i]);
				}
				//copy(populationArray[parentA], generationArray[i]);
			}

			//mutacja
			if (g.generateRandomFloat(0,100) <= mutationPercent)
			{
				if(inversion)
				inverionMutation(generationArray[i]);
				else
				swapInTable(generationArray[i]);
			}

		}

		
		swap(populationArray, generationArray);

		
		for (int i = 0; i < population; i++)
		{
			currentCost = calculateCost(populationArray[i], matrix);
			costOfChromosomes[i] = currentCost;
			if (currentCost < minCost)
			{
				minCost = currentCost;
				copy(populationArray[i], path);
			}
		}

	}

	path[size] = 0;
	cost = minCost;

	delete[] costOfChromosomes;
	delete[] child;
	delete[] weightArray;
	for (int i = 0; i < population; i++)
	{
		delete[] populationArray[i];
		delete[] generationArray[i];
	}
	delete[] populationArray;
	delete[] generationArray;


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
	
	for (int i = 0; i < size; i++)
	{
		std::cout << array[i] << " ";
	}

}

GA::~GA()
{
	delete[]path;
}
void GA::setPopulation(int pop)
{
	population = pop;
}
void GA::setMutationPercent(float mutPercent)
{
	mutationPercent = mutPercent;
}
void GA::setCrossoverPercent(float crosPer)
{
	crossOverPercent = crosPer;
}
void GA::setL(int l)
{
	L = l;
}
int GA::getPopulation()
{
	return population;
}
float GA::getMutationPercent()
{
	return mutationPercent;
}
float GA::getCrossoverPercent()
{
	return crossOverPercent;
}
int GA::getL()
{
	return L;
}
int* GA::getPath()
{
	return path;
}
void GA::changeParametrs(int menu)
{
	int a;
	float percent;
	cout << "podaj wartosc: ";
	switch (menu)
	{
	case 1:
		break;
	case 2:
		cin >> a;
		setPopulation(a);
		break;
	case 3:
		cin >> percent;
		setCrossoverPercent(percent);
		break;
	case 4:
		cin >> percent;
		setMutationPercent(percent);
		break;
	case 5:
		cin >> a;
		setL(a);
		break;
	case 6:
		changeBool(order);
		break;
	case 7:
		changeBool(inversion);
		break;
	default:
		cout << "bledna operacja!" << endl;
		break;
	}




}
void GA::displayParametrs()
{
	cout << "(1) Wykonaj" << endl;
	cout << "(2) Populacja: " << population << endl;
	cout << "(3) Krzyzowanie[%]: " << crossOverPercent << endl;
	cout << "(4) Mutacja[%]: " << mutationPercent << endl;
	cout << "(5) Liczba pokolen: " << L << endl;
	if(order)
	cout << "(6) Krzyzowanie: " <<"Order"<<endl;
	else
	cout << "(6) Krzyzowanie: " << "Standard" << endl;
	if(inversion)
	cout << "(7) Mutacja: " << "Inversion" << endl;
	else
	cout << "(7) Mutacja: " << "Swap" << endl;
}
void GA::setAllParametrs(int pop, float coP, float mutP, int l)
{
	population = pop;
	crossOverPercent = coP;
	mutationPercent = mutP;
	L = l;

}
int GA::getCost()
{
	return cost;
}
void GA::changeBool(bool& type)
{
	type = !type;
}