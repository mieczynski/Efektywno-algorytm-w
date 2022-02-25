#include "Node.h"
#include <iostream>
#include <chrono>
#include<windows.h>
#include <fstream>
#include <string>
#include <sstream>     
#include "Graph.h"
#include<ctime>
#include <iomanip>  


#define INF 1000
#define TEST 100

using namespace std;

//wczytanie lini
bool file_read_line(ifstream& file, int tab[], int size)
{
    string  s;
    getline(file, s);
    if (file.fail() || s.empty()) return(false);
    istringstream in_ss(s);
    for (int i = 0; i < size; i++)
    {
        in_ss >> tab[i]; if (in_ss.fail()) return(false);
    }

    return(true);
}

//wczytanie nag³ówka
int* readInfo(string file_name)
{
    ifstream file;
    int* tab = new int[1];
    

    file.open(file_name.c_str());

    if (file.is_open())
    {
        if (file_read_line(file, tab, 1))
        {
        }
        else
            cout << "File error - READ INFO" << endl;
        file.close();
    }
    else     cout << "File error - OPEN" << endl;

    return tab;
    delete[] tab;
}


//wczytanie grafu
void readFromFileDirected(string file_name, vector<vector<int>> &graph)
{
    ifstream file;
    int* tab = new int[1];
    
    file.open(file_name.c_str());

    if (file.is_open())
    {
        if (file_read_line(file, tab, 1))
        {
            
            int nodes = tab[0];
            
            int j = 0;
            
            int* tab2 = new int[nodes];
          
            for (int i = 0; i < nodes; i++)
            {
  
               if (file_read_line(file, tab2, nodes))
                {
                    
                    for (int j = 0; j < nodes; j++) {
                        
                        if (i==j) {
                            graph[i][j] = INF;
                            
                        }
                        else {
                            graph[i][j]= tab2[j];
                           
                        }
                        
                      
                    }
               }
                else
              {
                    cout << "File error - READ EDGE" << endl; break;

               }
             
                    
            }
            
            delete[] tab2;
        }
        else

            file.close();
        
   }
    else
        cout << "File error - OPEN" << endl;
 
  
    delete[] tab;
    
}

Node randNode(int size)
{
    srand(time(NULL));
    Node n(size);

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (i != j)
                n.matrix[i][j] = rand() % 100 + 1;

    return n;
}
Graph randGraph(int size)
{
    srand(time(NULL));
    Graph n(size);

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (i != j)
                n.startMatrix[i][j] = rand() % 100 + 1;

    return n;
}
long long int read_QPC()
{
    LARGE_INTEGER count;
    DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
    QueryPerformanceCounter(&count);
    SetThreadAffinityMask(GetCurrentThread(), oldmask);
    return((long long int)count.QuadPart);
}
// funkcja do testowania
void test()
{
    float avgBB = 0;    
    float avgBrute = 0;
    float avgHeld = 0;
  
    
    
    long long int frequency, start, elapsed;
    QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);


    for (int i = 0; i < TEST; i++) {


        Node node = randNode(16);
       
      // Graph graph = randGraph(9);
        
   

        start = read_QPC();
        node.BranchAndBound(node.matrix);
        elapsed  =read_QPC() - start;
        avgBB = elapsed + avgBB;

     

        /*
        start = read_QPC();

        graph.BruteForce(0);

        avgBrute = +read_QPC() - start;
        
        start = read_QPC();

        graphDirected.dijkstra(graphDirected);

        avgHeld = +read_QPC() - start;

        */

    }
    avgBB = avgBB / TEST;
    avgBrute = avgBrute / TEST;
    avgHeld = avgHeld / TEST;

    
    cout << fixed << setprecision(3) << (float)(avgBB * 1000000.0) / frequency << endl;
    cout << fixed << setprecision(3) << (float)(avgBrute * 1000000.0) / frequency << endl;
    cout << fixed << setprecision(3) << (float)(avgHeld * 1000000.0) / frequency << endl;

}

