#pragma once


class SimulatedAnnealing
{
	int size;
	const int L = 1000;
public:

	

	int getSize();
	void setSize(int val);
	SimulatedAnnealing();
	float calculateTemp(int startCost, float alpha); //iloczyn kosztu pocz�tkowego i wsp�czynnik
	int neigbourPermutation(int* array);
	float reduceTempGeo(float temp, float alpha);
	void findPath(int** array);



};