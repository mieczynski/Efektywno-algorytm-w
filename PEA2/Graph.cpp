#include "Graph.h"


Graph::Graph(int size)
{
    this->size = size;

    adjMatrix.resize(size);

    for (int i = 0; i < size; i++)
        adjMatrix[i].resize(size);

    solution.reserve(size);
}
  
Graph::~Graph()
{
    for (int i = 0; i < size; i++)
        adjMatrix[i].resize(0);

    adjMatrix.resize(0);
 
    size = 0;

}
void Graph::setGraph(vector<vector<int>>& matrix)
{
    adjMatrix = matrix;
}

void Graph::updateSolution(vector<int> solution)
{
    this->solution = solution;

    costOfPath = 0;

    for (int i = 0; i < solution.size() - 1; i++)
    {
        costOfPath += adjMatrix[solution[i]][solution[i + 1]];
    }

}