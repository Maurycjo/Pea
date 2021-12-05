
#include "BranchNBound.h"


using namespace std;
void BranchNBound::setVertex(int val)
{
	vertex = val;
}
int BranchNBound::reduce(int** array)
{
	int min = infinity, reducedCost = 0;

	//cout<<"rows\n";
	for (int i = 0; i < vertex; i++)
	{
		min = infinity;
		for (int j = 0; j < vertex; j++)
		{

			if (array[i][j] < min)
				min = array[i][j];

		}
		if (min == infinity)
		{
			min = 0;
		}

		//cout << min << " ";
		reducedCost += min;
		for (int k = 0; k < vertex; k++)
		{
			if (array[i][k] != infinity)
				array[i][k] -= min;
		}
	}

	//cout<<"\ncolumns\n";
	for (int i = 0; i < vertex; i++)
	{
		min = infinity;
		for (int j = 0; j < vertex; j++)
		{
			if (array[j][i] < min)
				min = array[j][i];
		}
		if (min == infinity)
			min = 0;
		//cout << min << " ";
		reducedCost += min;
		for (int k = 0; k < vertex; k++)
		{
			if (array[k][i] != infinity)
				array[k][i] -= min;
		}


	}
	return reducedCost;
}
void BranchNBound::setInfinity(int** array, int startVer, int endVer)
{

	for (int i = 0; i < vertex; i++)
	{
		array[i][endVer] = infinity;
		array[startVer][i] = infinity;
	}
	array[endVer][0] = infinity;


}


void BranchNBound::findPath(int** array, int ver)
{
	BinaryHeap nodeHeap;
	nodeHeap.setVertex(ver);

	setVertex(ver);

	Node operMatrix, parentMatrix;
	operMatrix.createNode(vertex);
	parentMatrix.createNode(vertex);
	copy(array, parentMatrix.array);
	parentMatrix.cost = reduce(parentMatrix.array);
	operMatrix.pathSize = parentMatrix.pathSize;
	parentMatrix.copyNode(operMatrix, vertex);
	operMatrix.cost = parentMatrix.cost;

	nodeHeap.addNode(parentMatrix);


	while (parentMatrix.pathSize < vertex && parentMatrix.cost <= nodeHeap.upper)
	{
		//displayNode(parentMatrix);
		operMatrix.pathSize = parentMatrix.pathSize;
		parentMatrix.copyNode(operMatrix, vertex);
		operMatrix.cost = parentMatrix.cost;

		//displayNode(parentMatrix);
		for (int i = 1; i < vertex; i++)
		{
			if (operMatrix.visited[1][i] == 0)
			{

				setInfinity(operMatrix.array, operMatrix.path[operMatrix.pathSize - 1], i);
				operMatrix.cost += reduce(operMatrix.array) + parentMatrix.array[operMatrix.path[operMatrix.pathSize - 1]][i];
				operMatrix.addPath(i);
				operMatrix.visited[1][i] = 1;
				//displayNode(operMatrix);

				if (operMatrix.cost <= nodeHeap.upper)
				{
					nodeHeap.addNode(operMatrix);
					//displayNode(nodeHeap.heap[0]);
				}


				if (operMatrix.pathSize == vertex && operMatrix.cost < nodeHeap.upper)
				{
					//cout << nodeHeap.upper << endl;
					nodeHeap.upper = operMatrix.cost;
				}

			}
			operMatrix.pathSize = parentMatrix.pathSize;
			parentMatrix.copyNode(operMatrix, vertex);
			operMatrix.cost = parentMatrix.cost;
		}
		parentMatrix = nodeHeap.heap[0];
		//parentMatrix.cost = nodeHeap.heap[0].cost;
		parentMatrix.pathSize = nodeHeap.heap[0].pathSize;

		nodeHeap.remove();
		/*
		parentMatrix.copyNode(operMatrix, vertex);
		operMatrix.pathSize = parentMatrix.pathSize;
		operMatrix.cost = parentMatrix.cost;
		*/
	}

	parentMatrix.addPath(0);
	//displayNode(parentMatrix);
	displayPath(parentMatrix);
	//cout <<endl<< operMatrix.pathSize;


}
void BranchNBound::display(int** array)
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
			std::cout << std::setw(5) << array[i][j];
		}
		std::cout << std::endl;
	}
}
void BranchNBound::displayNode(Node node)
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
			std::cout << std::setw(5) << node.array[i][j];
		}
		std::cout << std::endl;
	}
	cout << "path: ";
	for (int i = 0; i < node.pathSize; i++)
	{
		cout << node.path[i] << " ";
	}
	cout << endl;
	cout << "koszt: " << node.cost << endl;

}
void BranchNBound::copy(int** source, int** destiny)
{
	for (int i = 0; i < vertex; i++)
	{
		for (int j = 0; j < vertex; j++)
		{
			destiny[i][j] = source[i][j];
		}
	}

}
void BranchNBound::displayPath(Node node)
{
	cout << "path: ";
	for (int i = 0; i < node.pathSize; i++)
	{
		cout << node.path[i] << " ";
	}
	cout << endl;
	cout << "koszt: " << node.cost << endl;

}
