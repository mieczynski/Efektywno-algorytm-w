#include "GraphAlgorithms.h"
#include <iostream>
using namespace std;
#define INF 1000



int GraphAlgorithms::getCostOfPath(vector<int> path)
{
	int totalPath = 0;
	
	for (int i = 0; i < path.size() - 1; i++)
		totalPath += graph.getEdge(path[i], path[i + 1]);
	
	return totalPath;
}




Graph GraphAlgorithms::getMin(Graph graph)
{
	vector <bool> visited(graph.getSize(), false);

	currentPath.resize(graph.getSize() + 1);

	int startV, endV;

	int min = INF;

	for (int i = 0; i < graph.getSize(); i++)
	{
		for (int j = 0; j < graph.getSize(); j++)
		{
			if (graph.getEdge(i, j) < min )
			{
				min = graph.getEdge(i,j), startV = i, endV = j;
			}
		}
	}

	currentPath[0] = startV;
	visited[startV] = true;
	
	for (int i = 1; i < graph.getSize(); i++)
	{
		min = INF;

		for (int j = 0; j < graph.getSize(); j++)
		{
			if (!visited[j] && graph.getEdge(startV,j) < min  )
			{
				min = graph.getEdge(startV, j), endV = j;
			}
		
		}

		visited[endV] = true;
		startV = endV;
		currentPath[i] = startV;
	}

	currentPath[graph.getSize()] = currentPath[0];

	graph.updateSolution(currentPath);
	
	return graph;
}

