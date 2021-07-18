#include "Dynamic_array.h"
#include <iostream>
#include <random>
#include <chrono>
#include<sstream>
#include<string>
#include<fstream>
using namespace std;

Dynamic_array::Dynamic_array()
{
count =0;
array = nullptr;
}
Dynamic_array::~Dynamic_array()
{
    if (count == 0)
        return;
    delete [] array;
    array = nullptr;
    count=0;
}



void Dynamic_array::print(){
    if (count!=0){
        cout << "Elementy tablicy \n";
    for (int i=0; i<count ;i++)
        {
        cout << array[i]<<" ";
        }}
    else
    {
        cout << "Brak elementów tablicy do wyświetlenia \n";
    }
cout<<"\n";

}




void Dynamic_array::add(int index, int value)
{
    if (index>count||index<0)
    {
        cout << "Tablica nie posiada danego indeksu"<<endl;
    }
    else{
   int * NewTab = new int[ count + 1 ]; //nowa tablica
    for( int i = 0; i < index; ++i ) // kopiuje wartosci przed indexem
         NewTab[i] = array[i];

    NewTab[ index ] = value; //na index wstawiam zadana wartosc
    for( int i = index + 1; i < count + 1; ++i ) // i kopiuje reszte
         NewTab[i] = array[i-1];

    delete[] array; //zwalniam pamiec zajmowana przez poprzednia tablice
    array = NewTab; // przypisuje wskaznik na nowa tablice.
    ++count; // zwiekszam licznik
}}


void Dynamic_array::add_end(int value)
{

   int * NewTab = new int[count + 1]; //nowa tablica
    for( int i = 0; i < count; ++i ) //
         NewTab[i] = array[i];
         NewTab[count]=value;

  delete[] array; //zwalniam pamiec zajmowana przez poprzednia tablice
    array = NewTab; // przypisuje wskaznik na nowa tablice.
    ++count; // zwiekszam licznik
}


void Dynamic_array::add_start(int value)
{

   int * NewTab = new int[ count + 1 ]; //nowa tablica
    for( int i = 1; i < count + 1; ++i ) // i kopiuje reszte
         NewTab[i] = array[i-1];
         NewTab[0]=value;

  delete[] array; //zwalniam pamiec zajmowana przez poprzednia tablice
    array = NewTab; // przypisuje wskaznik na nowa tablice.
    ++count; // zwiekszam licznik
}


void Dynamic_array::remove(int index)
{
    if (count==0)
        {
        cout << "Brak elementów do usunięcie"<<endl;
        }
    else {
    if (index>count||index<0)
    {
        cout << "Tablica nie posiada danego indeksu"<<endl;
    }
    else {
      int * NewTab = new int[ count-1 ]; //nowa tablica
    for( int i = 0; i < index; ++i ) // kopiuje wartosci przed indexem
         NewTab[i] = array[i];

  for( int i = index ; i < count; ++i ) // i kopiuje reszte
         NewTab[i] = array[i+1];


   delete[] array; //zwalniam pamiec zajmowana przez poprzednia tablice

   array= NewTab; // przypisuje wskaznik na nowa tablice.
    count--;}
    }
}

void Dynamic_array::remove_start(){
if (count==0)
        {
        cout << "Brak elementów do usunięcie"<<endl;
        }
    else {
{   int * NewTab = new int[ count-1 ]; //nowa tablica

  for( int i = 0 ; i < count; ++i ) // i kopiuje reszte
         NewTab[i] = array[i+1];


   delete[] array; //zwalniam pamiec zajmowana przez poprzednia tablice

   array= NewTab; // przypisuje wskaznik na nowa tablice.
    count--;
}
}
}

void Dynamic_array::remove_end()
{
    if (count==0)
        {
        cout << "Brak elementów do usunięcie"<<endl;
        }
    else {
        array[count]=NULL; //ostatni element zostaje usunięty
    count--;
    }
}

void Dynamic_array::random(int test,int min,int max){
    if (test<0){
        cout << "Nieprawidłowa liczba testów"<<endl;}
        else {
unsigned seed = chrono::steady_clock::now().time_since_epoch().count(); //ustawienie ziarna zegara
default_random_engine rd(seed);
mt19937 gen(rd());
uniform_int_distribution<> dist(min, max);


    int * NewTab = new int[ count +test  ];//nowa tablica
    for( int i = 0; i < count; ++i ) //
         NewTab[ i ] = array[ i ];

         for(int j=count ;j<test+count;j++)
         NewTab[j]=dist(gen);

    delete[] array; //zwalniam pamiec zajmowana przez poprzednia tablice
   array= NewTab; // przypisuje wskaznik na nowa tablice.
    count=count +test;

        }

}




void Dynamic_array::file_read(string file_name)
 {
    ifstream file;
int size,value;

    file.open(file_name.c_str());



    if(file.is_open()) {
                    file >> size;
    if (file.fail())
     cout << "File error - READ SIZE" << endl;  // błąd związany z rozmierem struktury
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
            add_end(value);
        }
        file.close();
    }
else
             cout << "File error - OPEN" << endl;           //błąd z otwarciem pliku
    }


