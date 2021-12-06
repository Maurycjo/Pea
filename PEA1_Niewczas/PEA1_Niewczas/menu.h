#pragma once
#include "Matrix.h"
#include <Windows.h>
#include <ctime>

using namespace std;

long long int read_QPC()
{
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}

void algorytmList()
{
	cout << "(1) BruteForce" << endl;
	cout << "(2) B&B" << endl;
	cout << "(3) SimulatedAnnealing" << endl;
	cout << "(4) Zmiana grafu" << endl;
	cout << "(5) Wyswietl" << endl;
	cout << "(6) wyczysc ekran" << endl;
	cout << "(0) Wyjscie" << endl;

}

void inputGraphMenu()
{
	cout << "(1) wczytaj z pliku" << endl;
	cout << "(2) generuj graf" << endl;;
	cout << "(0) wyjscie" << endl;
	cout << "Wybierz: ";
}


void choseMat(Matrix& matrix)
{
	int ver;

		cout << "Wybierz ilosc wierzcholkow: ";
		cin >> ver;
		matrix.directedGraph(ver);
	
	
}