int main()
{

    long long int frequency, start, elapsed;
    QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
   
    vector<vector<int>> matrix;

    bool work = true;
  
 
    
    int option;
    do
    {
       
        cout << "Prosze wybrac opcje" << endl;
        cout << "1. Wczytanie danych z pliku" << endl;
        cout << "2. Losowanie danych" << endl;
        cout << "3. Alogrytm B&B" << endl;
        cout << "4. Algorytm BruteForce" << endl;
        cout << "5. Algorytm HeldKarp" << endl;
        cout << "6. Wyjscie z programu" << endl;
        cin >> option;
        switch (option)
        { 
        case 1:
        {
            system("cls");
            
            string file_name;
            cout << "Prosze podac nazwe pliku z ktorego zostana wczytane elementy, elementy musza byc w formacie: " << endl;
            cout << "1 cyfra oznacza liczbe wierzcholkow, w kolejnych liniach odleg³osci z danego miasta do wszystkich pozostalych miast (liczby calkowite rozdzielone bialymi znakami)" << endl;
            cin >> file_name;
            int* tab = new int[1];
            
            tab = readInfo(file_name);

            matrix.resize(tab[0]);
            for (int i = 0; i < tab[0]; i++)
                matrix[i].resize(tab[0]);

            readFromFileDirected(file_name, matrix);
            
            delete[] tab;
            break;
        }
        case 2:
        {

            system("cls");
            int size;
            cout << "Prosze podac ilosc wierzcholkow" << endl;
            cin >> size;
            Node node = randNode(size);

            Graph graph = randGraph(size);

            matrix.resize(size);

            for (int i = 0; i < size; i++)
                matrix[i].resize(size);

            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                    matrix[i][j]= node.matrix[i][j];
        
            cout << "Wylosowana Macierz" << endl;
            node.print();
            break;
        }
        case 3:
        {
            system("cls");
            if (matrix.size() == 0)
            {
                cout << "Macierz nie istnieje" << endl;
                break;
            }
            else {

                Node node(matrix[0].size());
                node.setGraph(matrix);
                
                cout << "Branch and Bound" << endl;
                 cout << "Macierz" << endl;
                node.print();
                
                cout << endl;
                
                start = read_QPC();
                int cost= node.BranchAndBound(node.matrix);
                     
                elapsed = read_QPC() - start;
                cout << endl;
                cout << "Czas wykonania [us]  = " << fixed << setprecision(3) << (float)elapsed * 1000000 / frequency << endl;
               cout << "Koszt: " << cost<<endl;
               
                
            }
            break; 
        }
        case 4:
        {
            system("cls");
        if (matrix.size() == 0)
        {
            cout << "Macierz nie istnieje" << endl;
            break;
        }
        else {
            system("cls");
            Graph graph(matrix[0].size());
            graph.setGraph(matrix);

            start = read_QPC();
            cout << "Brute Force" << endl;
            cout << "Macierz" << endl;
            graph.print();
            cout << endl;

            int cost = graph.BruteForce(0);


            elapsed = read_QPC() - start;
            cout << "Sciezka: " << endl;

            graph.printPathForBrute();

            cout << endl;
            cout << "Czas wykonania [us]  = " << fixed << setprecision(3) << (float)elapsed * 1000000 / frequency << endl;
            cout << "Koszt: " << cost << endl;
        }


            break;
        }
        case 5:
        {
            system("cls");
            if (matrix.size() == 0)
            {
                cout << "Macierz nie istnieje" << endl;
                break;
            }
            else {
                system("cls");
                Graph graph(matrix[0].size());
                graph.setGraph(matrix);

                start = read_QPC();
                cout << "Held-Karp" << endl;
                cout << "Macierz" << endl;
                graph.print();
                cout << endl;

                int cost = graph.HeldKarp(0);


                elapsed = read_QPC() - start;
                cout << "Sciezka: " << endl;

                graph.printPathForHeld();

                cout << endl;
                
                cout << "Czas wykonania [us]  = " << fixed << setprecision(3) << (float)elapsed * 1000000 / frequency << endl;
                cout << "Koszt: " << cost << endl;
            }


            break;
        }

        case 6:
        {

            work = false;
        }
        default:
            break;
        }
      
    }while(work);
    system("cls");
     
  
}