#pragma once

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <iomanip>
#include <string>
#include "RandomGenerator.h"

class Matrix
{
	const int minWeight = 1;
	const int maxWeight = 100;

private:
	int edges = 0;		//liczba krawedzi
	int vertex = 0;		//liczba wierzcholkow
	int startVertex = 0;//wierzcholek poczatkowy
public:
	RandomGenerator g;
	int** array = NULL;			//deklaracja tablicy wskaznikow
	void inputConsole();	//wczytywanie wag miedzy wierzcholkami
	void inputFile(bool &ifRead);		//wczytanie wag z pliku
	~Matrix();			//destruktor, zwalnienie pamieci
	void display();			//wyswietlanie grafu w postaci maczierzowej
	void init(int size);	//tworzenie tablicy wskaznikow
	void deinit();			//zwolnienie macierzy
	void clean();			//zerowanioe wag
	//setery, getery
	int getVertex();
	void setEdges(int val);
	void directedGraph(int quantity);

};

