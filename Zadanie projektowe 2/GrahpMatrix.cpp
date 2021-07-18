#include "GrahpMatrix.h"
#include<bits/stdc++.h>
#define INF 1000
using namespace std;
GraphMatrix::GraphMatrix(int v,int e,int s)
{
   matrix = new int * [v];
   for (int i = 0; i<v ;i++)
    matrix[i]= new int[v] ;

    for (int i = 0; i<v ;i++)
    {
        for (int j = 0; j<v ;j++)
        matrix[i][j]= INF;
    }
    cost = new int [v];
    path = new int[v];
    weightOfTree=0;
    numberOfNodes= v;
    numberOfEdges=e;
    start=s;
}

GraphMatrix::~GraphMatrix()
{
    for (int i = 0; i<numberOfNodes ;i++)
    delete [] matrix [i];

    delete [] cost;
    delete [] path;
    delete [] matrix;
    weightOfTree=0;
    numberOfNodes= 0;
    numberOfEdges = 0;

}

void GraphMatrix::print()
{
       for(int i = 0; i < numberOfNodes; i++)
        {
      for(int j = 0; j < numberOfNodes; j++)
        {
         cout <<" \t"<< matrix[i][j] << " ";
        }
      cout << endl;
        }
}

void GraphMatrix::addEdgeUndirected(int line, int column, int edge)
{
    matrix [line][column]= edge;
    matrix [column][line]= edge;
    weightOfTree+=edge;
    numberOfEdges++;

}

void GraphMatrix::addEdgeDirected(int line, int column, int edge)
{
    matrix [line][column]= edge;
numberOfEdges++;
    weightOfTree+=edge;
}

void GraphMatrix::addEdgesDirected(GraphMatrix & graph)
{

    int startNode, endNode, weight;

for( int i = 0; i < numberOfEdges; i++ )
  {
    cin >> startNode >> endNode >> weight; // Odczytujemy kolejne krawêdzie grafu
    graph.addEdgeDirected ( startNode, endNode, weight );             // i umieszczamy je w grafie
  }
}



void GraphMatrix::addEdgesUndirected(GraphMatrix & graph)
{

    int startNode, endNode, weight;

for( int i = 0; i < numberOfEdges; i++ )
  {
    cin >> startNode >> endNode >> weight; // Odczytujemy kolejne krawêdzie grafu
    graph.addEdgeUndirected ( startNode, endNode, weight );             // i umieszczamy je w grafie
  }

}


GraphMatrix GraphMatrix::mstForPrim( GraphMatrix & graph)
{
 bool * visited = new bool [ numberOfNodes ];   //tablica odwiedzin
 int* mst= new int[numberOfNodes];            // tablica na drzewo mst
 int* nextEdge= new int[numberOfNodes];        //tablica na wartosci krawędzi
GraphMatrix tree(numberOfNodes,numberOfEdges,0);

 for (int j=0; j<numberOfNodes;j++)  //inicjalizacja tablica
    {
    visited[j]=false;
    nextEdge[j]=INF;
    mst[j]=-1;
    }

nextEdge[0] = 0;        //ustalamy wierzchołek 0 jako startowym


for (int i=1; i<numberOfNodes;i++)
{

    int k = minKey(nextEdge,visited);       //szukamy wierzchołka dla którego wartość krwędzi jest najmniejsza
    visited[k]= true;                       //oznaczamy wierzchołek jako odwiedzony
    for ( int n =0 ; n < numberOfNodes; n++)
        {
            // graph.matrix[k][n]!=INF tylko jeśli jest sąsiadem
            // nextEdge[] jest aktualizowane gdy wartość graph.matrix[k][n] jest mniejsza od wartości nextEdge[n]
            if (graph.matrix[k][n]!=INF && visited[n] == false && graph.matrix[k][n] < nextEdge[n])
            {
                mst[n] = k;             //dodanie wierzchoła do mst
                nextEdge[n] = graph.matrix[k][n];
            }
        }
}
for (int i=1;i<numberOfNodes;i++)
tree.addEdgeDirected(mst[i],i,graph.matrix[i][mst[i]]);

return tree;
delete [] visited;
delete [] mst;
delete [] nextEdge;
}

int GraphMatrix::minKey(int edge[], bool mstSet[])
{
    int min = INF;      //min jako inf=1000
    int min_index;

    for (int v = 0; v < numberOfNodes; v++)
        if (mstSet[v] == false && edge[v] < min)    //jeśli wierzchołek nie jest odwiedzony i wartość krawędzi jest mniejsza niż min
            min = edge[v], min_index = v;           // przypisujemy min wartość krawędzi i ustalamy indeks wierzchołka

    return min_index;
}


int GraphMatrix::printPrimMST(int mst[], int **matrix)
{
    int mstCost=0;
	cout<<"Edge \t         Weight\n";
    for (int i = 1; i< numberOfNodes; i++) {
		cout<<"Edge: " <<mst[i]<<" - "<<i<<" \t"<< matrix[i][mst[i]]<<" \n";
		mstCost+=matrix[i][mst[i]];

    }
	cout<<"Minimal Spanning Tree Weight = "<<mstCost <<endl;
}


