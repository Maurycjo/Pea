#pragma once
#include <math.h>
#include "Matrix.h"
#include "generateRandom.h"

class SimulatedAnnealing
{
	const int L = 1000;
	const float ALPHA = 0.90; // <0,85; 0,98>
	int size;
public:
	int* path;
	//int getSize();
	//void setSize(int val);
	SimulatedAnnealing();
	int calculateCost(int * perm, Matrix mat);		//obliczanie kosztu permutacji
	float calculateTemp(int startCost, float alpha); //iloczyn kosztu pocz¹tkowego i wspó³czynnik
	void neigbourPermutation(int* src, int* des);			//szukanie sasiedniej permutacji
	float reduceTempGeo(float temp, float alpha);	//geometryczna redukcja temperatury
	void findPath(Matrix matrix);						//metoda g³owna algorytmu
	void copy(int* src, int* des);
	void setSize(Matrix matrix);
};