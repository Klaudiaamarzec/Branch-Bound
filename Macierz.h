#ifndef MACIERZ_H_INCLUDED
#define MACIERZ_H_INCLUDED
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include "krawedz.h"
#include "tablica.h"
#include "lista2.h"
#include "BranchAndBound.h"

using namespace std;

HANDLE hOut1 = GetStdHandle( STD_OUTPUT_HANDLE );


 /**

 macierz krawedzi, kazda krawedz ma swoja wage

 1  jezeli a(i) jest lukiem wychodzacym
 -1 jezeli a(i) jest lukiem wchodzacym
 0  jezeli inaczej

**/


class Macierz
{

public:

    Krawedzz *k;        // wskaznik na poczatek tablicy krawedzi
    int *w;             // wskaznik na poczatek tablicy wierzcholkow

    int rozmiar_k;
    int rozmiar_w;
    int **macierz;       // Wskaznik na tablice dwuwymiarowa (macierz)


    int *najDroga = new int[rozmiar_w];
    // koszt najkrotszej trasy
    int minKoszt= INT_MAX;

    bool findd(int arr[], int siize, int value)
    {
        for(int i=0; i<siize; ++i)
        {
            if(arr[i] == value)
                return true;
        }

        return false;
    }

    // Konstruktor domyslny

    Macierz(): rozmiar_k(0), rozmiar_w(0), macierz(nullptr) {}

    void stworz(Krawedzz *tab_k, int *tab_w, int rk, int rw)
    {
        // Przekazujemy tablice wierzcholkow oraz tablice krawedzi
        this->rozmiar_k = rk;
        this->rozmiar_w = rw;
        this->k = tab_k;
        this->w = tab_w;

        // Stworzenie tablicy dwuwymiarowej

        // alokacja pamieci dla wierszy
        macierz = new int*[rozmiar_w];

        // alokacja pamiêci dla kolumn
        for (int i = 0; i < rozmiar_w; i++)
        {
            macierz[i] = new int[rozmiar_w];
        }
    }

    void buildMacierz()
    {
        // STWORZENIE MACIERZY SASIEDZTWA

        // Uzupelnienie tablicy dwywymiarowej zerami

        for(int i=0; i<rozmiar_w; i++)
        {
            for(int j=0; j<rozmiar_w; j++)
            {
                macierz[i][j] = 0;
            }
        }

        // Prawidlowe  uzupelnienie

        for(int i=0; i<rozmiar_w; i++)
        {
            for(int j=0; j<rozmiar_w; j++)
            {
                macierz[j][i] = k[i+rozmiar_w*j].przepustowosc;
            }
        }
    }

    // REPREZENTACJA MACIERZOWA - wyswietlenie grafu

    void displayMacierz()
    {
        cout << endl << " MIASTA" << endl;

        cout << "   |";

        for(int i=0; i<rozmiar_w; i++)
            cout << setw(6) << w[i] << " |";

        cout << endl;

        cout << "----";

        for(int i=0; i<rozmiar_w*8; i++)
            cout << "-";

        cout << endl;

        for(int i=0; i<rozmiar_w; i++)
        {
            cout << setw(2) << w[i] << " |";
            for(int j=0; j<rozmiar_w; j++)
            {

                cout << setw(4) << macierz[i][j] << "   |";

            }
            cout << endl;
        }
    }

    void algorytm(int droga[], int koszt, int miasto, int odwiedzone, int start)
    {
        if(odwiedzone == rozmiar_w)
        {
            // Powrot do miasta poczatkowego
            koszt += macierz[miasto][start];

            if(koszt < minKoszt)
            {
                minKoszt = koszt;
                for(int i=0; i<rozmiar_w; i++)
                    najDroga[i] = droga[i];
            }

            /*for(int i=0; i<rozmiar_w; i++)
                cout << droga[i] << " -> ";

            cout << droga[rozmiar_w] << ": " << koszt << endl;*/

            return;
        }

        for(int miasto2 = 0; miasto2 < rozmiar_w; miasto2++)
        {
            if(miasto2 == miasto)
                continue;

            if(!findd(droga, odwiedzone, miasto2))
            {
                int nowyKoszt = koszt + macierz[miasto][miasto2];
                droga[odwiedzone] = miasto2;
                algorytm(droga, nowyKoszt, miasto2, odwiedzone+1, start);
            }
        }
    }

    // ALGORYTM BRUTEFORCE

    void bruteForce(int start)
    {
        int droga[rozmiar_w+1];

        // Pierwszym wierzcholkiem jest wierzcholek startowy
        droga[0] = w[start];
        droga[rozmiar_w] = w[start];

        algorytm(droga, 0, w[start], 1, w[start]);

        cout << endl << "Najkrotsza trasa: ";
        for (int i = 0; i < rozmiar_w; ++i)
            cout << najDroga[i] << " -> ";

        cout << start << endl;
        cout << "Koszt: " << minKoszt << endl << endl;
    }

    // tu

    // ALGORYTM BRANCH AND BOUND

    void branchBound(int start)
    {
        BranchAndBound(rozmiar_w, macierz, start);
    }

    ~Macierz()
    {
        for (int i = 0; i < rozmiar_w; i++) {
            delete[] macierz[i];
        }

        delete[] macierz;
        delete[] najDroga;
    }

};

#endif // MACIERZ_H_INCLUDED

