#include<sstream>
#include<string>
using namespace std;
struct Edge
{
  int startNode, endNode, weight;            // Wierzcho³ki krawêdzi, waga krawêdzi
};

struct comperator
{
    bool operator ()( const Edge & edge1, const Edge & edge2 )
    {
        //kolejność - rosnąco
        return( edge1.weight > edge2.weight );

        return( edge1.weight < edge2.weight);

    }
};

struct DSNode
{
  int dsNode, weightOfSet;
};

class DSet
{
  private:
    DSNode * arrayOfSets;
  public:
    DSet ( int numberOfElements );
    ~DSet();
    void MakeSet ( int node );
    int FindNodeInSet( int node );
    void UnionOfSets(Edge edge );
};

struct Node
{
    Node * next;
    int node, weight;
};

class Graph
{
private:
    Node ** arrayOfNode;         // Tablica list s¹siedztwa
    int numberOfNodes;      // Liczba komórek w tablicy
    Edge * arrayOfEdges;                  // Waga ca³ego drzewa
    int weightOfTree;
    int numberOfEdges;
    int * path;
    int * cost;
    int start;
    int actualEdge;

public:

    Graph ( int n, int e,int start);
    ~Graph( );
    void addEdgeDirected ( Edge e );
    void addEdgeUndirected( Edge e );
    Node * getList ( int n );
     void addEdgesToGraphDirected(Graph & graph);
    void addEdgesToGraphUndirected(Graph & graph);
     void print();
     void printMST();
    Graph  mstForPrim(Graph & graph);
    Graph mstForKruskal(Graph & graph);
    void dijkstra(Graph & graph);
    bool bellman(Graph & graph);
    void printPath();
    void randomDirected(int population,float density);
    void randomUndirected(int population,float density);
    bool ifWasRand( int value1, int tab[], int value2 );
    bool ifMinusWeight();


};

