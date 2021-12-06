#pragma once
#include "Matrix.h"
#include <ctime>
#include <cstdlib>
#include <random>



int generateRandom(int a, int b)
{

	std::random_device rd; // non-deterministic generator
	std::mt19937 gen(rd()); // random engine seeded with rd()
	//uniform_int_distribution<> dist(-2147483648, 2147483647); // distribute results between	
	std::uniform_int_distribution<> dist(a, b);
	return dist(gen);
}

/*
double generateRandomF(float a, float b)
{
	std::random_device rd; // non-deterministic generator
	std::mt19937 gen(rd()); // random engine seeded with rd()
	//uniform_int_distribution<> dist(-2147483648, 2147483647); // distribute results between	
	std::uniform_real_distribution<>dist(a, b);
	return dist(gen);
}
*/
