#include "Graph.h"
#include<sstream>
#include<string>
#include<fstream>
#include<bits/stdc++.h>

#define INF 1000
using namespace std;

DSet::DSet ( int n )
{
  arrayOfSets = new DSNode [ n ];    // Tworzymy tablicê dla elementów zbiorów
}

// Destruktor

DSet::~DSet()
{
  delete [ ] arrayOfSets ;            // Usuwamy tablicê ze zbiorami
}

// Tworzy wpis w tablicy Z

void DSet::MakeSet ( int node )
{
  arrayOfSets [ node ].dsNode   = node;
  arrayOfSets [ node ].weightOfSet = 0;
}

// Zwraca indeks reprezentanta zbioru, w którym jest wierzcho³ek v

int DSet::FindNodeInSet ( int node )
{
  if( arrayOfSets [ node ].dsNode != node )
        arrayOfSets[ node ].dsNode = FindNodeInSet( arrayOfSets [ node ].dsNode );
  return arrayOfSets [ node ].dsNode;
}


void DSet::UnionOfSets( Edge edge )
{
  int node1, node2;

  node1 = FindNodeInSet ( edge.startNode );
  node2 = FindNodeInSet ( edge.endNode );
  if( node1 != node2 )
  {
    if( arrayOfSets [ node1 ].weightOfSet > arrayOfSets [ node2 ].weightOfSet )
      arrayOfSets [ node2 ].dsNode = node1;
    else
    {
      arrayOfSets [ node1 ].dsNode = node2;

    if( arrayOfSets [ node1 ].weightOfSet == arrayOfSets [ node2 ].weightOfSet )
            arrayOfSets [ node2 ].weightOfSet++;
    }
  }
}


Graph::Graph( int nodes ,int edges,int s )
{
  arrayOfNode = new Node * [ nodes ];         // Tworzymy tablicê dynamiczn¹
  for(int i = 0; i < nodes; i++ )
    arrayOfNode [ i ] = NULL;               // i wype³niamy j¹ pustymi listami

arrayOfEdges = new Edge  [ edges ];         // Tworzymy tablicê dynamiczn¹
path = new int [nodes];
cost = new int [nodes];


  numberOfNodes = nodes ;                  // Zapamiêtujemy d³ugoœæ tablicy
  weightOfTree = 0;                                 // Zerujemy wagê drzewa
    numberOfEdges= edges;
    start=s;
    actualEdge=0;
}

Graph::~Graph( )
{
  Node *n1, *n2;

  for( int i = 0; i < numberOfNodes; i++ )
  {
    n1 = arrayOfNode[ i ];
    while( n1 )
    {
      n2 = n1;                     // Zapamiêtujemy wskazanie
      n1 = n1->next;               // Przesuwamy siê do nastêpnego elementu listy
      delete n2;                  // Usuwamy element
    }
  }

  delete [] arrayOfEdges;
  arrayOfEdges = nullptr;
  delete [] arrayOfNode;   // Usuwamy tablicê list s¹siedztwa
  arrayOfNode = nullptr;
    delete [] path;
    path=nullptr;
    delete [] cost;
    cost=nullptr;

}

void Graph::addEdgeUndirected ( Edge e )
{
    Node *newNode;
    newNode = new Node;                 // Tworzymy nowy wêze³
  newNode->node = e.endNode;                   // Wierzcho³ek koñcowy
  newNode->weight = e.weight;          // Waga krawêdzi
  newNode->next = arrayOfNode [ e.startNode ];          // Dodajemy p do listy wierzcho³ka v1
  arrayOfNode [ e.startNode ] = newNode;

newNode = new Node;                 // Tworzymy nowy wêze³
  newNode->node = e.startNode;                   // Wierzcho³ek koñcowy
  newNode->weight = e.weight;          // Waga krawêdzi
  newNode->next = arrayOfNode [ e.endNode ];          // Dodajemy p do listy wierzcho³ka v1
  arrayOfNode [ e.endNode ] = newNode;

    arrayOfEdges[actualEdge++]=e;
  weightOfTree += e.weight;            // Do wagi drzewa dodajemy wagê krawêdzi


}

