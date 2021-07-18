#include "BinaryHeap.h"
#include <iostream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <random>
#include <chrono>
#include<sstream>
#include<fstream>
using namespace std;


BinaryHeap::BinaryHeap()
{
    heap = nullptr;
    count =0;
}

BinaryHeap::~BinaryHeap()
{
    if (count == 0)
        return;
    delete [] heap;
   count=0;
}


void BinaryHeap::print()
{
    if(count==0)
    {
        cout<<"Nie ma nic do wyœwietlenia"<<endl;
    }

    else
   {

    int j=2;
    int k=1;
    int i=1;

    cout << heap[0]<<endl;
while(i<count)
{

    cout <<heap[i]<<"  ";
    if (k==j)
    {
        k=0;
        j=j*2;      //przejście do nowej linii jeśli pętla wykonała się x^2 raza

        cout <<endl;;
    }
    i++;
    k++;
}
    }
}


 void BinaryHeap::add(int value)
{


int * newHeap = new int[ count + 1 ]; //nowa tablica
for( int i = 0; i < count; ++i ) // kopiuje wartosci
         newHeap[i] = heap[i];
    delete[] heap; //zwalniam pamiec zajmowana przez poprzednia tablice
    heap = newHeap; // przypisuje wskaznik na nowa tablice.

  int i, j;
  i = count++;      //przypisanie ostatniej pozycji w nowej tablicy
  j = ( i - 1 ) / 2;        //znaleźenie rodzica dodawanej pozycji

  while( i > 0 && newHeap [j] < value )       //dopóki wartość rodzica jest mniejsza od wartości dodanej wykonuje się pętla
  {
    newHeap [i] = newHeap [j];      //przypisanie ostatniej pozycji wartośći rodzica
    i = j;                       // zamiana rodzica z ostatnią pozycją
    j = ( i - 1 ) / 2;          //znalezienie rodzica dla nowej pozycji
  }

  newHeap [i] = value;

}


void BinaryHeap::remove()
{

  if(count--)   //jeśli kopiec istnieje
  {
      int i, j, value;
    value= heap[count];

    i = 0;      //pozycja korzenia
    j = 1;      //pozycja lewego syna

    while( j < count )
    {
      if(j+1 < count && heap[j+1] > heap[j] )   //jeśli prawy syn istnieje i jego wartość jest większa od lewego syna to j przypisujemy pozycję prawego syna
        j++;
      if( value >= heap[j] )        //jeśli wartość ostatniego elementu kopca jest większa lub równa wartości prawego syna to wychodzimy z pętli
        break;
      heap[i] = heap[j];        //przypisanie wartości korzenia wartości któregoś z synów
      i = j;            // przypisanie pozycji korzenia pozycji któregoś z synów
      j = 2*j+1;        //znalezienie nowego lewego syna
    }

    heap[i] = value;

  }
  else
  {

    cout <<"Nie mo¿na usunąć korzenia \n";
    }
}


void BinaryHeap::random( int test,int min, int max)
{

    if (test<0){
        cout << "Nieprawidłowa liczba testów"<<endl;}
        else {
     unsigned seed = chrono::steady_clock::now().time_since_epoch().count();        //ustawienie ziarna zegara
default_random_engine rd(seed);
mt19937 gen(rd());
uniform_int_distribution<> dist(min, max);



int * newHeap = new int[ count + test ]; //nowa tablica
for( int i = 0; i < count; ++i ) // kopiuje wartosci
         newHeap[i] = heap[i];
    delete[] heap; //zwalniam pamiec zajmowana przez poprzednia tablice
    heap = newHeap; // przypisuje wskaznik na nowa tablice.
for(int k=0;k<test;k++){
  int i, j;
  i = count++;          //przypisanie ostatniej pozycji w nowej tablicy
  j = ( i - 1 ) / 2;     //znaleźenie rodzica dodawanej pozycji
int   value=dist(gen);
  while( i > 0 && newHeap[j] < value )       //dopóki wartość rodzica jest mniejsza od wartości dodanej wykonuje się pętla
  {
    newHeap[i] = newHeap[j];              //przypisanie ostatniej pozycji wartośći rodzica
    i = j;                                  // zamiana rodzica z ostatnią pozycją
    j = (i - 1) / 2;                      //znalezienie rodzica dla nowej pozycji
  }

  newHeap [i] = value;

}}}


void BinaryHeap::file_read(string file_name)
 {
    ifstream file;
int size,value;

    file.open(file_name.c_str());



    if(file.is_open()) {
                    file >> size;
    if (file.fail())
     cout << "File error - READ SIZE" << endl;          // błąd związany z rozmierem struktury

    else
        for (int i=0;i<size;i++)
        {

        file >> value;
            if(file.fail())
                {
                    cout << "File error - READ DATA" << endl;       // błąd związany z resztą danych w pliku
                    break;
                }
            else
            add(value);
        }
        file.close();
    }
else
             cout << "File error - OPEN" << endl;       //błąd z otwarciem pliku
    }
