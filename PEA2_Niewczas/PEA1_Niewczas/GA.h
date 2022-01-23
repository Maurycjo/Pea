#pragma once
#include "RandomGenerator.h"


class GA
{
private:

	int population = 1000;			//liczba chromosomow (sciezek)
	float crossOverPercent = 80;		//procent krzyzowek
	float mutationPercent = 5;		//procent mutacji
	int* path;					//najlepsze rozwiazanie
	int cost;
	int size;					//liczba wierzcholkow
	RandomGenerator g;			//obiekt generujacy liczby losowe
	void shuffle(int* arr);		//losowanie chromosomu
	void init2Darray(int **array);
	int calculateCost(int* perm, int** mat);
	int calculateAllChromosomes(int** populationArray, int** mat);
	void crossover(int* parA, int* parB, int* child);
	void copy(int* src, int* des);
	void swap(int* src);
	void displayArray(int* array);
	void calculateWeight(int* costOfChromosome,int costOfAllChromosomes, int* weightArray);
	int calculateAllWeights(int* weightArray);
	void swap2DArrays(int** pop, int** gen);
	void orderCrossover(int* parA, int* parB, int* child);
public:
	void displaySolution();
	void findChromosome(int **array, int vertex);
	~GA();
};

