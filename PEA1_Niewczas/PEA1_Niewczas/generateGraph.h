#pragma once
#include "Matrix.h"
#include <ctime>
#include <cstdlib>
#include <random>

const int minWeight = 1;
const int maxWeight = 100;

int generateRandom(int a, int b)
{

	std::random_device rd; // non-deterministic generator
	std::mt19937 gen(rd()); // random engine seeded with rd()
	//uniform_int_distribution<> dist(-2147483648, 2147483647); // distribute results between	
	std::uniform_int_distribution<> dist(a, b);
	return dist(gen);
}

void Matrix::directedGraph(int quantity)
{
	if (array != NULL)
		deinit();
	init(quantity);
	clean();
	edges = vertex * (vertex - 1);		//maksymalna ilosc krawedzi w grafie skierowanym
	
	for (int i = 0; i < vertex; i++)
	{

		//wartosci losowe w tablicy
		for (int j = 0; j < vertex; j++)
		{
			if (i != j)
				array[i][j] = generateRandom(minWeight, maxWeight);
			else
				array[i][j] = 9999;
		}
	}



}