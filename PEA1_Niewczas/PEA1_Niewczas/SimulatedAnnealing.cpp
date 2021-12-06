
#include "SimulatedAnnealing.h"


int SimulatedAnnealing::calculateCost(int *perm, Matrix mat)
{
	int cost = 0;
	for (int i = 0; i < size -1; i++)
	{
		cost += mat.array[perm[i]][perm[i + 1]];
	}
	return cost;
}
float SimulatedAnnealing::calculateTemp(int startCost, float alpha)
{
	return startCost*alpha;
}
void SimulatedAnnealing::neigbourPermutation(int* src, int* des)
{
	int temp;
	int ind1 = generateRandomInt(0, size- 1);
	int ind2 = generateRandomInt(0, size - 1);
	do
	{
		ind2 = generateRandomInt(0, size - 1);
	} while (ind1 == ind2);

	copy(src, des);
	des[ind1] = src[ind2];
	des[ind2] = src[ind1];

}
float SimulatedAnnealing::reduceTempGeo(float temp, float alpha)
{
	return alpha * temp;
}


void SimulatedAnnealing::copy(int* src, int* des)
{
	for (int i = 0; i < size; i++)
	{
		des[i] = src[i];
	}
}

void  SimulatedAnnealing::setSize(Matrix matrix)
{
	size = matrix.getVertex();
}

void SimulatedAnnealing::findPath(Matrix matrix)
{
	
	float temp;							//temperatura
	int minCost;						//koszt minimalny
	int costDiff, currentCost, neigCost;//koszty sciezek
	int x;								//liczba losowa z zakresu (0,1)

	//inicjacja tablic
	path = new int[size];
	int* minPath = new int[size];
	int* neighbour = new int[size];

	//permutacja poczatkowa {0, 1, 2, ..., n}
	for (int i = 0; i < matrix.getVertex(); i++)
	{
		path[i] = i;
		minPath[i] = i;
	}
	minCost=calculateCost(path, matrix);
	

	temp=calculateTemp(minCost, ALPHA); //ustawienie poczatkowej temperatury

	for (int i = 0; i < L; i++)
	{
		
		neigbourPermutation(path, neighbour);
		currentCost = calculateCost(path, matrix);
		neigCost = calculateCost(neighbour, matrix);
		costDiff = currentCost - neigCost;

		//ustawianie minimalnego kosztu na wypadek wyjscia z minimum lokalnego
		if (neigCost < minCost)
		{
			minCost = neigCost;
			copy(neighbour, minPath);
		}

		if (costDiff < 0)
		{
			currentCost = neigCost;
			copy(neighbour, path);
		}
		else
		{
			
		}





	}




}
