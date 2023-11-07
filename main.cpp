#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <math.h>
#include <windows.h>
#include "macierz.h"
#include "graf.h"
#include "tablica.h"

using namespace std;

HANDLE hOut = GetStdHandle( STD_OUTPUT_HANDLE );

void menu1();

Graf stworzGraf(int w);

int main()
{
    int wybor1;
    srand(time(NULL));

    do
    {
        //system("cls");
        cout << "W jaki sposob chcesz uzupelnic strukture grafu?\n" << endl;
        menu1();
        cin >> wybor1;
        system("cls");

         // Wczytanie danych: 1 - z pliku, 2 - wygenerowanie losowo

        switch(wybor1)
        {
            case 1:
                {
                    string nazwa;
                    cout << "Podaj nazwe pliku, z ktorego chcesz wczytac dane: ";
                    cin >> nazwa;
                    int blad= 0;

                    ifstream plik(nazwa);

                    if(plik.is_open())
                    {
                       string linia;
                       int krawedzie, wierzcholki, indeks=0, idx=0;

                       plik >> wierzcholki;
                       krawedzie = wierzcholki*wierzcholki;

                       Graf graf(krawedzie, wierzcholki);

                       // Uzupelnienie wierzcholkow z pierwszej linijki

                       int a, b, c;

                       plik >> a;
                       plik >> b;
                       plik >> c;

                       if(c < 0)
                       {
                           blad = 1;
                           break;
                       }

                       graf.completeWierzcholki(indeks++, a);

                       if(a!=b)
                        graf.completeWierzcholki(indeks++, b);

                       Krawedzz kra;
                       kra.poczatek =a;
                       kra.koniec = b;
                       kra.przepustowosc = c;

                       graf.completeKrawedzie(idx++, kra);

                       while(getline(plik, linia))
                        {
                            int x, y, z, rezultat;              // rezultat: 1 - jest w tablicy, 2- nie ma w tablicy

                            plik >> x;
                            plik >> y;
                            plik >> z;

                            if(z < 0)
                            {
                                blad = 1;
                                break;
                            }

                            // x - pierwsza krawedz
                            // y - druga krawedz
                            // z - przepustowowsc krawedzi

                            // DODAWANIE WIERZCHO£KÓW DO TABLICY

                            // Sprawdzenie, czy w tabeli wierzcho³ków znajduje siê ju¿ dany wierzcho³ek

                               for(int j=0; j<graf.rozmiarw; j++)
                               {
                                   if(x != graf.wierzcholki[j])
                                   {
                                       rezultat = 2;
                                       continue;
                                   }
                                   else
                                   {
                                       rezultat = 1;
                                       break;
                                   }
                               }

                               if(rezultat == 2)           // Jezeli nie ma w tablicy, to dodajemy
                                   graf.completeWierzcholki(indeks++, x);

                               for(int j=0; j<graf.rozmiarw; j++)
                               {
                                   if(y != graf.wierzcholki[j])
                                   {
                                       rezultat = 2;
                                       continue;
                                   }
                                   else
                                   {
                                       rezultat = 1;
                                       break;
                                   }
                               }

                               if(rezultat == 2)
                                   graf.completeWierzcholki(indeks++, y);

                            // DODAWANIE KRAWEDZI

                            Krawedzz k;
                            k.poczatek =x;
                            k.koniec = y;
                            k.przepustowosc = z;

                            graf.completeKrawedzie(idx++, k);

                        }

                        if(blad != 1)
                        {
                            // Posortowanie wierzcholkow
                            graf.sortWierzcholki();

                            cout << "STRUKTURA GRAFU" << endl;
                            graf.displayKrawedzie();
                            cout << endl;

                            plik.close();
                            graf.choice();
                        }
                        else
                            cout << "Graf zawiera ujemne krawedzie! Zmien strukture grafu" << endl << endl;
                    }
                    else
                        cout << "Nie udalo sie otworzyc pliku" << endl;

                    break;
                }
            case 2:
                {
                    // LOSOWO
                    int wierzcholki;
                    cout << "Podaj liczbe wierzcholkow\n";
                    cin >> wierzcholki;

                    // LOSOWO

                    Graf graf = stworzGraf(wierzcholki);

                    if(graf.roz_krawedzi == 0 && graf.roz_wierzcholkow == 0)
                        break;

                    cout << "STRUKTURA GRAFU" << endl;
                    graf.displayKrawedzie();
                    cout << endl;
                    graf.choice();
                    cout << endl;

                    break;
                }
            case 3:
                {
                     // LOSOWO

                    int wierzcholki=13;

                    // Seria losowych instancji - 100

                    for(int i=0; i<100; i++)
                    {
                        Graf graf = stworzGraf(wierzcholki);
                        graf.build();

                        graf.pomiary(wierzcholki);
                    }

                    break;
                }
        }
    }while(wybor1!=0);

    return 0;
}

void menu1()
{
    cout << "1. Wczytanie danych z pliku\n";
    cout << "2. Losowe wygenerowanie grafu\n";
    cout << "3. POMIARY\n";
    cout << "0. EXIT" << endl;
}

Graf stworzGraf(int w)
{
    // LOSOWO

    // liczba krawedzi w grafie
    int k = w*w;

    // Zalozenie - asymetrycszny problem komiwojazera

    system("cls");

    Graf graf(k, w);
    int rezultat, zawiera, zawiera2, los_start, los_koniec, start, koniec, cykl;

    // Uzupelnienie tablicy wierzcholkow
    // Przyjmujemy ze wierzcholki numerowane sa od 0 po kolei

    for(int i=0; i<w; i++)
    {
        graf.completeWierzcholki(i, i);
    }

    int index=0;

    for(int i=0; i<w; i++)
    {
        for(int j=0; j<w; j++)
        {
            Krawedzz k;
            k.poczatek = i;
            k.koniec = j;

            // Sprawdzenie czy w tablicy krawedzi znajduje sie juz taka tylko ze od drugiej strony

            if(graf.znalezienie(j, i) != -1)
            {
                // Wylosowanie odleglosci zblizonej do tej ktora jest juz wylosowana dla tej krawedzi

                int ind = graf.znalezienie(j, i);
                int odleglosc = graf.krawedzie[ind].przepustowosc;

                if(i==j)
                    k.przepustowosc = 0;
                else
                {
                    // Losowanie znaku + lub -

                    int znak = rand() % 2;

                    // 0 -
                    // 1 +

                    // Losowanie roznicy

                    int roznica = rand() % 51;

                    if(znak == 0)
                        k.przepustowosc = odleglosc - roznica;
                    else
                        k.przepustowosc = odleglosc + roznica;
                }
            }
            else
            {
                // Losowanie odleglosci miedzy miastami

                if(i==j)
                    k.przepustowosc = 0;
                else
                {
                    k.przepustowosc = rand() % 1000 + 1;         // Losowanie odleglosci z zakresu <1, 1000>
                }
            }

            graf.completeKrawedzie(index++, k);
        }
    }

    return graf;

}
