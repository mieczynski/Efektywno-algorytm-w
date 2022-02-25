#include "GA.h"
#include <algorithm>
#include <iostream>


GA::GA()
{
	crossoverProbability = 0.8;
	mutationProbability = 0.01;

}


void GA::initialization()
{
	bestSolution = INT_MAX;
	population.reserve(populationSize);
	parents.reserve(parentsPopulationSize);
	childrens.reserve(populationSize);
	parentsPopulationSize = 0.75 * populationSize;


}

//losowanie permutacji
void GA::generatePermutation(vector<int>& permutation)
{
	for (int i = 0; i < countOfCities; i++)
		permutation[i] = i;

	random_shuffle(permutation.begin(),permutation.end());
	permutation.push_back(permutation.at(0));
	
}

//wybór populacji startowej
void GA::getStartedPopulation()
{
	for (int i = 0; i < populationSize; i++) 
	{
		vector<int> permutation(countOfCities);
		generatePermutation(permutation);
		population.push_back(permutation);
	}
	
}


//metoda mutacji, Scramble mutation
void GA::mutate(vector<int>& child)
{
	int startOfSegment;
	int endOfSegment;
	
	do {
		startOfSegment = rand() % countOfCities;
		endOfSegment = rand() % countOfCities;
	} while (startOfSegment == endOfSegment);
	
	if (startOfSegment > endOfSegment) {
		int temp = startOfSegment;
		startOfSegment = endOfSegment;
		endOfSegment = temp;
	
	}


	random_shuffle(child.begin()+startOfSegment , child.end() - (child.size() - endOfSegment) );

}


//funkcja losoj¹ca zadan¹ liczbê osobników, zadanego przedzia³u		
vector <int> GA::randParents(int min, int max, int count)
{
	srand(time(NULL));
	vector < int > vect;
	vect.reserve(count);

	if (count > max) {
		for (int i = 0; i < max; i++)
			vect.push_back(i);

		do
		{

			vect.push_back(min);
			min++;
		} while (min != count - max);

	}
	else
	{
	do
	{

		vect.push_back(min);
		min++;
	} while (min != max);
}
	random_shuffle(vect.begin(), vect.end());

	
	int size = vect.size();

	for (int i = 0; i < size - count; i++)
		vect.pop_back();


	return vect;


}

void GA::getParents()
{

	srand(time(NULL));
	parents.clear();
	vector <pair<int, int>> valueOfEachPermutation;
	//podzielenie populacji na 4 grupy w zale¿noœci od d³ugoœci œcie¿ki
	int countOfRanks = 4;
	int sizeOfRanks = populationSize / countOfRanks;
	int cost;

	//przypisanie ka¿dej grupie liczbê osobników, które bêd¹ rodzicami
	vector <int>ranks;
	//z pierwszej grupy, bêdzie pochodziæ 55% rodziców
	int percent = 0.55 * parentsPopulationSize;
	ranks.push_back( percent);
	//z drugiej grupy, bêdzie pochodziæ 30% rodziców
	percent = 0.3 * parentsPopulationSize;
	ranks.push_back(percent);
	//z trzeciej grupy, bêdzie pochodziæ 10% rodziców
	percent = 0.1* parentsPopulationSize;
	ranks.push_back(percent);
	//z czwartej grupy, bêdzie pochodziæ 5% rodziców
	percent = 0.05 * parentsPopulationSize;
	ranks.push_back(percent);
	int sumOfPercent = 0;


	//zabezpieczenie dla ró¿nicy miêdzy zadan¹ populacj¹ rodziców
	//a liczb¹ rodziców wynikaj¹c¹ z poszczególnych grup
	for (int i = 0; i < countOfRanks; i++)
		sumOfPercent = sumOfPercent + ranks[i];

	while (sumOfPercent != parentsPopulationSize) {
		ranks[0]++;
		sumOfPercent++;
	}
	
	//obliczenie kosztu dla ka¿dego osobnika z populacji
	for (int i = 0; i < populationSize; i++) {
		cost = getCostOfPath(population[i]);
		valueOfEachPermutation.push_back(make_pair(i, cost));
		
	}

	//sortowanie osobników wg d³ugoœci œcie¿ki
	sort(valueOfEachPermutation.begin(), valueOfEachPermutation.end(), [this](const pair<int, int>& a,
		const pair<int, int>& b)->bool {return a.second < b.second; });
	

	
	int k = 0;
	int j = 0;
	int countOfParentsPerRank;
	
	//losowanie rodziców z poszczególych grup rankingowych i dodawanie ich do wektora rodziców
	for (int i = 0; i < countOfRanks; i++)
	{
		countOfParentsPerRank = ranks.at(i);
		
		for (int p : randParents(j, j + sizeOfRanks, countOfParentsPerRank))
		{
			
			parents.push_back(population[valueOfEachPermutation.at(p).first]);
			
		}
		j =j + sizeOfRanks;
	
	}


}


