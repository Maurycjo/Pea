
#include "Reader.h"


long long int Reader::read_QPC()
{
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}

void Reader::reading(BruteForce brute)
{
	/*
	7 wielkosci
	kazda 100 grafow
	B&B i BruteForce
	*/
	file.open("bruteReading.txt");

	for (int i = 4; i < 12; i++)
	{
		file << i << " wierzcholkow" << endl;
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
void Reader::reading(BranchNBound& bnb)
{
		file.open("bnbReading.txt");

		for (int i = 6; i < 21; i += 2)
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
				file << fixed << setprecision(10) << (float)elapsed / frequency << endl;
				//cout << "Time [ms] =" << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
				//cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) /frequency << endl;
			}

		}
		file.close();
}
void Reader::reading(SimulatedAnnealing& sa)
{
	file.open("SAReading.txt");

	for (int i = 8; i <= 40; i += 2)
	{
		file << i << " wierzcholkow" << endl;
		for (int j = 0; j < 10; j++)
		{
			matrix.directedGraph(i);
			start = read_QPC();
			sa.setStrartParametrs(matrix.getVertex(), matrix.array);
			sa.findPath(matrix.array);
			elapsed = read_QPC() - start;

			//file << fixed << setprecision(10) << (float)elapsed / frequency << endl;

			//file << fixed << setprecision(0) << (1000000.0 * elapsed) / frequency << endl;us
			//fiel<< fixed << setprecision(3) << (float)elapsed / frequency << endl; ms
			//file<< setprecision(3) << (1000.0 * elapsed) / frequency << endl; ms 
			file << fixed << setprecision(5) << (float)elapsed / frequency << endl;
			//cout << "Time [ms] =" << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
			//cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) /frequency << endl;
		}
	}
	file.close();
}
void Reader::compare(BranchNBound& bnb, SimulatedAnnealing& sa)
{
	file.open("bnbKoszt.txt");
	file2.open("saKoszt.txt");

	for (int i = 6; i < 20; i++)
	{
		file << i << " wierzcholkow" << endl;
		file2 << i << " wierzcholkow" << endl;
		for (int j = 0; j < 10; j++)
		{
		matrix.directedGraph(i);

		bnb.findPath(matrix.array, matrix.getVertex());
		file << bnb.getCost() << endl;
		sa.setStrartParametrs(matrix.getVertex(), matrix.array);
		sa.findPath(matrix.array);
		file2 << sa.getCost() << endl;
		}
	}

	file.close();
	file2.close();
}

void Reader::readingWithTemperature(SimulatedAnnealing& sa)
{

	file.open("SA_Temperature.txt");
	for (int i = 500; i <= 5000; i +=500 )
	{
		file << i << " temperatura" << endl;
		for (int j = 0; j < 100; j++)
		{
		matrix.directedGraph(15);
			
			start = read_QPC();
			sa.setStrartParametrs(matrix.getVertex(), matrix.array);
			sa.setT(i);
			sa.findPath(matrix.array);
			elapsed = read_QPC() - start;

			//file << fixed << setprecision(10) << (float)elapsed / frequency << endl;

			//file << fixed << setprecision(0) << (1000000.0 * elapsed) / frequency << endl;us
			//fiel<< fixed << setprecision(3) << (float)elapsed / frequency << endl; ms
			//file<< setprecision(3) << (1000.0 * elapsed) / frequency << endl; ms 
			file << fixed << setprecision(5) << (float)elapsed / frequency << endl;
			//cout << "Time [ms] =" << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
			//cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) /frequency << endl;
		}
	}
	file.close();



}