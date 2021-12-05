
#include "Matrix.h"
#include <algorithm>

using namespace std;
//generowanie permutacji algorytm
class BruteForce
{

public:
    void display(int a[], int n);               //wyswietlanie
    void findPermutations(int n, int **array);  //metoda szukajaca najkrotszej sciezki
   
    int* arr = NULL;
    int* path = NULL;
};


