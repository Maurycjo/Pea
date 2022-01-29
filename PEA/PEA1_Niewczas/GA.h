#pragma once
#include "RandomGenerator.h"

#pragma once
#include "RandomGenerator.h"


class GA
{
private:

	bool inversion =true;
	bool order = true;
	int population = 1000;			//liczba chromosomow (sciezek)
	float crossOverPercent = 40;		//procent krzyzowek
	float mutationPercent = 10;		//procent mutacji
	int L = 10000;				//liczba pokolen
	int* path;					//najlepsze rozwiazanie
	int cost;
	int size;					//liczba wierzcholkow
	RandomGenerator g;			//obiekt generujacy liczby losowe
	void shuffle(int* arr);		//losowanie chromosomu
	int calculateCost(int* perm, int** mat);
	void crossover(int* parA, int* parB, int* child);
	void copy(int* src, int* des);
	void swapInTable(int* src);
	void displayArray(int* array);
	//okreslenie wagi na podstawie oddalenie od najgorszego chromosomu
	int calculateWeight(int* costOfChromosome, int* weightArray);
	void inverionMutation(int* src);
	void swap2DArrays(int** pop, int** gen);
	void orderCrossover(int* parA, int* parB, int* child);
	void displayPopulation(int **matrix);
	void changeBool(bool& type);

public:
	void displaySolution();
	void findChromosome(int** array);
	~GA();
	void setSize(int vertex);
	void setPopulation(int pop);
	void setMutationPercent(float mutPercent);
	void setCrossoverPercent(float crosPer);
	void setL(int l);
	int getPopulation();
	float getMutationPercent();
	float getCrossoverPercent();
	int getL();
	int* getPath();
	void changeParametrs(int menu);
	void displayParametrs();
	void setAllParametrs(int pop, float coP, float mutP, int l);
	int getCost();


};
