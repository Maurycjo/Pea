
#include "BinaryHeap.h"

void BinaryHeap::addNode(Node node)
{

	Node temp2;
	temp2.createNode(vertex);


	Node* temp = new Node[heapSize + 1];

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