#pragma once
#include <vector>

using namespace std;
class Graph
{

	
private:
	int size;
	vector<vector<int>> adjMatrix;	//macierz s�siedztwa
	vector<int> solution;			//wektora na najlepsz� znalezion� �cie�k�
	int costOfPath;					//koszt najlepszej znalezionej �cie�ki
public:
	
	Graph() {};
	Graph(int size);
	~Graph();
	void setGraph(vector<vector<int>>& matrix);	//ustawianie tablicy po wczytaniu z pliku
	int getSize() { return size; }
	vector<int> getSolution()  { return solution; };
	void updateSolution(vector<int> solution);	//aktualizacja �cie�ki
	int getEdge(int i, int j)  { return adjMatrix[i][j]; };
	int getCost() { return costOfPath; };
	
};

