
#include "SimulatedAnnealing.h"




int SimulatedAnnealing::getSize()
{
	return size;
}
void SimulatedAnnealing::setSize(int val)
{
	val = size;
}


SimulatedAnnealing::SimulatedAnnealing()
{

}

float SimulatedAnnealing::calculateTemp(int startCost, float alpha)
{


	return 0;
}
int SimulatedAnnealing::neigbourPermutation(int* array)
{


	return 0;
}
float SimulatedAnnealing::reduceTempGeo(float temp, float alpha)
{
	return alpha * temp;
}
void SimulatedAnnealing::findPath(int** array)
{

}