void Graph::addEdgeDirected ( Edge e )
{
    Node *newNode;
    newNode = new Node;                 // Tworzymy nowy wêze³
  newNode->node = e.endNode;                   // Wierzcho³ek koñcowy
  newNode->weight = e.weight;          // Waga krawêdzi
  newNode->next = arrayOfNode [ e.startNode ];          // Dodajemy p do listy wierzcho³ka v1
  arrayOfNode [ e.startNode ] = newNode;

    arrayOfEdges[actualEdge++]=e;

  weightOfTree += e.weight;            // Do wagi drzewa dodajemy wagê krawêdzi
}


Node * Graph::getList ( int n )
{
  return arrayOfNode [ n ];
}

void Graph::print()
{
    cout<<"Edge \t     Weight\n";

for (int i=0; i<numberOfEdges; i++)
    cout <<"Edge "<< arrayOfEdges[i].startNode<< " - " << arrayOfEdges[i].endNode<< "\t " << arrayOfEdges[i].weight<<endl;


}
void Graph::printMST()
{
cout<<"Edge \t     Weight\n";

for (int i=0; i<numberOfNodes-1; i++)
    cout <<"Edge "<< arrayOfEdges[i].startNode<< " - " << arrayOfEdges[i].endNode<< "\t " << arrayOfEdges[i].weight<<endl;

cout  << endl << "Minimal Spanning Tree Weight = " << weightOfTree << endl;
}


void Graph::addEdgesToGraphDirected(Graph & graph)
{

    Edge e;
    for(int i = 0; i < numberOfEdges; i++ )
  {
    cin >> e.startNode >> e.endNode >> e.weight; // Odczytujemy kolejne krawêdzie grafu
    graph.addEdgeDirected ( e );
  }
}
void Graph::addEdgesToGraphUndirected(Graph & graph)
{

    Edge e;
    for(int i = 0; i < numberOfEdges; i++ )
  {
    cin >> e.startNode >> e.endNode >> e.weight; // Odczytujemy kolejne krawêdzie grafu
    graph.addEdgeUndirected ( e );
  }
}
Graph Graph::mstForPrim(Graph & graph)
{
    Edge e;
  Node * n;
  int i, v;
    priority_queue < Edge, vector < Edge >, comperator> quene;

  bool * visited = new bool [ numberOfNodes ];

  for( i = 0; i < numberOfNodes; i++ )
    visited [ i ] = false;       // Inicjujemy tablicê odwiedzin

  // Tworzymy minimalne drzewo rozpinaj¹ce

Graph mst(numberOfNodes,numberOfEdges,0);


  v = 0;                         // Wierzcho³ek startowy
  visited [ v ] = true;          // Oznaczamy go jako odwiedzonego
  for( i = 0; i < numberOfNodes-1; i++ )       // Do drzewa dodamy n - 1 krawêdzi grafu
  {
    for( n = graph.getList ( v ); n; n = n->next ) // Przegl¹damy listê s¹siadów
      if( !visited [ n->node ] )    // Jeœli s¹siad jest nieodwiedzony,
      {
        e.startNode = v;                // to tworzymy krawêdŸ
        e.endNode = n->node;
        e.weight = n->weight;
        quene.push ( e );            // Dodajemy j¹ do kolejki priorytetowej
      }

    do
    {
      e = quene.top( );            // Pobieramy krawêdŸ z kolejki
      quene.pop( );
    } while( visited [ e.endNode ] ); // KrawêdŸ prowadzi poza drzewo?

    mst.addEdgeUndirected ( e );             // Dodajemy krawêdŸ do drzewa rozpinaj¹cego
    visited [ e.endNode ] = true;     // Oznaczamy drugi wierzcho³ek jako odwiedzony
    v = e.endNode;
    mst.arrayOfEdges[i]=e;
  }


delete [] visited;
return mst;
}



Graph Graph::mstForKruskal(Graph & graph)
{

  Edge e;
  int i;


  DSet dset( numberOfNodes );        // Struktura zbiorów rozłącznych
  priority_queue < Edge, vector < Edge >, comperator> quene;
  Graph  mst ( numberOfNodes, numberOfEdges,0 );          // Minimalne drzewo rozpinające



for(int j=0; j<numberOfEdges;j++)
        quene.push(arrayOfEdges[j]);



  for( i = 0; i < numberOfNodes; i++ )
    dset.MakeSet ( i );       // Dla każdego wierzchołka tworzymy osobny zbiór


  for( i = 0; i < numberOfNodes-1; i++ ) // Pętla wykonuje się n - 1 razy
  {
    do
    {
      e = quene.top( );      // Pobieramy z kolejki krawędź
      quene.pop( );            // Krawędź usuwamy z kolejki
    } while( dset.FindNodeInSet ( e.startNode ) == dset.FindNodeInSet ( e.endNode ) );
    mst.addEdgeUndirected ( e );// Dodajemy krawędź do drzewa
    dset.UnionOfSets ( e );     // Zbiory z wierzchołkami łączymy ze sobą
    mst.arrayOfEdges[i]=e;
  }

return mst;
}


