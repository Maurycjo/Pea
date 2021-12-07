#pragma once
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <iomanip>
#include "BinaryHeap.h"
class BranchNBound
{
	const int infinity = 9999;
	int cost;
	int* pat;
public:
	int vertex;
	int* visited[2];
	//int** operMatrix = NULL, ** minMatrix = NULL, ** reducedMatrix = NULL, ** parentMatrix = NULL;
	void copy(int** source, int** destiny);					//kopiowanie tablicy dwuwumiarowej
	int reduce(int** array);								//redukowanie macierzy, zwraca koszt
	void setInfinity(int** array,int startVer, int endVer); //ustawianie nieskonczonoosci namacierzy
	void findPath(int** array, int ver);					//metoda szukajaca najkrotszej sciezki
	void display(int** array);								//wyswietlanie tablicy
	void displayNode(Node node);							//wyswietlanie calego wezla
	void setVertex(int val);								//ustawienie wierzcholkow
	void displayPath(Node node);							//wyswietlanie sciezki
	void copy(int* src, int *des);							//kopiowanie tablicy jednowymiarowej
	int getCost();
	void displayPath();
	~BranchNBound();
};

