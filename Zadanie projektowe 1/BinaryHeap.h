#include <iostream>

using namespace std;

class BinaryHeap
{    int count;    //liczba elementów kopca
    int *heap ;//wskaźnik na początek kopca
    public:
        BinaryHeap();
        ~BinaryHeap();
        void print();       //wyswietlanie kopca
        void add(int value);    //dodawanie elementu do kopca
        void remove();             //usuwanie korzenia
        void random(int test,int max, int min);      //wczytywanie losowych elementow
        void file_read(string file_name);           //wczytywanie z pliku

};