int GraphMatrix::findSet(int mst[], int v) //szukanie zbioru dla  wierzchołka v
{
    while(mst[v]!=v)                     //jeśli wierzchołka v nie ma w swoim pierwotnym zbiorze, znajdź zbiór w którym aktualnie się znajduje
        v = mst[v];

    return v;                               //zwróć numer zbioru w którym znajduje sie wierzchołek v
}



void GraphMatrix::unionOfSets(int mst[],int set1, int set2 )
{
    mst[findSet(mst,set1)] =findSet(mst,set2);          //połącz zbiory w których znaleziono wierzchołki o wspólnej krawędzi
}



GraphMatrix GraphMatrix::mstForKruskal(GraphMatrix & graph)
{
    int edge=0;

int* mst= new int[numberOfNodes];                 //tablica na zbiory
GraphMatrix tree(numberOfNodes,numberOfEdges,0);

    for (int i = 0; i < numberOfNodes; i++)      //każdemu wierzchołkowi przypisz zbiór w którym jest tylko on sam
        mst[i] = i;


    while ( edge < numberOfNodes - 1) {
        int min = INF;
        int a = -1;
        int b = -1;
        for (int i = 0; i < numberOfNodes; i++)
            {
            for (int j = 0; j < numberOfNodes; j++)
             {
                if (findSet(mst,i) != findSet(mst,j) && graph.matrix[i][j] < min)   //jeśli wierzchołek i nie należy do zbioru w którym jest wierzchołek j
                {                                                                   //oraz wartość krawędzi jest mniejsza od poprzedniej wartości
                    min = graph.matrix[i][j];                                       //to przypisz nową wartość i zapisz oba wierzchołki
                    a=i;
                    b=j;
                }
            }

        }

        tree.addEdgeDirected(a,b,min);
        unionOfSets(mst,a, b);                                                      //połącz zbiory w których znaleziono minimalną krawęd
        edge++;
    }

return tree;
delete [] mst;
}

void GraphMatrix::printEdge()
{

    cout<<"Edge \t        Weight\n";
for (int i=0;i<numberOfNodes;i++)
    for (int j=0; j<numberOfNodes;j++)
        if(matrix[i][j]!=INF)
		cout<<"Edge: " <<i<<" - "<<j<<" \t"<< matrix[i][j]<<" \n";

cout<<"Minimal Spanning Tree Weight = "<<weightOfTree <<endl;

}

void GraphMatrix::dijkstra(GraphMatrix & graph)
{

    bool * visited=new bool [numberOfNodes];        //zbiór początkowy który zawiera wszystkie wierzchołki


    for( int i= 0 ; i < numberOfNodes; i++)
{
    cost[i] = INF;          //ustalamy koszy dojścia do każdego wierzchołka na INF
    visited[i] = false;      //zbiór wierzchołków odwiedzonych na false
    path[i]=-1;
}

    cost[start]=0;          //wierzcholek startowy na 0

    for (int i = 0; i < numberOfNodes - 1; i++) {

        int u = minKey(cost, visited);  //szukamy najkrotszej sciezki do nieodwiedzonych wierzcholkow

        visited[u] = true;              //ustawiamy znaleziony wierzcholek na odwiedzony

        for (int v = 0; v < numberOfNodes; v++) //aktualizujemy sasiadow

            if (!visited[v] && graph.matrix[u][v] && cost[u] != INF // jesli wierzcholek v nie byl odwiedzony, koszt dojcia do wierzcholka u + wagag krawedzi
                && cost[u] + graph.matrix[u][v] < cost[v])          // jest mniejsza niz koszt dojscia do v
                {
                path[v] = u;
                cost[v] = cost[u] + graph.matrix[u][v];             //aktualizujemy koszt dojscia do v
                }
    }

    delete [] visited;
}

bool GraphMatrix::bellman(GraphMatrix & graph)
{
    int i;
    bool t;
    for(  i= 0 ; i < numberOfNodes; i++)
{
    cost[i] = INF;          //ustalamy koszy dojścia do każdego wierzchołka na INF
    path[i]=-1;
}


 cost[start] = 0;
int a=0;

  for( i = 1; i < numberOfNodes; i++ )
  {
      bool t=true;
    for( int v = 0; v < numberOfNodes; v++ ){ // Przechodzimy przez kolejne wierzchołki grafu
        for(int n=0;n< numberOfNodes;n++)
            if (graph.matrix[v][n]!=INF && cost[n]>cost[v]+graph.matrix[v][n])
                {
                    t= false;
                    path[n]=v;
                    cost[n]=cost[v]+graph.matrix[v][n];
                }
if (t)
    return true;
  }
}
 // Sprawdzamy istnienie ujemnego cyklu
for( int v = 0; v < numberOfNodes; v++ ) // Przechodzimy przez kolejne wierzchołki grafu
        for(int n=0;n< numberOfNodes;n++)
            if (graph.matrix[v][n]!=INF && cost[n]>cost[v]+graph.matrix[v][n])
                return false;

return true;

}

