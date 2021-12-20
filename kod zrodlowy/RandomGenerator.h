#pragma once
#include <cstdlib>
#include <time.h>
#include <random>
#include <ctime>



class RandomGenerator
{
public:

	int generateRandomInt(int a, int b)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(a, b);
		return dist(gen);
	}
	float generateRandomFloat(float a, float b)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dist(a, b);
		return dist(gen);
	
	}


};

