#ifndef GRAF_H_INCLUDED
#define GRAF_H_INCLUDED
#include "macierz.h"
#include "krawedz.h"
#include <iomanip>
#include <ctime>
#include <cstdlib>
using namespace std;

class Graf
{

public:
    int roz_krawedzi;                  // liczba krawedzi
    int roz_wierzcholkow;              // liczba wierzcholkow
    int rozmiark=0, rozmiarw=0;
    Krawedzz *krawedzie;                 // wskaznik na poczatek tablicy krawedzi
    int *wierzcholki;                   // wskaznik na poczatek tablicy wierzcholkow
    int **tab;                          // wskaznik na tablice dwuwymiarowa
    Macierz macierz;

    // konstruktor grafu

    Graf(int k, int w)
    {
        this->roz_krawedzi = k;
        this->roz_wierzcholkow = w;

        // Stworzenie tablic dynamicznych dla krawedzi i wierzcholków
        this->krawedzie = new Krawedzz[k];
        this->wierzcholki = new int[w];
    }

    // Uzupelnienie tablic

    void completeWierzcholki(int index, int wartosc)
    {
        wierzcholki[index] = wartosc;
        rozmiarw++;
    }

    void completeKrawedzie(int indeks, Krawedzz k)
    {
        krawedzie[indeks] = k;
        rozmiark++;
    }

    int znalezienie(int poczatek, int koniec)      // Zwrocenie indeksu
    {
        int znajduje = -1;

        for(int i=0; i<roz_krawedzi; i++)
        {
            if(krawedzie[i].poczatek == poczatek && krawedzie[i].koniec == koniec)
                znajduje = i;
        }

        return znajduje;
    }

    // Wyswietlenie tablicy wierzcholkow

    void displayWierzcholki()
    {
        for(int i=0; i<rozmiarw; i++)
            cout << wierzcholki[i] << " ";

        cout << endl;
    }

    void displayKrawedzie()
    {
        for(int i=0; i<rozmiark; i++)
        {
            cout << "(" << krawedzie[i].poczatek << ", " << krawedzie[i].koniec << "): " << krawedzie[i].przepustowosc << endl;
        }
    }

    // Funkcja sortujaca tablice wierzcholkow

    void sortWierzcholki()
    {
        int temp;
        for(int i=0; i<rozmiarw-1; i++)
        {
            for(int j= i+1; j<rozmiarw; j++)
            {
                if(wierzcholki[i]>wierzcholki[j])
                {
                    temp = wierzcholki[i];
                    wierzcholki[i] = wierzcholki[j];
                    wierzcholki[j] = temp;
                }
            }
        }
    }

    // Wyswietlenie wierzcholkow w kolejnosci uporzadkowanej

    void dispWierzcholki()
    {
        sortWierzcholki();
        displayWierzcholki();
    }

    void choice()
    {
        build();

        int wybor;

        macierz.displayMacierz();
        cout << endl;

        do
        {
            menu();
            cin >> wybor;
            system("cls");

            switch(wybor)
            {
                case 1:
                    {
                        // Brute Force

                        cout << endl << "ALGORYTM BRUTEFORCE" << endl;
                        int wierzcholek;

                        int blad;

                        do
                        {
                            blad=0;
                            cout << "Podaj indeks wierzcholka startowego: ";
                            cin >> wierzcholek;

                            if(wierzcholek>=roz_wierzcholkow || wierzcholek<0)
                                blad=1;

                        }while(blad==1);

                        macierz.bruteForce(wierzcholek);

                        break;
                    }
                case 2:
                    {
                        // Branch & Bound

                        cout << endl << "ALGORYTM BRANCH AND BOUND" << endl;
                        int wierzcholek;

                        int blad;

                        do
                        {
                            blad=0;
                            cout << "Podaj indeks wierzcholka startowego: ";
                            cin >> wierzcholek;

                            if(wierzcholek>=roz_wierzcholkow || wierzcholek<0)
                                blad=1;

                        }while(blad==1);

                        macierz.branchBound(wierzcholek);

                        break;
                    }
                case 3:
                    {
                        macierz.displayMacierz();
                        cout << endl;
                        break;
                    }
            }
        }
        while(wybor!=0);
    }

    void build()
    {
        macierz.stworz(krawedzie, wierzcholki, rozmiark, rozmiarw);
        macierz.buildMacierz();
    }

    // POMIARY

    void pomiary(int rozmiar)
    {
        ofstream plik("pomiary.txt", std::ios::app);
        srand(time(NULL));

        if(plik.is_open())
        {
                // 1. Algorytm Brute Force

                // losowanie wierzcholka startowego

                int w = rand() % rozmiar;

                //pomiar czasu przed wykonaniem operacji
                LARGE_INTEGER start;
                QueryPerformanceCounter(&start);

                macierz.bruteForce(w);

                //pomiar czasu po wykonaniu operacji
                LARGE_INTEGER koniec;
                QueryPerformanceCounter(&koniec);

                //obliczenie czasu
                LARGE_INTEGER frequency;
                QueryPerformanceFrequency(&frequency);
                double czas = (koniec.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;

                plik << czas << "   ";

                // 2. Algorytm Branch And Bound

                QueryPerformanceCounter(&start);

                macierz.branchBound(w);

                QueryPerformanceCounter(&koniec);

                //obliczenie czasu
                QueryPerformanceFrequency(&frequency);
                czas = (koniec.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;

                plik << czas << "   ";

                plik << endl;
        }
        else
            cout << "Nie udalo sie otworzyc pliku" << endl;

        plik.close();
    }

    void menu()
    {
        cout << "1. Algorytm Brute Force\n";
        cout << "2. Algorytm Branch & Bound\n";
        cout << "3. Wyswietlenie macierzy\n";
        cout << "0. EXIT\n";
    }
};

#endif // GRAF_H_INCLUDED