//krzy¿owanie rodziców oparte jest na idei Order crossover( OX, Davis, 1985)
void GA::crossingAndMutate()
{
	
	//wybór rodziców
	vector<int> parent1 = parents.at(rand() % parentsPopulationSize);
	vector<int> parent2 = parents.at(rand() % parentsPopulationSize);

	vector<int> child1(countOfCities);
	vector<int> child2(countOfCities);


	//losowanie pocz¹tku i koñca segmentu 
	int startOfSegment;
	int endOfSegment;

	do {
		startOfSegment = rand() % countOfCities;
		endOfSegment = rand() % countOfCities;
	} while (startOfSegment == endOfSegment);


	if (startOfSegment > endOfSegment) {
		int temp = startOfSegment;
		startOfSegment = endOfSegment;
		endOfSegment = temp;
	}

	//skopiowanie danego segmentu od rodziców do dzieci
	for (int i = startOfSegment; i <= endOfSegment; i++) {
		child1[i] = parent1[i];
		child2[i] = parent2[i];

	}	
	vector<int> temp1;
	vector<int> temp2;
	temp1.reserve(countOfCities);
	temp2.reserve(countOfCities);
	
	bool isOnList1 = false;
	bool isOnList2 = false;

	
	int pos = endOfSegment;

	//skopiowanie kolejnoœci miast zaczynaj¹c od koñca segmentu
	for (int i = 0; i < countOfCities; i++)
	{
		if (pos == countOfCities-1)
			pos = 0;
		else
			pos++;


		temp1.push_back(parent1.at(pos));
		temp2.push_back(parent2.at(pos));

	}



	//sprawdzenie czy miasto znajduje siê w segmencie oraz wstawienie reszty miast do potomka
	for (int i = 0; i < countOfCities; i++)
	{
		isOnList1 = false;
		isOnList2 = false;

		for (int j = startOfSegment; j <= endOfSegment; j++) {
			if (temp1[i] == child2[j])
				isOnList1 = true;
			if (temp2[i] == child1[j]) 
				isOnList2 = true;
			

		}

		if (isOnList1)
			temp1[i] = -1;
		if (isOnList2)
			temp2[i] = -1;

	}

		pos = endOfSegment + 1;
	for (int i = 0; i < countOfCities; i++) {
		if (pos == countOfCities ) 
			pos = 0;

		if (temp2[i] != -1) 
		{
			child1[pos] = temp2[i];
			pos++;
		}
		

	}

	
	pos = endOfSegment + 1;

	for (int i = 0; i < countOfCities; i++) {
		if (pos == countOfCities)
			pos = 0;

		if (temp1[i] != -1)
		{
			child2[pos] = temp1[i];
			pos++;
		}

	}


	//wylosowanie 2 liczb
	double r1 = (double)rand() / (double)RAND_MAX;
	double r2 = (double)rand() / (double)RAND_MAX;

	//jeœli  wylosowana liczba jest mniejsza od prawdopodobieñstwa mutacji, to nastêpuje mutacja
	if (r1 < mutationProbability)
		mutate(child1);
	
	if (r2 < mutationProbability)
		mutate(child2);
	
	//dodanie powrotu do wierzcho³ka startowego 
	child1.push_back(child1[0]);
	child2.push_back(child2[0]);
	
	//dodanie nowego dziecka do wektora dzieci
	childrens.push_back(child1);
	childrens.push_back(child2);

	temp1.resize(0);
	temp2.resize(0);
	child1.resize(0);
	child2.resize(0);
	
	
}

vector<vector<int>>  GA::getNewPopulation()
{
	vector<vector<int>> newPopulation;
	newPopulation.reserve(populationSize);

	//sortowanie starej populacji 
	sort(population.begin(), population.end(), [this](auto i, auto j)->bool {return getCostOfPath(i) > getCostOfPath(j); });


	//dodanie dzieci do populacji
	// liczba dzieci stanowi %(crossoverProbability) nowej populacji	
	for (int i = 0; i < crossoverProbability * populationSize; i++) {
		newPopulation.push_back(childrens.back());
		childrens.pop_back();

	}

		int size = newPopulation.size();

	//dodanie najlepszych osobników ze starej populacji 
	for (int i = 0; i < populationSize - size; i++)
	{
		newPopulation.push_back(population.back());
		population.pop_back();
	}
	
		return newPopulation;

}

vector<int> GA::getBestSolutionFromPopulation()
{

	return population.front();

}


Graph GA::GeneticAlgorithm(Graph graph, int endTime, double mutationProb, double crossoverProb, int size)
{
	srand(time(NULL));;
	this->graph = graph;
	countOfCities = graph.getSize();
	populationSize = size;
	mutationProbability = mutationProb;
	crossoverProbability = crossoverProb;

	double time = 0;	//zmienna licz¹ca czas trwania algorytmu
	initialization();	//inicjalizacja wektorów
	getStartedPopulation();	// losowewybranie pocz¹tkowej populacji
	vector<int> currnetOrder;
	int currentBest;
	clock_t begin = clock();



	while (time < endTime) {

			getParents(); //wybór rodziców

		for (int i = 0; i < (populationSize * crossoverProbability) / 2; i++)
			crossingAndMutate(); // krzy¿owanie i mutacja powsta³ych dzieci
		population = getNewPopulation();	//utworzenie nowej populacji z powsta³ych dzieci i reszty populacji

		//znalezienie najlepszego osobnika z nowej populacji
		currnetOrder = getBestSolutionFromPopulation();
		currentBest = getCostOfPath(currnetOrder);
		
		//sprawdzenie czy nowe rozwi¹zanie jest lepsze, jeœli tak zapamiêtanie go 
		if (currentBest < bestSolution)
		{
			bestSolution = currentBest;
			bestOrder = currnetOrder;
			costToPrint.push_back(bestSolution);
			timeToPrint.push_back(time);
		}
		clock_t end = clock();
		double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		time = elapsed_secs;
		
	}

	population.clear();
	childrens.clear();
	parents.clear();
	graph.updateSolution(bestOrder);
	return  graph;

}
void GA::print()
{

	cout << "Droga    Czas" << endl;
	for (int i = 0; i < costToPrint.size(); i++)
		cout << costToPrint[i] << "    " << timeToPrint[i] << endl;


	

	costToPrint.clear();
	timeToPrint.clear();
}