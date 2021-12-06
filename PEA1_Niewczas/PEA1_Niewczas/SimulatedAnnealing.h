#pragma once
#include <math.h>
#include "Matrix.h"
#include "RandomGenerator.h"


class SimulatedAnnealing
{
private:
	const int L = 1000;
	const int T0 = 10000;
	const float ALPHA = 0.90; // <0,85; 0,98>
	int size, cost;
	int* path;

	void copy(int* src, int* des);					 //kopiowanie z tablicy do drugiej
	void setSize(int val);						 //ustawienie ilosci wierzchlkow
	void setCost(int val);
	int calculateCost(int* perm, int **mat);		 //obliczanie kosztu permutacji
	float calculateTemp(int startCost, float alpha); //iloczyn kosztu pocz¹tkowego i wspó³czynnik
	void neigbourPermutation(int* src, int* des);	 //szukanie sasiedniej permutacji
	double reduceTempGeo(float temp, float alpha);	 //geometryczna redukcja temperatury
	RandomGenerator g;								//generator liczb losowych

public:												
	void findPath(int **matrix, int ver);			 //metoda g³owna algorytmu
	void displaySolution();
	~SimulatedAnnealing();
	
};