
#include "SimulatedAnnealing.h"

const double EULER= 2.71828182845904523536;
int SimulatedAnnealing::calculateCost(int *perm, int** mat)
{
	int cost = 0;
	for (int i = 0; i < size -1; i++)
	{

		//std::cout << mat.array[perm[i]][perm[i + 1]] << std::endl;
		cost += mat[perm[i+1]][perm[i]];
	}
	cost += mat[perm[0]][perm[size - 1]];
	return cost;
}
float SimulatedAnnealing::calculateTemp(int startCost, float alpha)
{
	return startCost*alpha;
}
void SimulatedAnnealing::neigbourPermutation(int* src, int* des)
{
	int temp;
	int ind1 = g.generateRandomInt(1, size- 1);
	int ind2 = g.generateRandomInt(1, size - 1);
	do
	{
		ind2 = g.generateRandomInt(1, size - 1);
	} while (ind1 == ind2);

	copy(src, des);
	des[ind1] = src[ind2];
	des[ind2] = src[ind1];
}




double SimulatedAnnealing::reduceTempGeo(float temp, float alpha)
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

void SimulatedAnnealing::setSize(int val)
{
	size = val;
}
void SimulatedAnnealing::setCost(int val)
{
	cost = val;
}
void SimulatedAnnealing::displaySolution()
{
	std::cout << "path: ";
	for (int i = 0; i <= size; i++)
	{
		std::cout << path[i] << " ";
	}
	//std::cout << std::endl;
	std::cout << std::endl << "koszt: " << cost << std::endl;
}


int SimulatedAnnealing::epoch(int vertex, int multipier)
{
	return vertex * multipier;
}

float SimulatedAnnealing::startTemp(float startCost, float vertex)
{

	return startCost * vertex;
}


void SimulatedAnnealing::setStrartParametrs(int ver, int **matrix)
{
	setSize(ver);						//ilosc wierzcholkow
	path = new int[size + 1];
	//permutacja poczatkowa {0, 1, 2, ..., n}
	for (int i = 0; i < size; i++)
	{
		path[i] = i;
		
	}
	path[size] = 0;						//pierwszy i ostatni element tablicy zawsze ma wartosc 0
	//losowa permutacja
	shuffle(path);
	T0 = startTemp(calculateCost(path, matrix), ver);
	L = epoch(ver, 20);
}




void SimulatedAnnealing::findPath(int **matrix)
{
	
	float temp;							//temperatura
	int minCost;						//koszt minimalny
	int costDiff, currentCost, neigCost;//koszty sciezek
	double x;							//liczba losowa z zakresu (0,1)

	//inicjacja tablic
	
	int* minPath = new int[size];
	int* neighbour = new int[size];

	


	minCost=calculateCost(path, matrix);
	

	//temp=calculateTemp(minCost, ALPHA); 
	temp = T0; //ustawienie poczatkowej temperatury
	//std::cout <<"(3,5) "<<matrix[5][3] << std::endl;

	int n = 0; int m = 0;
	while(temp>0.1)
	{
		for (int j = 0; j < L; j++)
		{
		
			for (int k = 0; k < size - 1; k++)
			{

				neigbourPermutation(path, neighbour);
				currentCost = calculateCost(path, matrix);
				neigCost = calculateCost(neighbour, matrix);
				costDiff = currentCost - neigCost;

			}

			//ustawianie minimalnego kosztu na wypadek wyjscia z minimum lokalnego
			if (neigCost < minCost)
			{
				minCost = neigCost;
				copy(neighbour, minPath);
				//std::cout << "minCost: " << minCost << "\n";
			}

			if (costDiff < 0)
			{
				currentCost = neigCost;
				copy(neighbour, path);
			}
			else
			{
				x = g.generateRandomFloat(0, 1);
				if (x < pow(EULER,((float)-costDiff/(float)temp)))
				{
					currentCost = neigCost;
					copy(neighbour, path);
				}
				
			}
			
			//displaySolution();
		}
		//std::cout << "nowaEpoka: " << i << "\n";
		temp = reduceTempGeo(temp, ALPHA);
		//std::cout << temp << "\n";
		

	}
	//displaySolution();
	//std::cout << "currentCost: " << currentCost << " \n\n";
	copy(minPath, path);
	cost = minCost;

	delete[] neighbour;
	delete[] minPath;
}


SimulatedAnnealing::~SimulatedAnnealing()
{
	delete[]path;
}

void SimulatedAnnealing::shuffle(int* arr)
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

int SimulatedAnnealing::getCost()
{
	return cost;
}

void SimulatedAnnealing::setL(int l)
{
	
	L = l;
}
void SimulatedAnnealing::setT(int t)
{
	
	T0 = t;
}
void SimulatedAnnealing::setAlpha(float a)
{
	
	ALPHA = a;
}
int SimulatedAnnealing::getL()
{
	return L;
}
int SimulatedAnnealing::getT0()
{
	return T0;
}
float SimulatedAnnealing::getAlpha()
{
	return ALPHA;
}
void SimulatedAnnealing::displayParametrs()
{
	std::cout << "\n(1)wykonaj\n";
	std::cout << "(2)dlugosc epoki L:        "<< L << std::endl;
	std::cout << "(3)Temperatura poczatkowa: "<< T0 << std::endl;
	std::cout << "(4)wspolczynnik alpha:     "<< ALPHA << std::endl;
	


}