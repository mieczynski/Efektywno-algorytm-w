#include "Graph.h"
#include <iostream>

#include <algorithm>
#define INF 1000;
#define ZERO 0;
using namespace std;
Graph::Graph(int v)
{
    startMatrix = new int* [v];
    for (int i = 0; i < v; i++)
        startMatrix[i] = new int[v];

        path.reserve(numberOfVertex);
  
    numberOfVertex = v;
}

Graph::~Graph()
{
    for (int i = 0; i < numberOfVertex; i++)
        delete[] startMatrix[i];

    delete[] startMatrix;
    path.resize(0);
    numberOfVertex = 0;
}

void Graph::setGraph(vector<vector<int>>& matrix)
{
    for (int i = 0; i < numberOfVertex; i++)
        for (int j = 0; j < numberOfVertex; j++)
            startMatrix[i][j] = matrix[i][j];
 

}




void Graph::print()
{
    for (int i = 0; i < numberOfVertex; i++)
    {
        for (int j = 0; j < numberOfVertex; j++)
            cout << startMatrix[i][j] << " ";
        cout << endl;
    }

    cout << endl;
}
//utworzenie podzbiorów
void Graph::makeSubsets(int currentVertex)
{
   if (currentVertex > numberOfVertex-1)        //warunek koñcz¹cy rekurencje
       return;

    vector<int> subset;
    if (currentVertex == 1)     //utworzenie pustego zbioru i zbioru dla 1 wierzcho³ka
    {
        allOfSubsets.push_back(subset);		
        subset.push_back(1);			       
        allOfSubsets.push_back(subset); //dodanie podzbioru do wektora na wszystkie podzbiory
        subset.clear();
        makeSubsets(currentVertex + 1); //wywo³anie rekurencji
        return;
    }

   
    int size = allOfSubsets.size();  //zapamiêtanie rozmiaru wektora wszystkich podzbiorów
   
    for (int i = 0; i < size; i++)  //pêtla tworz¹ca resztê podzbiorów
    {
        subset = allOfSubsets[i];
        subset.push_back(currentVertex);
        allOfSubsets.push_back(subset);
    }
    subset.clear();
    makeSubsets(currentVertex + 1);
}
// koszt dojœcia do wierzcho³ka przechodz¹c przez wierzcho³ki z podzbioru
int Graph::getCost(vector<int> subset, int previousV)
{
    subset.erase(find(subset.begin(), subset.end(), previousV));    //usuniêcie wierzcho³ka z podzbioru

    Index t;        //zmienna pomocnicza
    t.subset = subset;
    t.currentVertex = previousV;
    
    return minCost.at(t);   //zwrócenie kosztu 
}


void Graph::clear()
{
    allOfSubsets.clear();
}


