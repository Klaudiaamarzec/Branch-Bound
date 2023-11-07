#ifndef BRANCHANDBOUND_H_INCLUDED
#define BRANCHANDBOUND_H_INCLUDED
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <climits>
#include "kolejkaPriorytetowa.h"

using namespace std;

class BranchAndBound
{

private:
    int rozmiar;
    int *najDroga = new int[rozmiar+1];
    int najKoszt = INT_MAX; //oo
    int **macierz;
    int start;

public:

    BranchAndBound(int rozmiarw, int **wskaznik, int st)
    {
        rozmiar = rozmiarw;
        macierz = wskaznik;
        start = st;

        // Wywolanie od razu funkcji wykonujacej algorytm
        branchBound();
    }

    int minDlugosc(int wierzcholek, int *droga, int roz)
    {
        int minimum = INT_MAX;

        for(int i=0; i<rozmiar; i++)
        {
            int blad = 0;

            if(wierzcholek == droga[roz-1])
            {
                for(int j=0; j<roz; j++)
                {
                    if(droga[j] == i)
                        blad = 1;
                }
            }
            else
            {
                for(int j=1; j<roz; j++)
                {
                    if(droga[j] == i)
                        blad = 1;
                }
            }

            if(blad == 1 || i == wierzcholek)
                continue;

            if(macierz[wierzcholek][i] < minimum)
                minimum = macierz[wierzcholek][i];
        }

        return minimum;
    }

    int bound(int *wierzcholek, int poziom)
    {
        int roz = poziom+1;

        // Przekazujemy tablice miast - trasa w danym wierzcholku grafu

        int sumaMinimum = 0;

        // Dlugosc tras pomiedzy miastami w wierzcholku

        for(int i=0; i<roz-1; i++)
            sumaMinimum += macierz[wierzcholek[i]][wierzcholek[i+1]];

        if(roz==rozmiar)
        {
            return sumaMinimum;
        }

        // Minimum sposrod pozostalych

        for(int i=0; i<rozmiar; i++)
        {
            int blad = 0;
            for(int j=0; j<roz-1; j++)        // Pominiecie wierzcholkow juz rozpatrzonych, nie liczac ostatniego elementu
            {
                if(wierzcholek[j] == i)
                    blad = 1;
            }

            if(blad == 1)
                continue;

            // Wyznaczenie minimum dla kolejnych wierzcholkow

            int minDl = minDlugosc(i, wierzcholek, roz);
            sumaMinimum += minDl;
        }

        return sumaMinimum;
    }

    void branchBound()
    {
        /**

        Dzieci kazdego wezla oznaczaja konkretne sytuacje

        W przypadku problemu komiwojazera sa to etapy przechodzenia pomiedzy sciezkami, np.:

                             4                                      lvl 0
                    4->1    4->2    4->3                            lvl 1
        4->1->2  4->1->3  4->2->1  4->2->3  4->3->1  4->3->2        lvl 2

        STRATEGIA NAJPIERW NAJLEPSZY:
        Po przejrzeniu symow jakiegos wezla przegladamy wszystkie pozostale
        nierozwiniete obiecujace wezly i rozwijamy wezel o najlepszej granicy


        **/

        int *korzen = new int[1];
        korzen[0] = start;             // indeksy miast

        // Granica dla korzenia

        int granica = bound(korzen, 0);

        Wierzcholek root = {korzen, 0, granica, 0};

        // inicjalizacja kolejki

        KolejkaPriorytetowa kolejka(1);
        kolejka.complete(root);             // Dodanie korzenia do kolejki priorytetowej

        while(kolejka.rozmiar>0)
        {
            /*kolejka.display();
            cout << endl;*/
            // Wybranie wierzcholka o najmniejszej granicy sposrod obiecujacych

            Wierzcholek node = kolejka.bestNode();

            // Usuniecie z kolejki aktualnego wierzcholka
            kolejka.deleteElem(node);

            /*cout << "Najlepszy wybor: " << endl;

            for(int i=0; i<node.poziom; i++)
                cout << node.trasa[i] << "->";

            cout << node.trasa[node.poziom] << endl;*/

            // Zdjecie wierzcholka z kolejki o najmniejszej obiecujacej granicy

            int poziom = node.poziom;
            int *trasa = node.trasa;
            int koszt = node.koszt;

            if(poziom+1 == rozmiar)
            {
                koszt += macierz[node.trasa[rozmiar-1]][node.trasa[0]];

                if(koszt < najKoszt)
                {
                    najKoszt = koszt;

                    for(int k=0; k<rozmiar+1; k++)
                        najDroga[k] = trasa[k];

                    najDroga[rozmiar] = najDroga[0];

                    /*cout << endl << "NAJLEPSZA TRASA" << endl;
                    for (int i = 0; i < rozmiar; i++)
                        cout << najDroga[i] << " -> ";

                    cout << najDroga[rozmiar] << endl;
                    cout << "Koszt: " << najKoszt << endl << endl;*/

                    // Usuniecie z kolejki wszystkich nieobiecujacych wezlow

                    kolejka.deleteAll(najKoszt);
                }

                delete[] trasa;
            }
            else
            {
                for(int i=0; i<rozmiar; i++)
                {
                    // Przejrzenie synow

                    // Sprawdzenie czy w aktualnej trasie nie znajduje sie juz element i
                    int next=0;

                    for(int j=0; j<poziom+1; j++)
                    {
                        if(trasa[j] == i)
                            next=1;
                    }

                    if(macierz[trasa[poziom]][i] != 0 && next == 0)
                    {
                        // Utworzenie nowego wezla bedacego synem aktualnego:
                        // obecna sciezka plus i

                        // Rozmiar o 2 wiekszy, poniewaz rozmiar na danym poziomie to poziom+1

                        int nowyRozmiar = poziom+2;
                        int *dziecko = new int[nowyRozmiar];
                        for(int i=0; i<nowyRozmiar; i++)
                            dziecko[i] = trasa[i];

                        dziecko[nowyRozmiar-1] = i;

                        int nowaGranica = bound(dziecko, poziom+1);

                        // Dodanie do kolejki tylko wezlow obiecujacych
                        if(nowaGranica < najKoszt)
                        {
                            int nowyKoszt = koszt + macierz[trasa[poziom]][i];
                            Wierzcholek potomek = {dziecko, poziom+1, nowaGranica, nowyKoszt};

                            kolejka.addNew(potomek);
                        }
                        else
                        {
                            delete[] dziecko;
                        }

                    }
                }

                delete[] trasa;
            }
        }

        cout << endl << "NAJLEPSZA TRASA" << endl;
        for(int i = 0; i < rozmiar; i++)
            cout << najDroga[i] << " -> ";

        cout << najDroga[rozmiar] << endl;
        cout << "Koszt: " << najKoszt << endl << endl;

    }

    ~BranchAndBound()
    {
        delete[] najDroga;
    }

};

#endif // BRANCHANDBOUND_H_INCLUDED
