#pragma once
#include <list>

using namespace std;
	struct pairOfNodes
{
	int nodeA;
	int nodeB;
};
class TabuList
{
	
private:
	list<pair<pairOfNodes,int>> tabuList;	//lista tabu
	
public:
	TabuList() {};
	~TabuList() { tabuList.clear(); };
	bool contains(int nodeA, int nodeB);	//sprawdzenie czy dany ruch znajduje siê na liœcie
	void insert(int nodeA, int nodeB, int cadence); //dodawanie elementu do listy
	void clear() { tabuList.clear(); };	//czyszczenie listy tabu
	void update();	//aktualizowanie listy tabu
};