void Graph::dijkstra(Graph & graph)
{

int j,i,k;
Node * v;
bool * visited=new bool [numberOfNodes];        //zbiór początkowy który zawiera wszystkie wierzchołki




for( i= 0 ; i < numberOfNodes; i++)
{
    cost[i] = INF;          //ustalamy koszy dojścia do każdego wierzchołka na INF
    path[i] = -1;           //sciezki na -1
    visited[i] = false;      //zbiór wierzchołków odwiedzonych na false
}


cost[start] = 0;        //koszt wierzchołka startowego na 0


 for( i = 0; i < numberOfNodes; i++ )
  {
    for( j = 0; visited [ j ]; j++ );        //ustalamy ile wierzchołków było odwiedzonych

    for( k = j++; j < numberOfNodes; j++ )  //  k przypisujmey następnemu wierzchołkowi
      if( !visited [ j ] && ( cost [ j ] < cost [ k ] ) )   // jeśli wiechołek j był nieodwiedzony i koszt dojścia do niego jest mniejszy niż do wierzchołka k
        k=j;                                            // wierzchołek k zamieniamy na j


    visited [ k ] = true;                           //oznaczamy że wierzchołek k jest odwiedzony

 for( v = graph.getList(k); v; v = v->next )        //znajdź listę sąsiadów wierzchołka k
      if( !visited [ v->node ] && ( cost [ v->node ] > cost [ k ] + v->weight ) )   //jeśli sąsiad był nieodwiedzony i koszt dojścia do niego jest wiekszy
      {                                                                               // niż do wierzchołka k to modyfikujemy koszt i zmieniamy poprzednika v na k
        cost [ v->node ] = cost [ k ] + v->weight;
        path [ v->node ] = k;
      }

    }

  delete [] visited;
  }


void Graph::printPath()
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


bool Graph::bellman(Graph & graph)
{
    int i, v;
    bool t;
    Node * node;

    for( i= 0 ; i < numberOfNodes; i++)
{
    cost[i] = INF;          //ustalamy koszy dojścia do każdego wierzchołka na INF
    path[i] = -1;           //sciezki na -1
}

  cost [ start ] = 0;               // Zerujemy koszt dojścia do v


  for( i = 1; i < numberOfNodes; i++ )
  {
    t = true;             // Oznacza, że algorytm nie wprowadził zmian do cost i path
    for( v = 0; v < numberOfNodes; v++ ) // Przechodzimy przez kolejne wierzchołki grafu
      for( node =graph.getList(v); node; node = node->next ) // Przeglądamy listę sąsiadów wierzchołka v
        if( cost [ node->node ] > cost [ v ] + node->weight ) // sprawdzamy czy koszt dojścia do sąsiada jest większy niż koszt dojścia do wierzchołka v + waga krawędzi
        {
          t = false;      // jeśli tak to zachodzi zmiana w path i cost
          cost [ node->node ] = cost [ v ] + node->weight; // koszt dojścia do sąsiada ustlamy na koszt dojścia do v + waga krawędzi miedzy v i sąsiadem
          path [ node->node ] = v;   // Poprzednikiem sąsiada będzie v
        }
    if( t )
        return true;  // jeśli nie było zmiany to koniec
  }

  // Sprawdzamy istnienie ujemnego cyklu

  for( v = 0; v < numberOfNodes; v++ )
    for( node =graph.getList(v) ;node ;node = node->next )// Przeglądamy listę sąsiadów wierzchołka v
      if( cost [ node->node ] > cost [ v ] + node->weight ) // jeśli koszt dojścia do sąsiada jest większy niż koszt dojścia do v + waga krawedzi
    return false;                            // wykryto ujemny cykl

 return true;

}


