#include <iostream>
#include <List.h>
#include <chrono>
#include <random>
#include<sstream>
#include<string>
#include<fstream>
using namespace std;



// Inicjuje pola zmiennej listy
 List::List( )
{ tail = NULL;
  head  = tail;
  count = 0;
}

// Usuwa liste z pamięci
 List::~List( )
{
  while(count!=0)
    remove_end( );
}

 Element * List::index(unsigned n)
    {
      Element * w;

      if((!n) || (n > count))
        return NULL;
      else if(n == count)
        return tail;
      else
      {
        w = head;
        while(--n)
        w = w->next;
        return w;
      }
    }
void List::print_start()      //wyświetlanie zawartości listy
{
    Element* w = head;      //utworzenie wskaźnika na element listy i przypisanie zapisanie do niego wskaźnika na początek listy
    cout << "Zawartosc listy: \n";
    while (w)           //dopóki istnieje nastêpnik pętla wyœwietla elementy
        {
            cout << w->element << " ";
            w = w->next;
        }
    cout << "\n";

}
void List::print_end()      //wyświetlanie zawartości listy
{
    Element* w = tail;      //utworzenie wskaźnika na element listy i przypisanie zapisanie do niego wskaźnika na początek listy
    cout << "Zawartosc listy: \n";
    while (w)           //dopóki istnieje poprzednik pętla wyœwietla elementy
        {
            cout << w->element << " ";
            w = w->prev;
        }
    cout << "\n";
}
void List::add_start(int value)     //dodanie elementu na początek listy
{
    Element* w;                         //utworzenie wskaźnika na nowy element
    w = new Element;
    w->element=value;
    w->next=head;
    w->prev=NULL;
    head=w;
    if (w->next)        //jeśli istnieje następny element to przypisujemy jego wskaźnikowi na poprzedni element dodany element
        w->next->prev=w;
    else
        tail = w;       //jeśli następny element nie istnieje to nowy element staje się ogonem
    count++;

}
void List::add_end(int value)
{
    Element* w;                         //utworzenie wskaźnika na nowy element
    w = new Element;
    w->element=value;
    w->next=NULL;
    w->prev=tail;
    tail=w;
    if (w->prev)        //jeśli istnieje poprzedni element to przypisujemy jego wskaźnikowi na następny element dodany element
        w->prev->next=w;
    else
        head=w;     //jeśli poprzedni element nie istnieje to nowy element staje się głową
    count++;
}

void List::add(Element* i, int value)           //dodawanie elementu za podanym
{
    Element* w;             //utworzenie wskaźnika na nowy element
    if (i==tail)            //sprawdzenie czy podany element nie jest końcem listy
        add_end(value);
    else
    {
    w = new Element;
    w->element=value;
    w->prev=i;
    w->next=i->next;
    i->next->prev = w;
    i->next = w;
    count++;
    }
}

void List::remove(Element *i)
{


    if(cout)
    {
  if( i->next )
   i->next->prev = i->prev;
  else
        tail = i->prev;
  if( i->prev )
   i->prev->next = i->next;
  else
  head = i->next;
  delete i;
  count--;
  }
  else{
    cout << "Brak elementu na liście";
  }}



void List::remove_start()
{
    if (count)  //jeśli lista istnieje to usuwamy głowę
        remove(head);
    else
    cout << "Brak elementu na liście";
}



void List::remove_end()
{
    if (count)  //jeśli lista istnieje to usuwamy ogon
        remove(tail);
    else
    cout << "Brak elementu na liście";
}

void List::random(int test, int min, int max)

{

unsigned seed = chrono::steady_clock::now().time_since_epoch().count(); //ustawienie ziarna zegara
default_random_engine rd(seed);
mt19937 gen(rd());
uniform_int_distribution<> dist(min, max);
for (int i=0;i<test;i++)
    add_end(dist(gen));
}




void List::file_read(string file_name)
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
            add_start(value);
        }
        file.close();
    }
else
             cout << "File error - OPEN" << endl;       //błąd z otwarciem pliku
    }






