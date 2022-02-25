#include "TabuList.h"
#include <iostream>
using namespace std;

bool TabuList::contains(int nodeA, int nodeB)
{ 
	bool contains = false;

	for (list<pair<pairOfNodes, int>>::iterator it = tabuList.begin(); it != tabuList.end(); ++it)
		if (it->first.nodeA == nodeA && it->first.nodeB == nodeB && it->second > 0) 
			contains = true;
	
	return contains;
}


void TabuList::insert(int nodeA, int nodeB, int cadence)
{
	pairOfNodes nodes;
	nodes.nodeA = nodeA;
	nodes.nodeB = nodeB;
	
	tabuList.push_back(make_pair(nodes, cadence));

}

void TabuList::update()
{
	list<pair<pairOfNodes, int>>::iterator it = tabuList.begin();
	while (it != tabuList.end())
	{
		it->second = it->second - 1;
		if (it->second == 0) {
			tabuList.erase(it++);
		}
		else
		++it;
	}
	
}

