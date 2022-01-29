
#include "Matrix.h"
#include "RandomGenerator.h"
#include "menu.h"
#include "BruteForce.h"
#include "BranchNBound.h"
#include "Reader.h"
#include "SimulatedAnnealing.h"
#include "GA.h"

using namespace std;

int main()
{
	
	ofstream times;

	BranchNBound bnb;
	BruteForce brute;
	SimulatedAnnealing sa;
	Matrix matrix;
	Reader r;
	int menu, saMenu, temp, gamenu;
	float temp2;
	bool ifRead;
	GA ga;
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
				//pomiary
				r.readingWithMutation(ga);
				
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
					bnb.displayPath();
					//bnb.deinitAll(matrix.getVertex());
					
					break;
				case 3:
						
							sa.setStrartParametrs(matrix.getVertex(), matrix.array);
						sa.displayParametrs();
						do
						{
							cout << "Wybierz: ";
							cin >> saMenu;

						switch (saMenu)
						{
						case 1:
							sa.findPath(matrix.array);
							sa.displaySolution();
							break;
						case 2:
							cout << "nowa epoka: ";
							cin >> temp;
							sa.setL(temp);
							sa.displayParametrs();
							break;
						case 3:
							cout << "nowa temperatura: ";
							cin >> temp;
							sa.setT(temp);
							sa.displayParametrs();
							break;
						case 4:
							cout << "nowy wspolczynnik alpha: ";
							cin >> temp2;
							sa.setAlpha(temp2);
							sa.displayParametrs();
							break;
						default:
							cout << "podaj odpowiednia operacje!\n";
							break;
						}
						} while (saMenu != 1);

						break;
				case 4:
					ga.setSize(matrix.getVertex());
					
					ga.displayParametrs();
					do
					{
						cout << "wybierz: ";
						cin >> gamenu;
						ga.changeParametrs(gamenu);
						system("cls");
						ga.displayParametrs();
					} while (gamenu != 1);
					
					ga.findChromosome(matrix.array);
					ga.displaySolution();
					algorytmList();
					break;
				case 5:
					system("cls");
					algorytmList();
					break;
					
					break;
				case 6:
					matrix.display();
					break;
				case 7:
					system("cls");
					algorytmList();
					break;
				case 0:
					return 0;
				default:
					cout << "wybierz poprawna liczbe!" << endl;
					break;
				}

			} while (menu != 5);
		
	}
	return 0;
}


