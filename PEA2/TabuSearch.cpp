#include "TabuSearch.h"
#include "Graph.h"
#include <iostream>
#include <ctime>

using namespace std;


vector<int> TabuSearch::getNeighbour(vector<int> vect, int cadence)
{
		tabuList->update();	//aktualizacja listy tabu
		
		vector<int> path(vect);
		bool aspiration = false;
		bool find = false;
		change[0] = 0;
		change[1] = 0;	
	
		//wylosowanie pocz�tkowej �cie�ki, dla danego s�siedztwa

		int nodeA = rand() % (size -1) +1 ;
		int nodeB = rand() % (size -1) + 1;

		while (nodeA == nodeB )
			nodeB = rand() % (size - 1)+1 ;

		swap(path[nodeA], path[nodeB]);
		
		
	for ( int i = 0 ; i< size*5;i++)
	 {
		vector<int> newPath(vect);
		aspiration = false;

		 nodeA = rand() % (size - 1) + 1;
		 nodeB = rand() % (size - 1) + 1;

		while (nodeA == nodeB)
			nodeB = rand() % (size - 1) + 1;
		
		swap(newPath[nodeA], newPath[nodeB]);
		
		//sprawdzenie kryteria aspiracji		
			if (tabuList->contains(nodeA, nodeB)&&getCostOfPath(newPath)<bestCost)
			{
				aspiration = true;
				path = newPath;
				
			}
			//je�li koszt nowej znalezionej �cie�ki jest mniejszy od kosztu starej �cie�ki, to zmieniamy �cie�k� na aktualn� 
			
			if (!aspiration && !tabuList->contains(nodeA, nodeB) && getCostOfPath(newPath) < getCostOfPath(path))
			{

						path = newPath;
						find = true;
						change[0] = nodeA;
						change[1] = nodeB;
						
			}
			
	}
	//dodanie ruchu do tablicy tabu
	if (find) 
		tabuList->insert(change[0], change[1], cadence);
	

	return path;
}

void TabuSearch::reset(vector<int> &vect)
{
	int nodeA = rand() % (size );		//generujemy dwie warto�ci r�ne od siebie
	int nodeB = rand() % (size ) ;
	

	while (nodeA == nodeB || (nodeA == 0 && nodeB == size) || (nodeB == 0 && nodeA == size ))
		nodeB = rand() % (size ) ;

	swap(vect[nodeA], vect[nodeB]);
 
	if (nodeA == 0 || nodeA == size)
	{
		vect[0] = vect[nodeA];
		vect[size] = vect[nodeA];
	}
	else if (nodeB == 0 || nodeB == size )
	{
		vect[0] = vect[nodeB];
		vect[size] = vect[nodeB];
	}
	

}

Graph TabuSearch::tabuSearch(Graph graph, int cadence, int endTime, int resetParametr)
{
	double time = 0;	//zmienna licz�ca czas trwania algorytmu
	this->graph = graph;
	size = graph.getSize();
	this->tabuList = new TabuList();	//utworzenie listy tabu
	int tabuNotChange = 0;
	int currentCost;
	GraphAlgorithms g;		//obiekt pomocniczy, do znalezenia pocz�tkowej �cie�ki
	vector < vector<int> > startPath;	//wektora na �cie�ki pocz�tkowe
	//wyznaczenie pocz�tkowej �cie�ki metod� zach�ann�

	currentPath = g.getMin(graph).getSolution();

	//przypisanie najlepszej �cie�ce, znalezion� scie�k�

	bestPath = currentPath;

	startPath.push_back(bestPath);

	bestCost = getCostOfPath(bestPath);
	

	clock_t begin = clock();
	while(time < endTime)
	{
		//znalazeienie s�siedztwa i policzenie kosztu
		currentPath = getNeighbour(currentPath, cadence);
		currentCost= getCostOfPath(currentPath);	
		
		//je�li znaleziony koszt jest lepszy, zapisujemy go, w przeciwnym wypadku inkrementujemy zmienn� dla funkcji  reset
		if (currentCost < bestCost)
		{
			bestPath = currentPath;
			bestCost = currentCost;
			tabuNotChange = 0;
			costToPrint.push_back(bestCost);
			timeToPrint.push_back(time);
		}
		else
		{
			tabuNotChange++;	
		}	
		
		//funkcja restartuj�ca je�li przez k iteracji nie znaleziono nowego rozwi�zania
		if (tabuNotChange == resetParametr)
		{
			
			bool b = false;
			do {
				for (int i = 0; i < 3*size; i++)
					reset(currentPath);

				if (!count(startPath.begin(), startPath.end(), currentPath))
					b = true;
			}while(!b);

			startPath.push_back(currentPath);
			if (getCostOfPath(currentPath) < bestCost)
			{
				bestPath = currentPath;
				bestCost = currentCost;
			}
			tabuNotChange = 0;
			tabuList->clear();
		}
		clock_t end = clock();
		double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		time = elapsed_secs;
		
	}

	delete tabuList;
	graph.updateSolution(bestPath);
	return  graph;

}

void TabuSearch::print()
{
	cout << "Droga    Czas" << endl;
	for (int i = 0; i<costToPrint.size();i++)
		cout << costToPrint[i]<< "    " << timeToPrint[i] << endl;

	cout << endl;
	costToPrint.clear();
	timeToPrint.clear();
}