void GraphMatrix::printPath()
{

int i,j;
 int *S = new int [ numberOfNodes ];
  int sptr = 0;

    cout << "Start = " << start<<endl;
    cout << "End\tDist\tPath\t"<< endl;
    for( i = 0; i < numberOfNodes; i++ )
        {
        cout << " "<< i << " |\t "<< cost [i]<< " |\t";


        for( j = i; j > -1; j = path [ j ] ) //zapisujemy w tablicy pomocniczej ścieżkę od końca
            S [ sptr++ ] = j;

        while( sptr )
            cout << S [--sptr] << " "; //wyświetlamy ścieżkę

            cout <<endl;
        }


delete [] S;

}


void GraphMatrix::randomDirected(int nodes,float density)
{
    unsigned seed = chrono::steady_clock::now().time_since_epoch().count(); //ustawienie ziarna zegara
default_random_engine rd(seed);
mt19937 rng(rd());
uniform_int_distribution<int> dist(-50,50);
    int edges=(nodes*density*(nodes-1))/2;
    int max= (nodes*(nodes-1))/2;

vector<pair<int,int> > pairs1(max-nodes+1);
vector<pair<int,int> > pairs2(nodes-1);


int j=0;
int k=0;
int l=0;
for (int i=0;i<nodes;i++)
{
    j=i;
    while(j<nodes){
             if(j-i>1)
                {
               pairs1[k].first=i;
                pairs1[k].second=j;
                k++;
                }
            else if(j-i==1){
             pairs2[l].first=i;
                pairs2[l].second=j;

            l++;
             }
    j++;
    };
}

if (max-nodes +1==0)
        {
for (int i = 0;i<edges ;i++)
    addEdgeDirected(pairs2[i].first,pairs2[i].second,dist(rng));

        }
else
    {
    int * randInt= new int[max-nodes +1];
    int count=0;

srand(time(NULL));
   do
    {
        int value =  rand() % (max-nodes+1) ;
        if( ifWasRand( value, randInt, count ) == false )
        {
            randInt[ count ] = value;
            count++;
        } //if
    } while( count < max-nodes+1 );





vector<pair<int,int> > arr(nodes-1 + max-nodes+1);
    for (int i = 0; i < nodes-1 + max-nodes+1; i++)
    {
        if (i < nodes-1) {
            arr[i] = pairs2[i];
        }
        else {
            arr[i] = pairs1[randInt[i-nodes+1]];
        }
    }

for (int i = 0;i<edges ;i++){
    addEdgeDirected(arr[i].first,arr[i].second,dist(rng));

}
delete[] randInt;
arr.clear();


}
pairs1.clear();
pairs2.clear();

}



void GraphMatrix::randomUndirected(int nodes,float density)
{
     unsigned seed = chrono::steady_clock::now().time_since_epoch().count(); //ustawienie ziarna zegara
default_random_engine rd(seed);
mt19937 rng(rd());
uniform_int_distribution<int> dist(-50,50);
    int edges=(nodes*density*(nodes-1))/2;
    int max= (nodes*(nodes-1))/2;

vector<pair<int,int> > pairs1(max-nodes+1);
vector<pair<int,int> > pairs2(nodes-1);


int j=0;
int k=0;
int l=0;
for (int i=0;i<nodes;i++)
{
    j=i;
    while(j<nodes){
             if(j-i>1)
                {
               pairs1[k].first=i;
                pairs1[k].second=j;
                k++;
                }
            else if(j-i==1){
             pairs2[l].first=i;
                pairs2[l].second=j;

            l++;
             }
    j++;
    };
}

if (max-nodes +1==0)
        {
for (int i = 0;i<edges ;i++)
    addEdgeUndirected(pairs2[i].first,pairs2[i].second,dist(rng));

        }
else
    {
    int * randInt= new int[max-nodes +1];
    int count=0;

srand(time(NULL));
   do
    {
        int value =  rand() % (max-nodes+1) ;
        if( ifWasRand( value, randInt, count ) == false )
        {
            randInt[ count ] = value;
            count++;
        } //if
    } while( count < max-nodes+1 );






vector<pair<int,int> > arr(nodes-1 + max-nodes+1);
    for (int i = 0; i < nodes-1 + max-nodes+1; i++)
    {
        if (i < nodes-1) {
            arr[i] = pairs2[i];
        }
        else {
            arr[i] = pairs1[randInt[i-nodes+1]];
        }
    }

for (int i = 0;i<edges ;i++){
    addEdgeUndirected(arr[i].first,arr[i].second,dist(rng));

}
delete[] randInt;
arr.clear();


}
pairs1.clear();
pairs2.clear();

}

bool GraphMatrix::ifWasRand( int value1, int tab[], int value2 )
{
    if( value2 <= 0 )
         return false;

    int i = 0;
    do
    {
        if( tab[ i ] == value1 )
             return true;

        i++;
    } while( i < value2 );

    return false;
}

bool GraphMatrix::ifMinusWeight()
{
    for (int i=0;i<numberOfNodes;i++)
            for (int j=0;j<numberOfNodes;j++)
                if (matrix[i][j]<0)
                return true;

    return false;

}


