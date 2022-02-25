#include "Node.h"
#include <iostream>
#include <queue>
#include <vector>
#define INF 1000

using namespace std;

Node::Node(int v)
{
    
    matrix = new int* [v];
    for (int i = 0; i < v; i++)
        matrix[i] = new int[v];

    for (int i = 0; i < v; i++)
    {
        for (int j = 0; j < v; j++)
            matrix[i][j] = INF;
    }
    currentNode = 0;
    numberOfVertex = v;
    cost = 0;
    tier = 0;
}

Node::~Node()
{
    for (int i = 0; i<numberOfVertex ;i++)
        delete [] matrix [i];

    delete [] matrix;
    numberOfVertex = 0;

}
void Node::setGraph(vector<vector<int>>& matrix1)
{
    for (int i = 0; i < numberOfVertex; i++)
        for (int j = 0; j < numberOfVertex; j++)
            matrix[i][j] = matrix1[i][j];

}

//zapamiętanie ścieżki i zamiana wartości w tablicy na INF
void Node::matrixSetting(int **previousMatrix, int startNode, int endNode,int tier1, vector<int> path)
{
    pathToPrint = path;
       

    pathToPrint.push_back(endNode);

    for (int i = 0; i < numberOfVertex; i++)
        for (int j = 0; j < numberOfVertex; j++)
            matrix[i][j] = previousMatrix[i][j];

   if (startNode == 0 && endNode == 0) return;

    for (int i = 0; i < numberOfVertex; i++)
    {
        matrix[startNode][i] = INF;
        matrix[i][endNode] = INF;

    }

    matrix[endNode][0]  = INF;
    currentNode = endNode;
    tier= tier1;
   
    
}

//redukacja i koszt w wierszach
void Node::reductionInLine(int** reducedMatrix, int* costOfLine)
{
  
    int min = INF;
  
    for (int i = 0; i < numberOfVertex; i++)
    {
        for (int j = 0; j < numberOfVertex; j++)
            if (reducedMatrix[i][j] < min)
                min = reducedMatrix[i][j];

        costOfLine[i] = min;
        min = INF;
    }
   
    for (int i = 0; i < numberOfVertex; i++)
        for (int j = 0; j < numberOfVertex; j++)
        { 
            if  (reducedMatrix[i][j] != INF)
             reducedMatrix[i][j] -= costOfLine[i];
        }

}

//redukacja i koszt w kolumnach
void Node::reductionInColumn(int **reducedMatrix, int *costOfColumn)
{


    int min = INF;

    for (int i = 0; i < numberOfVertex; i++)
    {
        for (int j = 0; j < numberOfVertex; j++)
            if (reducedMatrix[i][j] < min)
                min = reducedMatrix[i][j];

        costOfColumn[i] = min;
        min = INF;
    }

    for (int i = 0; i < numberOfVertex; i++)
        for (int j = 0; j < numberOfVertex; j++)
        {
            if (reducedMatrix[i][j] != INF)
                reducedMatrix[i][j] -= costOfColumn[i];
        }
    

}
//obliczanie kosztu dojścia do syna
void Node::costOfWayToNode()
{
    int* costOfLine = new int[numberOfVertex];
    int* costOfColumn = new int[numberOfVertex];
    
    reductionInColumn(matrix, costOfColumn);
    reductionInLine(matrix, costOfLine);

 
    for (int i = 0; i < numberOfVertex; i++) 
    {
        if (costOfColumn[i] != INF) 
            cost += costOfColumn[i];
       
        if (costOfLine[i] != INF) 
          cost += costOfLine[i];
    }

  
    delete [] costOfColumn;
    delete [] costOfLine;
}
void Node::print()
{
    for (int i = 0; i < numberOfVertex; i++)
    {
        for (int j = 0; j < numberOfVertex; j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }
  
   cout << endl;
}

//comperator dla kolejki priorytetowej
struct comperator
{
    bool operator()(const Node* node1, const Node* node2) const 
    {
        return node1->cost > node2->cost;
    }
};


int Node::BranchAndBound(int** startMatrix)
{
    
    priority_queue <Node*,vector<Node*>, comperator> quene;  //kolejka priorytetowa na kolejne wierzcholki

    Node* root = new Node(numberOfVertex);          //utworzenie korzenia
    vector <int> p;

    root->matrixSetting(startMatrix, 0,0,0, p);         //ustawienie parametrow korzenia
   
    root->costOfWayToNode();                        //policzenie kosztu korzenia

    quene.push(root);       //dodanie korzenia do kolejki
  
 
   
  
   while (!quene.empty())
    {
        Node* minimalCostNode = quene.top();    //sciagniecie z kolejki wierzcholka o minimalnym koszcie
        quene.pop();            //usuniecie znalezionego wierzcholka z kolejki

        
        if (minimalCostNode->tier == numberOfVertex - 1) {  //warunek konczacy petle, jesli wszystkie miasta zostaly odwiedzone
            minimalCostNode->pathToPrint.push_back(0);
            minimalCostNode->printPath();
            return minimalCostNode->cost;
        }
            
        
        int i = minimalCostNode->currentNode;
 
       // pętla przechodząca przez wszystkich synów danego wierzchołka
        for (int j = 0; j < numberOfVertex; j++)
        {
            if ( minimalCostNode->matrix[i][j] != INF)
            {
                Node* son = new Node(numberOfVertex);    
                son->matrixSetting(minimalCostNode->matrix, i, j, minimalCostNode->tier + 1, minimalCostNode->pathToPrint);
                son->costOfWayToNode();
                son->cost = minimalCostNode->cost + minimalCostNode->matrix[i][j] + son->cost;
                quene.push(son);  
            }
     
        }
      
        delete minimalCostNode;
    }

}

void Node::printPath()
{
    cout << "Sciezka:" << endl;
    for (int i : pathToPrint)
        cout << i << " - > ";

}