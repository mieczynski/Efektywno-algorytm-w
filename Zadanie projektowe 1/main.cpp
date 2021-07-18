#include <List.h>
#include <iostream>
#include <Dynamic_array.h>
#include <BinaryHeap.h>
#include <string>
#include <random>
#include <chrono>
#include <fstream>
#include<sstream>
#include<string>
#include <windows.h>
#include <iomanip>

using namespace std;


long long int read_QPC()
{
    LARGE_INTEGER count;
     DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
      QueryPerformanceCounter(&count);
       SetThreadAffinityMask(GetCurrentThread(), oldmask);
      return((long long int)count.QuadPart);
}



int main()
{
  long long int frequency, start, elapsed;
    QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
    int option1, option2, option3;
    bool work=true;
    bool work2=true;

            do{
            system("cls");
          cout << "Proszę wybrać opcje testowania"<<endl <<"1. Operacje na tablicach dynamicznych"<<endl <<"2. Operacje na listach dwukierunkowych"<<
          endl <<"3. Operacje na kopcach binarnych"<< endl <<"4. Koniec programu"<<endl;
          cin>>option1;

          system("cls");
          switch(option1)
          {
          case 1:
              {
              Dynamic_array D_array;
            work2=true;
              do{
            cout<< "Proszę wybrać działanie:"<<endl << "1. Dodawanie elementu na początek tablicy" <<endl<< "2. Dodawanie elementu na koniec tablicy "<<endl
            << "3. Dodawanie elementu w wybrane miejsce tablicy" <<endl<< "4. Usuwanie elementu z początku tablicy" <<endl
            << "5. Usuwanie elementu z końca tablicy" <<endl << "6. Usuwanie elementu z wybranego miejsca tablicy" <<endl
            << "7. Wyświetlenie tablicy"<<endl << "8. Losowanie zmiennych do tablicy" <<endl<< "9. Wczytanie elementów z pliku" <<endl
            << "10. Powrót do menu głównego" <<endl;
            cin>> option2;


            switch(option2)
                {
            case 1:
                {

                    int value;
                    system("cls");
                    cout << "Proszę podać wartość"<<endl;
                    cin>> value;
                    start = read_QPC();
                    D_array.add_start(value);
                    elapsed = read_QPC() - start;
                   cout << "Czas wykonania [us]  = " << fixed << setprecision(3) << (float)elapsed*1000000 / frequency << endl;
                    break;


                }
            case 2:
                {
                    system("cls");
                    int value;
                    cout << "Proszę podać wartość"<<endl;
                    cin>> value;
                    start = read_QPC();
                    D_array.add_end(value);
                    elapsed = read_QPC() - start;
                    cout << "Czas wykonania [us]  = " << fixed << setprecision(3) << (float)elapsed*1000000 / frequency << endl;
                    break;
                }
            case 3:
                {
                    system("cls");
                    int index,value;
                    cout << "Proszę podać wartość"<<endl;
                    cin>> value;
                    cout << "Proszę podać numer indeksu"<<endl;
                    cin >> index;
                    start = read_QPC();
                    D_array.add(index, value);
                    elapsed = read_QPC() - start;
                    cout << "Czas wykonania [us]  = " << fixed << setprecision(3) << (float)elapsed*1000000 / frequency << endl;
                    break;
                }
            case 4:
                {
                    system("cls");
                    start = read_QPC();
                    D_array.remove_start();
                    elapsed = read_QPC() - start;
                    cout << "Czas wykonania [s]  = " << fixed << setprecision(3) << (elapsed*1000000000.0)   / frequency << endl;

            break;
                }
            case 5:
                {
                    system("cls");
                    start = read_QPC();
                    D_array.remove_end();
                    elapsed = read_QPC() - start;
                    cout << "Czas wykonania [us]  = " << fixed << setprecision(3) << (float)elapsed*1000000 / frequency << endl;
                    break;
                }
            case 6:
                {
                    system("cls");
                    int index;
                    cout << "Proszę podać numer indeksu"<<endl;
                    cin >> index;
                    system("cls");
                    start = read_QPC();
                    D_array.remove(index);
                    elapsed = read_QPC() - start;
                   cout << "Czas wykonania [us]  = " << fixed << setprecision(3) << (float)elapsed*1000000 / frequency << endl;
                    break;
                }
            case 7:
                {
                    system("cls");
                    start = read_QPC();
                    D_array.print();
                    elapsed = read_QPC() - start;
                    cout << "Czas wykonania [us]  = " << fixed << setprecision(3) << (float)elapsed*1000000 / frequency << endl;
                    break;
                }
            case 8:
                {
                    system("cls");
                    int test, min_dist, max_dist;
                    cout << "Proszę podać ilość elementów, które mają być wylosowane"<<endl;
                    cin>> test;
                    if (test<1){
                        cout <<"Nieprawidłowa ilość elementów"<<endl;
                        break;}
                    cout<<endl;
                    cout << "Proszę podać minimalny zakres liczb, które mają być wylosowane"<<endl;
                    cin>> min_dist;
                    cout<<endl;
                    cout << "Proszę podać maksymalny zakres liczb, które mają być wylosowane"<<endl;
                    cin>> max_dist;
                    cout<<endl;
                    if (min_dist>=max_dist){
                        cout <<"Podano błędny zakres"<<endl;
                        break;}
                    start = read_QPC();
                    D_array.random(test,min_dist, max_dist);
                    elapsed = read_QPC() - start;
                    cout << "Czas wykonania [us]  = " << fixed << setprecision(3) << (float)elapsed*1000000 / frequency << endl;
                    break;
                }
            case 9:
                {
                    system("cls");
                    string file_name;
                    cout << "Proszę podać nazwę pliku z którego zostaną wczytane elementy, elementy muszą być w formacie: "<<endl;
                     cout << "1 cyfra oznacza liczbę elementów, kolejne są wartościami "<<endl;
                    cin >> file_name;
                    start = read_QPC();
                    D_array.file_read(file_name);
                    elapsed = read_QPC() - start;
                    cout << "Czas wykonania [us]  = " << fixed << setprecision(3) << (float)elapsed*1000000 / frequency << endl;
                    break;

                }
            case 10:
                {

                work2=false;
                }
            default:
                break;
                }
            }while(work2);
            system("cls");

          break;
          }
          case 2:
              {
             List list;


                work2=true;
              do{
            cout<< "Proszę wybrać działanie:"<<endl << "1. Dodawanie elementu na początek listy" <<endl<< "2. Dodawanie elementu na koniec listy "<<endl
            << "3. Dodawanie elementu w wybrane miejsce listy" <<endl<< "4. Usuwanie elementu z początku listy" <<endl
            << "5. Usuwanie elementu z końca listy" <<endl << "6. Usuwanie elementu z wybranego miejsca listy" <<endl
            << "7. Wyświetlenie listy od początku"<<endl << "8. Wyświetlenie listy od końca" <<endl
            << "9. Losowanie zmiennych do listy" <<endl<< "10. Wczytanie elementów z pliku" <<endl
            << "11. Powrót do menu głównego" <<endl;
            cin>> option2;


            switch(option2)
                {
            case 1:
                {
                    int value;
                    system("cls");
                    cout << "Proszę podać wartość"<<endl;
                    cin>> value;
                    start = read_QPC();
                    list.add_start(value);
                    elapsed = read_QPC() - start;
                    cout << "Czas wykonania [us]  = " << fixed << setprecision(3) << (float)elapsed*1000000 / frequency << endl;
                    break;

                }
            case 2:
                {
                    system("cls");
                    int value;
                    cout << "Proszę podać wartość"<<endl;
                    cin>> value;
                    start = read_QPC();
                    list.add_end(value);
                    elapsed = read_QPC() - start;
                    cout << "Czas wykonania [us]  = " << fixed << setprecision(3) << (float)elapsed*1000000 / frequency << endl;
                    break;
                }
            case 3:
                {
                    system("cls");
                    int value,index;
                    cout << "Proszę podać wartość"<<endl;
                    cin>> value;
                    cout << "Proszę podać numer indeksu"<<endl;
                    cin >> index;
                    if (index>list.count)
                        cout << "Brak elementu na liście"<<endl;
                    else
                        start = read_QPC();
                    list.add(list.index(index), value);
                    elapsed = read_QPC() - start;
                    cout << "Czas wykonania [us]  = " << fixed << setprecision(3) << (float)elapsed*1000000 / frequency << endl;
                    break;
                }
            case 4:
                {
                    system("cls");
                    start = read_QPC();
                    list.remove_start();
                    elapsed = read_QPC() - start;
                    cout << "Czas wykonania [us]  = " << fixed << setprecision(3) << (float)elapsed*1000000 / frequency << endl;
                    break;
                }
            case 5:
                {
                    system("cls");
                    start = read_QPC();
                    list.remove_end();
                    elapsed = read_QPC() - start;
                    cout << "Czas wykonania [us]  = " << fixed << setprecision(3) << (float)elapsed*1000000 / frequency << endl;
                    break;
                }
            case 6:
                {
                    system("cls");
                    int index;
                    cout << "Proszę podać numer indeksu"<<endl;
                    cin >> index;
                    if (index>list.count)
                        cout << "Brak elementu na liście"<<endl;
                    else
                    start = read_QPC();
                    list.remove(list.index(index));
                    elapsed = read_QPC() - start;
                    cout << "Czas wykonania [us]  = " << fixed << setprecision(3) << (float)elapsed*1000000 / frequency << endl;
                    break;
                }
            case 7:
                {
                    system("cls");
                    start = read_QPC();
                    list.print_start();
                    elapsed = read_QPC() - start;
                    cout << "Czas wykonania [us]  = " << fixed << setprecision(3) << (float)elapsed*1000000 / frequency << endl;
                    break;
                }
                case 8:
                {
                    system("cls");
                    start = read_QPC();
                    list.print_end();
                    elapsed = read_QPC() - start;
                    cout << "Czas wykonania [us]  = " << fixed << setprecision(3) << (float)elapsed*1000000 / frequency << endl;
                    break;
                }
            case 9:
                {
                    system("cls");
                    int test, min_dist, max_dist;
                    cout << "Proszę podać ilość elementów, które mają być wylosowane"<<endl;
                    cin>> test;
                    if (test<1){
                        cout <<"Nieprawidłowa ilość elementów"<<endl;
                        break;}
                    cout<<endl;
                    cout << "Proszę podać minimalny zakres liczb, które mają być wylosowane"<<endl;
                    cin>> min_dist;
                    cout<<endl;
                    cout << "Proszę podać maksymalny zakres liczb, które mają być wylosowane"<<endl;
                    cin>> max_dist;
                    cout<<endl;
                    if (min_dist>=max_dist){
                        cout <<"Podano błędny zakres"<<endl;
                        break;}
                    start = read_QPC();
                    list.random(test, min_dist, max_dist);
                    elapsed = read_QPC() - start;
                    cout << "Czas wykonania [us]  = " << fixed << setprecision(3) << (float)elapsed*1000000 / frequency << endl;
                    break;
                }
            case 10:
                {
                    system("cls");
                    string file_name;
                    cout << "Proszę podać nazwę pliku z którego zostaną wczytane elementy, elementy muszą być w formacie: "<<endl;
                     cout << "1 cyfra oznacza liczbę elementów, kolejne są wartościami   "<<endl;
                    cin >> file_name;
                    start = read_QPC();
                    list.file_read(file_name);
                    elapsed = read_QPC() - start;
                    cout << "Czas wykonania [us]  = " << fixed << setprecision(3) << (float)elapsed*1000000 / frequency << endl;
                    break;

                }
            case 11:
                {

                work2=false;
                }
            default:
                break;
                }
            }while(work2);
            system("cls");

          break;
          }
          case 3:
              {
             BinaryHeap heap;

                work2=true;
              do{
            cout<< "Proszę wybrać działanie:"<<endl << "1. Dodawanie elementu do kopca" <<endl<< "2. Usunięcie korzenia "<<endl
            << "3. Wyświetlenie kopca" <<endl<< "4.Wylosowanie elementów kopca" <<endl
            << "5. Wczytanie elementów z pliku" <<endl << "6. Powrót do menu głównego" <<endl;

            cin>> option2;


            switch(option2)
                {
            case 1:
                {
                    int value;
                    system("cls");
                    cout << "Proszę podać wartość"<<endl;
                    cin>> value;
                    start = read_QPC();
                    heap.add(value);
                    elapsed = read_QPC() - start;
                    cout << "Czas wykonania [us]  = " << fixed << setprecision(3) << (float)elapsed*1000000 / frequency << endl;
                    break;


                }
            case 2:
                {
                    system("cls");
                    start = read_QPC();
                    heap.remove();
                    elapsed = read_QPC() - start;
                    cout << "Czas wykonania [us]  = " << fixed << setprecision(3) << (float)elapsed*1000000 / frequency << endl;
            break;
                }
            case 3:
                {
                    system("cls");
                    start = read_QPC();
                    heap.print();
                    elapsed = read_QPC() - start;
                    cout << "Czas wykonania [s]  = " << fixed << setprecision(3) << (float)elapsed / frequency << endl;

            break;
                }
            case 4:
                {
                    system("cls");
                    int test, min_dist, max_dist;
                     cout << "Proszę podać ilość elementów, które mają być wylosowane"<<endl;
                    cin>> test;
                    if (test<1){
                        cout <<"Nieprawidłowa ilość elementów"<<endl;
                        break;}
                    cout<<endl;
                    cout << "Proszę podać minimalny zakres liczb, które mają być wylosowane"<<endl;
                    cin>> min_dist;
                    cout<<endl;
                    cout << "Proszę podać maksymalny zakres liczb, które mają być wylosowane"<<endl;
                    cin>> max_dist;
                    cout<<endl;
                    if (min_dist>=max_dist){
                        cout <<"Podano błędny zakres"<<endl;
                        break;}
                    start = read_QPC();
                    heap.random(test, min_dist, max_dist);
                    elapsed = read_QPC() - start;
                    cout << "Czas wykonania [s]  = " << fixed << setprecision(3) << (float)elapsed / frequency << endl;
                    break;

                }
            case 5:
                {
                     system("cls");
                    string file_name;
                    cout << "Proszę podać nazwę pliku z którego zostaną wczytane elementy, elementy muszą być w formacie: "<<endl;
                     cout << "1 cyfra oznacza liczbę elementów, kolejne są wartościami   "<<endl;
                    cin >> file_name;
                    start = read_QPC();
                    heap.file_read(file_name);
                    elapsed = read_QPC() - start;
                    cout << "Czas wykonania [s]  = " << fixed << setprecision(3) << (float)elapsed / frequency << endl;
                    break;

                }

            case 6:
                {

                work2=false;
                }
            default:
                break;
                }
            }while(work2);
            system("cls");
            break;
          }

          case 4:
            {
                work=false;
            }
          default:
            break;
          }
            }while(work);





return 0;

}