void Graph::randomDirected(int nodes,float density)
{
    unsigned seed = chrono::steady_clock::now().time_since_epoch().count(); //ustawienie ziarna zegara
default_random_engine rd(seed);
mt19937 rng(rd());
uniform_int_distribution<int> dist(-50,50);
    int edges=(nodes*density*(nodes-1))/2;
    int max= (nodes*(nodes-1))/2;
    Edge **table = new Edge*[nodes];

    for( int i = 0; i < nodes; ++i )
        table[ i ] = new Edge[ nodes ];

    Edge * table2 = new Edge[max-nodes+1];
    Edge * table3 = new Edge[nodes-1];
    Edge e;

int j=0;
int k=0;
int l=0;

for (int i=0;i<nodes;i++)
{
    j=i;
    while(j<nodes){

             table[i][j].startNode=i;
             table[i][j].endNode=j;
             if(j-i>1){
                table2[k].endNode= table[i][j].endNode;
                table2[k].startNode=table[i][j].startNode;
                table2[k].weight=dist(rng);
                k++;}
             else if (j-i==1)
                {
                table3[l].endNode= table[i][j].endNode;
                table3[l].startNode=table[i][j].startNode;
                table3[l].weight=dist(rng);
             l++;
             }


    j++;
    };
}


if (max-nodes +1==0)
        {
for (int i = 0;i<edges ;i++)
    addEdgeDirected(table3[i]);

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







    Edge *arr= new Edge[nodes-1 + max-nodes+1];
    for (int i = 0; i < nodes-1 + max-nodes+1; i++)
    {
        if (i < nodes-1) {
            arr[i] = table3[i];
        }
        else {
            arr[i] = table2[randInt[i-nodes+1]];
        }
    }

for (int i = 0;i<edges ;i++)
    addEdgeDirected(arr[i]);


delete[] randInt;
delete [] arr;

}


 for (int i = 0; i<nodes ;i++)
   delete [] table [i];

delete [] table;
delete [] table2;
delete [] table3;

}



void Graph::randomUndirected(int nodes,float density)
{
    unsigned seed = chrono::steady_clock::now().time_since_epoch().count(); //ustawienie ziarna zegara
default_random_engine rd(seed);
mt19937 rng(rd());
uniform_int_distribution<int> dist(-50,50);
    int edges=(nodes*density*(nodes-1))/2;
    int max= (nodes*(nodes-1))/2;
    Edge **table = new Edge*[nodes];

    for( int i = 0; i < nodes; ++i )
        table[ i ] = new Edge[ nodes ];

    Edge * table2 = new Edge[max-nodes+1];
    Edge * table3 = new Edge[nodes-1];
    Edge e;

int j=0;
int k=0;
int l=0;

for (int i=0;i<nodes;i++)
{
    j=i;
    while(j<nodes){

             table[i][j].startNode=i;
             table[i][j].endNode=j;
             if(j-i>1){
                table2[k].endNode= table[i][j].endNode;
                table2[k].startNode=table[i][j].startNode;
                table2[k].weight=dist(rng);
                k++;}
             else if (j-i==1)
                {
                table3[l].endNode= table[i][j].endNode;
                table3[l].startNode=table[i][j].startNode;
                table3[l].weight=dist(rng);
             l++;
             }


    j++;
    };
}


if (max-nodes +1==0)
        {
for (int i = 0;i<edges ;i++)
    addEdgeUndirected(table3[i]);

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
        }
    } while( count < max-nodes+1 );






    Edge *arr= new Edge[nodes-1 + max-nodes+1];
    for (int i = 0; i < nodes-1 + max-nodes+1; i++)
    {
        if (i < nodes-1) {
            arr[i] = table3[i];
        }
        else {
            arr[i] = table2[randInt[i-nodes+1]];
        }
    }

for (int i = 0;i<edges ;i++)
    addEdgeUndirected(arr[i]);


delete[] randInt;
delete [] arr;

}


 for (int i = 0; i<nodes ;i++)
   delete [] table [i];

delete [] table;
delete [] table2;
delete [] table3;

}


bool Graph::ifWasRand( int value1, int tab[], int value2 )
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

bool Graph::ifMinusWeight()
{
    for (int i=0;i<numberOfEdges;i++)
        if (arrayOfEdges[i].weight<0)
        return true;

    return false;

}

