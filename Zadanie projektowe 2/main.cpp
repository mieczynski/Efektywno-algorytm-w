#include "Graph.h"
#include <iostream>
#include "GrahpMatrix.h"
#include<bits/stdc++.h>
#include <chrono>
#include<windows.h>
#include<ctime>

#define TEST 100
using namespace std;


//wczytanie lini
bool file_read_line(ifstream &file, int tab[], int size)
{
    string  s;
     getline(file, s);
      if(file.fail() || s.empty()) return(false);
      istringstream in_ss(s);
      for(int i = 0; i < size; i++)
        {
        in_ss >> tab[i]; if(in_ss.fail()) return(false);
        }

        return(true);
}

//wczytanie nag³ówka
int * readInfo(string file_name)
 {
    ifstream file;
    int* tab= new int[4];
    Edge e;

    file.open(file_name.c_str());

    if(file.is_open())
{
if (file_read_line(file, tab, 4))
    {
    }
    else
    cout << "File error - READ INFO" << endl;
        file.close();
}
  else     cout << "File error - OPEN" << endl;

return tab;
delete [] tab;
}


//wczytanie grafu
void readFromFileDirected(string file_name, Graph & graph, GraphMatrix & matrix)
{
    ifstream file;
    int tab[4];
    Edge e;
    file.open(file_name.c_str());

    if(file.is_open())
{
if (file_read_line(file, tab, 4))
    {
       int edges = tab[0];
    for(int i = 0; i < edges; i++)
        if(file_read_line(file, tab, 3))
        {
            e.startNode  = tab[0];
            e.endNode    = tab[1];
            e.weight = tab[2];
            graph.addEdgeDirected(e);
            matrix.addEdgeDirected(tab[0],tab[1],tab[2]);
        }
        else
        {
               cout << "File error - READ EDGE" << endl; break;

        }
    }
    else

        file.close();
}
  else
        cout << "File error - OPEN" << endl;

}

//wczytanie grafu
void readFromFileUndirected(string file_name, Graph & graph, GraphMatrix & matrix)
{
    ifstream file;
    int tab[4];
    Edge e;
    file.open(file_name.c_str());

    if(file.is_open())
{
if (file_read_line(file, tab, 4))
    {
       int edges = tab[0];
    for(int i = 0; i < edges; i++)
        if(file_read_line(file, tab, 3))
        {
            e.startNode  = tab[0];
            e.endNode    = tab[1];
            e.weight = tab[2];
            graph.addEdgeUndirected(e);
            matrix.addEdgeUndirected(tab[0],tab[1],tab[2]);
        }
        else
        {           cout << "File error - READ EDGE" << endl; break;

        }
    }
    else

        file.close();

}
  else
        cout << "File error - OPEN" << endl;

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
void test(int population, float denstity)
{
  float avgPrim=0;
    float avgKruskal=0;
  float avgDijkstra=0;
  float avgBellman=0;

        int e=(population*denstity*(population-1))/2;
        long long int frequency, start, elapsed;
    QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);

        for (int i =0; i< TEST;i++ ){


GraphMatrix graphDirected(population,e,0);
GraphMatrix graphUndirected(population,e,0);

        graphDirected.randomDirected(population,denstity);
        graphUndirected.randomUndirected(population,denstity);

         start = read_QPC();
        graphUndirected.mstForPrim(graphUndirected);
         avgPrim=+read_QPC() - start;


        start = read_QPC();

        graphUndirected.mstForKruskal(graphUndirected);

        avgKruskal=+ read_QPC() - start;

         start = read_QPC();

        graphDirected.dijkstra(graphDirected);

                avgDijkstra =+ read_QPC() - start;

            start = read_QPC();

        graphDirected.bellman(graphDirected);


                avgBellman =+ read_QPC() - start;


        }
        avgPrim=avgPrim/TEST;
    avgKruskal=avgKruskal/TEST;
    avgBellman=avgBellman/TEST;
    avgDijkstra=avgDijkstra/TEST;

        cout << fixed << setprecision(3) << (float)(avgPrim*1000000.0) / frequency << endl;
        cout << fixed << setprecision(3) << (float)(avgKruskal*1000000.0) / frequency << endl;
        cout << fixed << setprecision(3) << (float)(avgDijkstra*1000000.0) / frequency << endl;
        cout << fixed << setprecision(3) << (float)(avgBellman*1000000.0) / frequency << endl;
}

