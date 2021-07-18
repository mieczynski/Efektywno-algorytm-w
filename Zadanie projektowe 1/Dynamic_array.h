#include <iostream>

using namespace std;


class Dynamic_array
{
    int count;                  //iloœæ elementów tablicy
    int *array;                 //wskaźnik na początek tablicy
    public:
        Dynamic_array();        //konstruktor
        ~Dynamic_array();       //destruktor
        void print( );           //wyświetlenie
        void add_start(int value);      //dodanie na start
        void add_end(int value);        //dodanie na początek
        void add(int idex,int value);   //dodanie w wybrane miejsce
        void remove( int index );       //usunięcie elementu z wybrenego miejsca
        void remove_end( );                     //usunięcie elementu z końca
        void remove_start( );               //usunięcie elementu z począktku
        void random( int test,int min,int max);       //wczytanie elementów losowych
        void file_read(string file_name);           //wczytanie z pliku

};

