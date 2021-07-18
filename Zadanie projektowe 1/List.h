#include<sstream>
#include<string>
using namespace std;

struct Element
{
    int element;         //wartość elementu
    Element*next;        //następnik
    Element*prev;       //poprzednik
};


class List
{
    public:
    Element *head;      //początek listy
    Element *tail;      // koniec listy
    unsigned int count;     //ilość elementów listy
    void print_start( );        //wyświetlanie od początku
    void print_end();           //wyświetlanie od końca
    void add_start( int value );        //dodanie elementu na początek
    void add_end( int value );       //dodanie elementu na koniec
    void add( Element * i, int value );         //dodanie elementu w wybrane miejsce
    void remove( Element * i );             //usunięcie elementu z wybrenego miejsca
    void remove_end( );                 //usunięcie elementu z końca
    void remove_start( );               //usunięcie elementu z począktku
    void random(int test,int min, int max);     //wczytanie elementów losowych
    void file_read(string file_name);           //wczyanie z pliku
    Element * index(unsigned n);        //funkcja zwraca wskaźnik na element podanego przez nas indeksu
    List();         //konstruktor
    ~List();        //destruktor


};



