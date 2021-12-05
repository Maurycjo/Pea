#pragma once

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <iomanip>
#include <string>

class Matrix
{

private:
	int edges = 0;		//liczba krawedzi
	int vertex = 0;		//liczba wierzcholkow
	int startVertex = 0;//wierzcholek poczatkowy
public:
	int** array = NULL;			//deklaracja tablicy wskaznikow
	void inputConsole();	//wczytywanie wag miedzy wierzcholkami
	void inputFile(bool &ifRead);		//wczytanie wag z pliku
	~Matrix();			//destruktor, zwalnienie pamieci
	void display();			//wyswietlanie grafu w postaci maczierzowej
	void init(int size);	//tworzenie tablicy wskaznikow
	void deinit();			//zwolnienie macierzy
	void clean();			//zerowanioe wag
	//setery, getery
	int getVertex();
	void setEdges(int val);
	void directedGraph(int quantity);

	void bruteForce();

};

int Matrix::getVertex()
{
	return vertex;
}
void Matrix::setEdges(int val)
{
	if (val >= 0)
		edges = val;
	else
		throw std::out_of_range("liczba ujemna: ilosc krawedzi");
}

void Matrix::init(int size)
{
	if (size > 0)
	{
		array = new int* [size]; //tablica wskaźników
		for (int i = 0; i < size; i++)
		{
			array[i] = new int[size];
		}
		vertex = size;
	}
	else
		throw std::out_of_range("ilosc wierzchokow musi byc wieksza od 0");
}
//metoda pomocnicza czyszczaca tablice
void Matrix::clean()
{
	for (int i = 0; i < vertex; i++)
	{
		for (int j = 0; j < vertex; j++)
		{
			array[i][j] = 0;
		}
	}
}
void Matrix::deinit()
{
	
	for (int i = 0; i < vertex; i++)
	{
		delete[] array[i];
	}
	delete[] array;
	
}

Matrix::~Matrix()
{
	deinit();
}


//zmiana formatu
void Matrix::inputFile(bool &ifRead)
{
	std::string whenDimension, edgeSection;
	std::string fileName;
	int  val;
	int dimension;

	std::cout << "podaj nazwe pliku z ktorego chcesz wczytac graf: ";
	std::cin >> fileName;
	std::ifstream file;
	file.open(fileName.c_str());
	if (file.is_open())
	{
		
		
			if (file.fail())
			{
				std::cout << "File error - READ DATA" << std::endl;
			}
			else
			{
				do
				{
					file >> whenDimension;

				} while (whenDimension != "DIMENSION:");
			//wczytanie ilosci wierzcholkow
			file >> dimension;

			}
		try
		{
			init(dimension);
		}
		catch (std::out_of_range& e)
		{
			std::cout << e.what() << std::endl;
		}
		
		clean();
		if (file.fail())
			std::cout << "File error - READ SIZE" << std::endl;
		else
		{
			do 
			{
			
				file >> edgeSection;
			} while (edgeSection != "EDGE_WEIGHT_SECTION");

			for (int i = 0; i < dimension; i++)
			{
				for (int j = 0; j < dimension; j++)
				{


					if (file.fail())
					{
						std::cout << "File error - READ DATA" << std::endl;
						break;
					}
					else
					{
							file >> val;
							if (file.fail())
							{
								std::cout << "File error - READ DATA" << std::endl;
								break;
							}
							else
							{
								ifRead = 1;
								array[i][j] = val;
							}
						

					}


				}
			}
		}
		file.close();
		setEdges(dimension * dimension);
	}
	else
		std::cout << "File error - OPEN" << std::endl;
}

//wyswietlanie grafu
void Matrix::display()
{
	std::cout << std::setw(4) << " ";
	for (int i = 0; i < vertex; i++)
	{
		std::cout << " |" << std::setw(3) << i;
	}
	std::cout << " |" << std::endl;

	for (int i = 0; i < vertex; i++)
	{
		std::cout << std::setw(4) << i << "|";
		for (int j = 0; j < vertex; j++)
		{
			std::cout << std::setw(5) << array[j][i];
		}
		std::cout << std::endl;
	}

}