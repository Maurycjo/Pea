#pragma once
#include <stdexcept>
#include <iostream>

//using namespace std;

class Node
{
public:
	int cost;
	int** array = NULL;
	int* path = NULL;
	
	int pathSize;
	int* visited[2];
	
	void createNode(int vertex)
	{

		array = new int* [vertex]; //tablica wskaŸników
		visited[0] = new int[vertex];
		visited[1] = new int[vertex];
		path = new int[vertex+1];
		for (int i = 0; i < vertex; i++)
		{
			array[i] = new int[vertex];
			visited[0][i] = i;
			visited[1][i] = 0;
		}
		visited[1][0] = 1; //wierzcholek poczatkowy traktuje jako odwiedzony
		path[0] = 0;
		pathSize = 1;
	}
	void addPath(int val)
	{
		path[pathSize] = val;
		pathSize++;
	}

	void removeNode(int vertex)
	{
		for (int i = 0; i < vertex; i++)
		{
			delete[] array[i];
		}
		delete[] array;
		delete[] path;
		delete[] visited[0];
		delete[] visited[1];
	}

	
	void copyNode(Node destiny, int vertex)
	{
		for (int i = 0; i < vertex; i++)
		{
			destiny.visited[1][i] = visited[1][i];
			for (int j = 0; j < vertex; j++)
			{
				destiny.array[i][j] = array[i][j];
			}
		}
		for (int i = 0; i < pathSize; i++)
		{
			destiny.path[i]=path[i];
		}
		destiny.pathSize = pathSize;
		//destiny.cost = cost;
	


	}

	
};

//kopiec minimalny sortowany po koszcie macierzy
class BinaryHeap
{

public:
	const int infinity = 9999;

	Node* heap = NULL;
	int heapSize = 0;
	int upper = infinity;
	int vertex;

	~BinaryHeap()
	{
		while (heapSize > 0)
		{
			remove();
		}
	}
	void addNode(Node node);
	int parent(int sonIndeks);
	//zwraca indeks lewego potomka, arg= indeks rodzica
	int leftSon(int parentIndeks);
	//zwraca indeks prawego potomka, arg= indeks rodzica
	int rightSon(int parentIndeks);
	//naprawa kopca na podstawie kosztu macierzy
	void heap_fix_up();
	void heap_fix_down();
	void heap_fix_root();
	void remove();
	Node copyNode(Node Source, int vertex);
	void addPath(Node node, int val);
	void setVertex(int val)
	{
		vertex = val;
	}
	
};









