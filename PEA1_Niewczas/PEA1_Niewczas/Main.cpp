
#include "Matrix.h"
#include <Windows.h>
#include "generateGraph.h"
#include <ctime>
#include "menu.h"
#include "BruteForce.h"
#include "BranchNBound.h"
#include "reading.h"

using namespace std;

int main()
{
	
	ofstream times;

	BranchNBound bnb;
	BruteForce brute;
	Matrix matrix;
	int menu;
	bool ifRead;
	//ofstream times;


	while (true)
	{
		cout << "Graf w postaci macierzy sasiedctwa" << endl << endl;

		inputGraphMenu();
		do
		{
			ifRead = 0;
			cin >> menu;

			switch (menu)
			{
			case 1:
				matrix.inputFile(ifRead);
				if (ifRead == 0)
				{
					inputGraphMenu();
				}
				break;
			case 2:
				system("cls");
				choseMat(matrix);
				break;
			/*
			case 3:
				
				readingBF(matrix, brute);
				readingBB(matrix, bnb);

				cout << "koniec pomiarow" << endl;

				return 0;
			*/
			case 0:
				return 0;
			default:
				cout << "wybierz poprawna liczbe!" << endl;
				break;
			}

		} while (menu < 0 || menu>2||menu==1&&ifRead==0);

		
		
				algorytmList();
			do
			{
				cout << "Wybierz: ";
				cin >> menu;

				switch (menu)
				{
				case 1:
					cout << "BruteForce" << endl;
					

					//BruteForce brute;
					//brute.findPermutations(matrix.getVertex());
					brute.findPermutations(matrix.getVertex(), matrix.array);
				


					break;
				case 2:
					//tu bedzie metoda wykonujaca B&B lub DP
					bnb.findPath(matrix.array, matrix.getVertex());
					//bnb.deinitAll(matrix.getVertex());
					
					break;

				case 3:
					system("cls");
					algorytmList();
					break;
					
					break;
				case 4:
					matrix.display();
					break;
				case 5:
					system("cls");
					algorytmList();
					break;
				case 0:
					return 0;
				default:
					cout << "wybierz poprawna liczbe!" << endl;
					break;
				}

			} while (menu != 3);
		
	}
	return 0;
}


