#pragma once
#include <vector>
#include "TabuList.h"
#include "Graph.h"
#include "GraphAlgorithms.h"


using namespace std;

class TabuSearch : public GraphAlgorithms
{
	int bestCost;			//najlepszy znaleziony koszt
	vector<int> bestPath;	//najlepsza znaleziona �cie�ka
	TabuList* tabuList;		//lista tabu
	int change[2];			//tablica na najlepszy znaleziony ruch
	vector<int> getNeighbour( vector <int> vect,int cadence);	//przeszukiwanie s�siedztwa
	void reset(vector <int>& vect);					//funkcja resetuj�ca, s�u�aca do dywersyfikacji
	vector<int> costToPrint; 
	vector<double> timeToPrint;
	
public :
	TabuSearch() {};
	Graph tabuSearch(Graph graph, int cadence, int endTime, int resetParametr);	//g��wny algorytm TabuSearch
	void print();
};

