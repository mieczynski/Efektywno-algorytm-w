
class GraphMatrix
{
    private:
    int weightOfTree;                  // Waga ca³ego drzewa
    int numberOfNodes;
    int numberOfEdges;
    int ** matrix;
    int * cost;
    int * path;
    int start;
    public:
        GraphMatrix(int v,int e,int s);
         ~GraphMatrix();
        void addEdgeUndirected (int line, int column, int edge );
        void addEdgeDirected (int line, int column, int edge );
        void addEdgesDirected (GraphMatrix & graph );
        void addEdgesUndirected (GraphMatrix & graph );
        void print();
        GraphMatrix mstForPrim( GraphMatrix & graph);
        int minKey(int edge[], bool mstSet[]);
        int printPrimMST(int mst[], int ** graph) ;
        int findSet(int mst[], int v);
        void unionOfSets(int mst[],int set1, int set2 );
        GraphMatrix mstForKruskal(GraphMatrix & graph);
        void printEdge();
        void dijkstra(GraphMatrix & graph);
        bool bellman(GraphMatrix & graph);
        void printPath();
        void randomDirected(int nodes,float density);
        void randomUndirected(int nodes,float density);
        bool ifWasRand( int value1, int tab[], int value2 );
        bool ifMinusWeight();

};

