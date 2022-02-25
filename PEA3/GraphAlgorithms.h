#pragma once
#include "Graph.h"

using namespace std;

class GraphAlgorithms
{
protected:
	int size;
	vector <int> currentPath;				//aktualnie znaleziona �cie�ka
	int getCostOfPath(vector <int> path);		//metoda zwracaj�ca koszt �cie�ki
	Graph graph;

public:
	GraphAlgorithms() {};
	~GraphAlgorithms() {};
	Graph getMin(Graph graph);	//metoda ustalaj�ca �cie�k� pocz�tkow� metod� zach�ann�
};