int main( )
{

    int option1;
    bool work=true;
bool t=false;


                system("cls");
                    string file_name;
                    cout << "Prosze podac nazwe pliku, 1 linijka to plik naglowkowy, gdzie  "<<endl;
                     cout << "1 cyfra oznacza liczbe krawedzi   "<<endl;
                     cout << "2 cyfra oznacza liczbe wierzcholkow   "<<endl;
                     cout << "3 cyfra oznacza wierzcholek startowy   "<<endl;
                     cout << "4 cyfra oznacza wierzcholek koncowy   "<<endl;
                     cout << "Nastepne linie to poszczegolne krawedzie w kolejnosci wierzcholek startowy, wierzcholek koncowy, waga"<<endl;
                     cout << "Jesli nastapil blad wczytywania nalezy zresetowac program"<<endl;
                    cin >> file_name;
                    int* tab = new int(4);
                    tab = readInfo(file_name);
                    Graph graphUndirected(tab[1],tab[0],tab[2]);
                    Graph graphDirected(tab[1],tab[0],tab[2]);
                    GraphMatrix graphMatrixUndirected(tab[1],tab[0],tab[2]);
                    GraphMatrix graphMatrixDirected(tab[1],tab[0],tab[2]);
                    readFromFileUndirected(file_name,graphUndirected,graphMatrixUndirected);
                    readFromFileDirected(file_name,graphDirected,graphMatrixDirected);


                    delete [] tab;

            system("cls");
            do{
          cout << "Menu:"<<endl <<"1. Wyswietlenie grafu"<<endl <<"2. Algorytm Prima"<< endl
          <<"3. Algorytm Kruskala"<<endl<<"4. Algorytm Dijkstry"<<endl<<"5. Algorytm Bellmana-Forda"<<endl
          <<"6. Zakoncz program"<<endl;
          cin>>option1;
system("cls");

          switch(option1)
          {
          case 1:
              {
            cout << "Graf skierowany jako lista"<<endl;
            graphDirected.print();
            cout << "Graf skierowany jako macierz"<<endl;
            graphMatrixDirected.print();

            cout << "Graf nieskierowany jako lista"<<endl;
            graphUndirected.print();
            cout << "Graf nieskierowany jako macierz"<<endl;
            graphMatrixUndirected.print();
            break;
            }
            break;
          case 2:
              {
                  system("cls");

                   cout << "Algorytm Prima dla grafu jako lista: "<<endl;
               graphUndirected.mstForPrim(graphUndirected).printMST();
               cout << endl << endl;
                    cout << "Algorytm Prima dla grafu jako macierz: "<<endl;
               graphMatrixUndirected.mstForPrim(graphMatrixUndirected).printEdge();
        break;
              }

          case 3:
                {
                    system("cls");

                  cout << "Algorytm Kruskala dla grafu jako lista: "<<endl;
               graphUndirected.mstForKruskal(graphUndirected).printMST();
               cout << endl << endl;
                cout << "Algorytm Kruskala dla grafu jako macierz: "<<endl;
               graphMatrixUndirected.mstForKruskal(graphMatrixUndirected).printEdge();
break;
                }

        case 4:
                {
                    system("cls");

                cout << "Algorytm Dijkstry dla grafu jako lista: "<<endl;
               graphDirected.dijkstra(graphDirected);
                 if (graphDirected.ifMinusWeight())
                    cout << "Graf zawiera ujemne krawedzie, wynik moze byc niepoprawny" <<endl;
               graphDirected.printPath();
               cout << endl << endl;
                cout << "Algorytm Dijkstry dla grafu jako macierz: "<<endl;
                if (graphMatrixDirected.ifMinusWeight())
                    cout << "Graf zawiera ujemne krawedzie, wynik moze byc niepoprawny" <<endl;
               graphMatrixDirected.dijkstra(graphMatrixDirected);
               graphDirected.printPath();
               break;
                }

        case 5:
            {
                system("cls");

                cout << "Algorytm Bellmana-Forda dla grafu jako lista: "<<endl;
               if(graphDirected.bellman(graphDirected))
               graphDirected.printPath();
               else
                  cout << "Graf posiada ujemny cykl"<<endl;
               cout << endl << endl;
                cout << "Algorytm Bellmana-Forda dla grafu jako macierz: "<<endl;
               if(graphMatrixDirected.bellman(graphMatrixDirected))
               graphDirected.printPath();
               else
                cout << "Graf posiada ujemny cykl"<<endl;
break;
            }


          case 6:
            {
                work=false;
            }

          }
            }while(work);


return 0;

}

