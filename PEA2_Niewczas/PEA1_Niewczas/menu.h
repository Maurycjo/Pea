#pragma once
#include "Matrix.h"
#include <Windows.h>
#include <ctime>

using namespace std;



void algorytmList()
{
	cout << "(1) BruteForce" << endl;
	cout << "(2) B&B" << endl;
	cout << "(3) SimulatedAnnealing" << endl;
	cout << "(4) Genetic Algoritm" << endl;
	cout << "(5) Zmiana grafu" << endl;
	cout << "(6) Wyswietl" << endl;
	cout << "(7) wyczysc ekran" << endl;
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
