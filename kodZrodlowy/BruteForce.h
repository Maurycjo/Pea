
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


void BruteForce::display(int a[], int n)
{
    for (int i = 0; i < n; i++) {
        cout << a[i] << "  ";
    }
    cout << endl;
}


void BruteForce::findPermutations(int n, int **array)
{
    int key;
    int minKey = 9999;

    arr = new int[n];
    path = new int[n+1];
    for (int i = 0; i < n; i++)
    {
        arr[i] = i;
    }
   

    //wszystkie mozliwe permutacje
    do 
    {
        key = 0;
       // display(arr, n);
        for (int i = 0; i < n-1; i++)
        {
            key += array[arr[i]][arr[i + 1]];
        }
        key += array[arr[n - 1]][arr[0]];

        if (key < minKey)
        {
            for (int i = 0; i < n; i++)
            {
                path[i] = arr[i];
            }
            minKey = key;
            //cout << key << endl;
        }



    } while (next_permutation(arr, arr + n));

    
    path[n] = 0;
    
    cout << "path: ";
    for (int i = 0; i < n+1; i++)
    {
        cout << path[i] << " ";
    }
    cout << endl << "koszt: " << minKey << endl;
    
    arr = nullptr;
    path = nullptr;

    delete[]arr;
    delete[]path;


}