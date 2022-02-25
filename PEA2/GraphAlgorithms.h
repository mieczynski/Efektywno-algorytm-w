#pragma once
#include "Graph.h"

using namespace std;

class GraphAlgorithms
{
protected:
	int size;
	vector <int> currentPath;				//aktualnie znaleziona œcie¿ka
	int getCostOfPath(vector <int> path);		//metoda zwracaj¹ca koszt œcie¿ki
	Graph graph;

public:
	GraphAlgorithms() {};
	~GraphAlgorithms() {};
	Graph getMin(Graph graph);	//metoda ustalaj¹ca œcie¿kê pocz¹tkow¹ metod¹ zach³ann¹
};

