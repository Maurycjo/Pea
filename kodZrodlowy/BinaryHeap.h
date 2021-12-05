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



void BinaryHeap::addNode(Node node)
{
	
	Node temp2;
	temp2.createNode(vertex);
	

	Node* temp = new Node[heapSize+1];

	for (int i = 0; i < heapSize; i++)
	{
		temp[i] = heap[i];
	}
	node.copyNode(temp2, vertex);
	temp2.cost = node.cost;
	temp2.pathSize = node.pathSize;
	temp[heapSize] = temp2;


	delete[] heap;
	heap = temp;
	heapSize++;
	
	heap_fix_up();
}



void BinaryHeap::heap_fix_up()
{
	//dekrementacja nastepuje w celu wyznaczenia ostaniego indeksu kopca
	int fixSize = heapSize - 1;
	int help;
	Node temp;
	while (heap[parent(fixSize)].cost > heap[fixSize].cost)
	{
		temp = heap[parent(fixSize)];
		heap[parent(fixSize)] = heap[fixSize];
		heap[fixSize] = temp;
		fixSize = parent(fixSize);
	}
}
int BinaryHeap::parent(int sonIndeks)
{
	return ((sonIndeks - 1) / 2);
}
//zwraca indeks lewego potomka, arg= indeks rodzica
int BinaryHeap::leftSon(int parentIndeks)
{

	return 2 * parentIndeks + 1;
}
//zwraca indeks prawego potomka, arg= indeks rodzica
int BinaryHeap::rightSon(int parentIndeks)
{

	return 2 * parentIndeks + 2;
}
void BinaryHeap::heap_fix_down()
{
	int fixSize = 0;
	Node help;
	while (leftSon(fixSize) < heapSize - 1 && rightSon(fixSize) < heapSize - 1)
	{

		if ((heap[fixSize].cost > heap[leftSon(fixSize)].cost) && heap[leftSon(fixSize)].cost <= heap[rightSon(fixSize)].cost)
		{
			help = heap[fixSize]; //rodzic
			heap[fixSize] = heap[leftSon(fixSize)];
			heap[leftSon(fixSize)] = help;
			fixSize = leftSon(fixSize);
		}
		else if (heap[fixSize].cost > heap[rightSon(fixSize)].cost)
		{
			help = heap[fixSize];
			heap[fixSize] = heap[rightSon(fixSize)];
			heap[rightSon(fixSize)] = help;
			fixSize = rightSon(fixSize);
		}
		else break;
	}
}
void BinaryHeap::remove()
{
	if (heapSize == 0)
	{
		std::cout << "brak wartosci do usuniecia!" << std::endl;
		return;
	}
	heap[0] = heap[heapSize - 1];
	heapSize--;
	Node* buffor = new Node[heapSize];
	for (int i = 0; i < heapSize; i++)
	{
		buffor[i] = heap[i];
	}
	delete[] heap;
	heap = buffor;
	heap_fix_down();
}





