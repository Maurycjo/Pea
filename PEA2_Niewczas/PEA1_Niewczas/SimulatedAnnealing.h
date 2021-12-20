#pragma once
#include <math.h>
#include "Matrix.h"
#include "RandomGenerator.h"
#include <fstream>


class SimulatedAnnealing
{
private:
	int L;											//dlugosc epoki
	float T0;											//temperatura poczatkowa
	float ALPHA = 0.95; // <0,85; 0,98>
	int size, cost = 0;
	int* path;

	void copy(int* src, int* des);					 //kopiowanie z tablicy do drugiej
	void setSize(int val);						 //ustawienie ilosci wierzchlkow
	void setCost(int val);
	int calculateCost(int* perm, int **mat);		 //obliczanie kosztu permutacji
	float calculateTemp(int startCost, float alpha); //iloczyn kosztu pocz¹tkowego i wspó³czynnik
	void neigbourPermutation(int* src, int* des);	 //szukanie sasiedniej permutacji
	double reduceTempGeo(float temp, float alpha);	 //geometryczna redukcja temperatury
	RandomGenerator g;								//generator liczb losowych
	void shuffle(int* arr);							//losowe wymieszanie wartosci w tablicy
	float startTemp(float startCost, float vertex);		//ustawienie temperatury poczatkowej
	int epoch(int vertex, int multipier);			//ustawienie dlugosci epoki

public:						
	void setStrartParametrs(int ver, int **matrix);
	void setL(int l);
	void setT(int t);
	void setAlpha(float a);
	int getL();
	int getT0();
	float getAlpha();
	void displayParametrs();
	int getCost();								
	void findPath(int **matrix);					 //metoda g³owna algorytmu
	void displaySolution();							//wyswietlanie wyniku
	~SimulatedAnnealing();							//zwalnianie pamieci
	
};