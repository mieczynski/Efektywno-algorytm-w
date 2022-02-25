#include "TabuSearch.h"
#include "Graph.h"
#include <random>
#include <iostream>
#include <chrono>
#include<windows.h>
#include <fstream>
#include <string>
#include <sstream>     
#include <iomanip>  

#define INF 1000
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
void readFromFileDirected(string file_name, vector<vector<int>>& graph)
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

                        if (i == j) {
                            graph[i][j] = INF;

                        }
                        else {
                            graph[i][j] = tab2[j];

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

int main()
{ 
        srand(time(NULL));

    bool work = true;
    vector<vector<int>> matrix;

    string file_name = " ";
    string option1;
    int stop = 60;
    string dyw =  "Wylaczona";
    int reset = -1;
    int cadence = 0;
    int option;

 

    
    do
    {
 

        cout << "Prosze wybrac opcje" << endl;
        cout << "1. Wczytanie danych z pliku" << endl;
        cout << "2. Wprowadzenie kryterium stopu" << endl;
        cout << "3. Wlaczenie dywersyfikacji" << endl;
        cout << "4. Wylaczenie dywersyfikacji" << endl;
        cout << "5. Zmiana kadencji listy tabu" << endl;
        cout << "6. Uruchomienie algorytmu" << endl;
        cout << "7. Wyjscie z programu" << endl << endl;
        cout << "Wczytany plik: " << file_name << endl;
        cout << "Kryterium stopu[s]: " << stop << endl;
        cout << "Dywersyfikacja: " << dyw << endl;
        cout << "Kadencja listy tabu: " << cadence << endl;

        cin >> option1;
        istringstream(option1) >> option;


        if ((option < 1) && (option > 7)) {
            break;
            system("cls");
        }


        switch (option)
        {
        case 1:
        {
            system("cls");
         
            
            string txt(".txt");
            cout << "Prosze podac nazwe pliku z ktorego zostana wczytane elementy, elementy musza byc w formacie: " << endl;
            cout << "1 cyfra oznacza liczbe wierzcholkow, w kolejnych liniach odleg³osci z danego miasta do wszystkich pozostalych miast (liczby calkowite rozdzielone bialymi znakami)" << endl;
            cin >> file_name;
            system("cls");

            if(file_name.find(txt) == string::npos)
              file_name = file_name + txt;

            int* tab = new int[1];

            tab = readInfo(file_name);

            matrix.resize(tab[0]);
            for (int i = 0; i < tab[0]; i++)
                matrix[i].resize(tab[0]);

            readFromFileDirected(file_name, matrix);
            if (matrix.size() != 0)
                cadence = matrix[1].size() / 2;
            delete[] tab;
            
            break;
        }
        case 2:
        {

            system("cls");
            cout << "Prosze kryterium stopu w sekundach" << endl;
            cin >> stop;

            system("cls");

            break;
        }
        case 3:
        {
            system("cls");
            cout << "Prosze podac paratmetr restartu dla dywersyfikacji" << endl;
            cin >> reset;
            dyw = "Wlaczona";
            system("cls");
            break;
        }
        
        case 4:
        {
            system("cls");

            dyw = "Wylaczona";
            reset = -1;

            break;
        }
        case 5:
        {

            system("cls");
            cout << "Prosze podac nowa kadencje" << endl;
            cin >> cadence;
            system("cls");

            break;
        }
        case 6:
        {
            system("cls");
            if (file_name == " " || matrix.size()==0)
            {
                cout << "Prosze wczytac plik" << endl;
                break;
            }
            else
            {
                Graph g(matrix[0].size());
                g.setGraph(matrix);
                TabuSearch alg;
                alg.tabuSearch(g, cadence, stop, reset);
                alg.print();
            }

            break;
        }

        case 7:
        {

            work = false;
        }
        default:
            system("cls");
            break;
        }

    }while (work);
    system("cls");
    
}

 
   





 

  



  
