#pragma once
#include <vector>
using namespace std;
class Node
{
	

public:
	
	int cost;				//koszt dojscia do danego wezla
	int numberOfVertex;		//iloœæ wierzcho³ków
	int** matrix;			//macierz dla kazdego wezla
	vector <int> pathToPrint;	//wektor na œcie¿kê

private:
	
	int currentNode;		//liczba oznaczajaca aktualny wezel
	int tier;				//liczba oznaczajaca ile wezlow pozostalo do konca

public:
	Node(int N);
	~Node();
	void reductionInLine(int **reducedMatrix, int* costOfLine);	
	void reductionInColumn(int** reducedMatrix, int* costOfColumn);
	void matrixSetting(int** previousMatrix, int startNode, int endNode,int tier, vector<int> path);
	void costOfWayToNode();	//koszta dojœcia do wierzchoka
	void print();
	int BranchAndBound(int** startMatrix);
	void printPath();
	void setGraph(vector<vector<int>>& matrix);	//ustawienie macierzy po wczytaniu z pliku

};

