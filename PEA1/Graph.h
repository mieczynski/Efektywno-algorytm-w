#pragma once
#include <vector>
#include <unordered_map>
using namespace std;

//klasa index pozawala potrzebna do u¿ycia unordered_map
class Index {
public:
	int currentVertex;
	vector<int> subset;

	bool operator==(const Index& other) const
	{
		return subset == other.subset && currentVertex == other.currentVertex;
	}

};
//funkcja hashuj¹ca tworzy unikalny klucz dla unordered_map
class hashFunction {
public:
	size_t operator()(const Index& index) const
	{
		size_t res = 0;

		for (int i = 0; i < index.subset.size(); i++)
			res = res*17+ hash<int>()(index.subset[i]);
			res = res * 17 + hash<int>()(index.currentVertex);

		return res;
	}
};
class Graph
{

public:
	int numberOfVertex;	//iloœæ wierzcho³ków
	int** startMatrix;	//tablica startowa

private:
	vector <int> path;		//wektor na œcie¿kê
	vector <vector<int>> allOfSubsets;		//wektor na wszystkie mo¿lwie podzbiory
	unordered_map<Index, int, hashFunction> minCost;	//mapa potrzebna do znalezielnia minimalnego kosztu
	unordered_map<Index, int, hashFunction> parents;	//mapa potrzebna do wyznaczenia œcie¿ki
public:
	Graph(int N);
	~Graph();
	int HeldKarp( int startV);
	int getCost(vector<int> subset, int previousV);	//koszt dla HeldKarpa
	void makeSubsets(int firstNode);	//tworzenie podzbiorow dla HeldaKarpa
	int BruteForce(int startV);
	void printPathForHeld();
	void printPathForBrute();
	void clear();	//czysczenie podzbiorów
	void setGraph(vector<vector<int>> &matrix);	//ustawianie tablicy po wczytaniu z pliku
	void print();
};

