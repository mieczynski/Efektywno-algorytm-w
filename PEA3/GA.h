#pragma once
#include "GraphAlgorithms.h"

class GA : public GraphAlgorithms
{
private:

	int countOfCities;
	int populationSize;
	int parentsPopulationSize;
	double mutationProbability;
	double crossoverProbability;
	vector<vector<int>> population;
	vector<vector<int>> parents;
	vector<vector<int>> childrens;
	vector<int> costToPrint;
	vector<double> timeToPrint;

	void initialization();
	void getStartedPopulation();
	vector<vector<int>>  getNewPopulation();
	void generatePermutation(vector<int>& parents);
	void getParents();
	void crossingAndMutate();
	vector <int> randParents(int min, int max, int count);
	void mutate(vector<int>& child);
	vector<int> getBestSolutionFromPopulation();



public:
	GA();
	~GA() {};
	int bestSolution;
	vector<int> bestOrder;
	Graph GeneticAlgorithm(Graph graph, int endTime, double mutationProb , double crossoverProb, int populationSize);
	void print();


};

