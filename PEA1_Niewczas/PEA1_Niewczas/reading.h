#pragma once
#include <fstream>
#include "generateGraph.h"




//pomiary brute force
void readingBF(Matrix &matrix, BruteForce &brute)
{
	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
	/*
	7 wielkosci
	kazda 100 grafow
	B&B i BruteForce
	*/
	ofstream file;
	file.open("bruteReading.txt");

	for (int i = 4; i < 12; i++)
	{
		file<< i << " wierzcholkow" << endl;
		for (int j = 0; j < 100; j++)
		{
			matrix.directedGraph(i);
			start = read_QPC();
			brute.findPermutations(matrix.getVertex(), matrix.array);
			elapsed = read_QPC() - start;

			file << fixed << setprecision(10) << (float)elapsed / frequency << endl;

			//file << fixed << setprecision(0) << (1000000.0 * elapsed) / frequency << endl;us
			//file<< fixed << setprecision(3) << (float)elapsed / frequency << endl; ms
			//file<< setprecision(3) << (1000.0 * elapsed) / frequency << endl; ms 
			//cout << "Time [s] = " << fixed << setprecision(3) << (float)elapsed /frequency << endl;
			//cout << "Time [ms] =" << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
			//cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) /frequency << endl;
		}

	}
	file.close();
}

//pomiary B&B
void readingBB(Matrix &matrix, BranchNBound &bnb)
{
	long long int frequency, start, elapsed;
QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

	ofstream file;
	file.open("bnbReading.txt");

	for (int i = 6; i < 21; i+=2)
	{
		file << i << " wierzcholkow" << endl;
		for (int j = 0; j < 100; j++)
		{
			matrix.directedGraph(i);
			start = read_QPC();
			bnb.findPath(matrix.array, i);
			elapsed = read_QPC() - start;

			//file << fixed << setprecision(10) << (float)elapsed / frequency << endl;

			//file << fixed << setprecision(0) << (1000000.0 * elapsed) / frequency << endl;us
			//fiel<< fixed << setprecision(3) << (float)elapsed / frequency << endl; ms
			//file<< setprecision(3) << (1000.0 * elapsed) / frequency << endl; ms 
			file << fixed << setprecision(10) << (float)elapsed /frequency << endl;
			//cout << "Time [ms] =" << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
			//cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) /frequency << endl;
		}

	}
file.close();




}