int Graph::HeldKarp(int startV)
{
    path.clear();       //czyszczenie œcie¿ki
    makeSubsets(1);     //utworzenie wszystkich podzbiorów i posortowanie ich wed³ug rozmiarów
    sort(allOfSubsets.begin(), allOfSubsets.end(), [](const vector<int>& set1, const vector<int>& set2)
        {
            return set1.size() < set2.size();
        }
    );


    for (int i = 0; i < allOfSubsets.size(); i++) //pêtla przechodz¹ca przez wszystkie podzbiory 
    {    
        for (int currentVertex = 1; currentVertex < numberOfVertex; currentVertex++) //przejœcie przez wszystkie wierzcho³ki w danym podzbiorze
        {
          
            if (find(allOfSubsets[i].begin(), allOfSubsets[i].end(), currentVertex) != allOfSubsets[i].end())   //jeœli dany wierzcho³ek znajduje siê w danym podzbiorze to kontunuujemy
                continue;

            int parentOfCurrentVertex = 0;  
            int min = INF;
            for (int vertexFromCurrentSet = 0; vertexFromCurrentSet < allOfSubsets[i].size(); vertexFromCurrentSet++) //iterowanie po elementach podzbioru, koñcz¹c na  aktualnym wierzcho³ku
            {
                int cost = getCost(allOfSubsets[i], allOfSubsets[i][vertexFromCurrentSet])+ startMatrix[allOfSubsets[i][vertexFromCurrentSet]][currentVertex];
                
               
                if (cost < min) 
                {
                    min = cost;
                    parentOfCurrentVertex = allOfSubsets[i][vertexFromCurrentSet]; 
                }

            }
            if (allOfSubsets[i].size() == 0)
            {
                min = startMatrix[0][currentVertex];
                parentOfCurrentVertex = 0;
               
            }

            Index t;
            t.currentVertex = currentVertex;
            t.subset = allOfSubsets[i];
            
            parents.insert(make_pair(t, parentOfCurrentVertex));
            minCost.insert(make_pair(t, min));

        }

    } 

    //znalezielnie kosztu powrotu do wierzcho³ka startowego
    Index t;
    vector<int> subset = allOfSubsets[allOfSubsets.size() - 1];
    t.subset = subset;  
    int allCost ;
    int min = INF
    for (int i = 1; i < numberOfVertex; i++)		
    {
        allCost = startMatrix[i][startV] + getCost(t.subset, i);
     
        if (min > allCost)
        {
           min = allCost;
            t.currentVertex = i;
           
        } 
    }

//odtworzenie œcie¿ki
   
    path.push_back(startV);
    path.push_back(t.currentVertex);

    int parentVertex = 0;

  

    subset.erase(find(subset.begin(), subset.end(), t.currentVertex));
    t.subset = subset;

    do
    {
        parentVertex = parents.at(t);// znajdujemy poprzedni odwiedzony wierzcho³ek
        path.push_back(parentVertex);   //dodajemy go do œcie¿ki
        subset.erase(find(subset.begin(), subset.end(),parentVertex));    //usuwamy wierzcho³ek ze zbioru
        t.subset = subset;  //aktualizaujmy zmienn¹ pomocnicz¹
        t.currentVertex = parentVertex; 

    } while (path.size() != numberOfVertex);
    
    path.push_back(startV);

    return min;
}
   


int Graph::BruteForce(int startV)
{
    path.clear();
    vector<int> nodes;
    nodes.reserve(numberOfVertex);

    for (int i = 0; i < numberOfVertex; i++)    //zapamietane wszystkich sciezek wychodzacych z wierzcholka startV
        if (i != startV) {
            nodes.push_back(i);
        }
        
    int minPath = INF;


     //petla wykonuje sie dopoki w wekotrze v istnieja niewykonane permutacje                     
    do
    {  
        int currentPath = 0;

        int i = startV;         //ustawienie aktualneo wierzcholka
       
        for (int j = 0; j < nodes.size(); j++) {    //przejscie przez wszystkie miasta i dodanie 
            currentPath += startMatrix[i][nodes[j]];        //aktualizaja sciezki
            i = nodes[j];               //zmiana poczatkowego wierzcholka, na nastepny wynikajacy z permutaacji
          
        }
       
        currentPath += startMatrix[i][startV];      //powrot do wierzcholka poczatkowego
        
        if (minPath > currentPath) {  
           //jesli znaleziona sciecka jest mniejsza od dotychczasowej najmniejszej sciezki, to uaktualniamy
            minPath = currentPath;
            path = nodes;

        }

       
    } while (next_permutation(nodes.begin(), nodes.end()));
    path.insert(path.begin(), 0);
    path.push_back(0);
    return minPath;
}



void Graph::printPathForHeld()
{

    for (int i = path.size()-1 ; i >= 0; i--) {
      cout << path[i] << " - > ";
    }
}

void Graph::printPathForBrute()
{

    for (int i = 0 ; i < path.size(); i++) {
        cout << path[i] << " - > ";
    }
}