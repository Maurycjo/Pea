#include <stdlib.h>
#include <time.h>



int generateRandomInt(int a, int b)
{
	srand(static_cast<unsigned>(time(0)));
	return rand() % b + a;
}
float generateFloata(float a, float b)
{
	srand(static_cast<unsigned>(time(0)));
	return a + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (b - a)));
}