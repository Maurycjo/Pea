#pragma once
#include <fstream>
#include "BranchNBound.h"
#include "BruteForce.h"
#include"SimulatedAnnealing.h"
#include <ctime>
#include <Windows.h>
#include <iostream>




class Reader
{
private:
	long long int frequency, start, elapsed;
	ofstream file, file2;
	Matrix matrix;
public:
	Reader()
	{
		QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
	}
	long long int read_QPC();
	void reading(BruteForce brute);
	void reading(BranchNBound& bnb);
	void reading(SimulatedAnnealing &sa);
	void compare(BranchNBound& bnb, SimulatedAnnealing& sa);
	void readingWithTemperature(SimulatedAnnealing& sa);




};

