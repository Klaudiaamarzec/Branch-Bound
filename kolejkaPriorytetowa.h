#ifndef KOLEJKAPRIORYTETOWA_H_INCLUDED
#define KOLEJKAPRIORYTETOWA_H_INCLUDED

struct Wierzcholek
{
    int *trasa;
    int poziom;
    int granica;
    int koszt;
};

class KolejkaPriorytetowa
{

public:

    int rozmiar;
    Wierzcholek *kolejka;           // wskaznik na poczatek tablicy (kolejki)

    KolejkaPriorytetowa(int roz)
    {
        this->rozmiar = roz;
        kolejka = new Wierzcholek[roz];
    }

    void complete(Wierzcholek wierzcholek)
    {
        kolejka[0] = wierzcholek;
    }

    void display()
    {
        cout << "KOLEJKA" << endl;
        for(int i=0; i<rozmiar; i++)
        {
            for(int j=0; j<kolejka[i].poziom; j++)
            {
                cout << kolejka[i].trasa[j] << "->";
            }

            cout << kolejka[i].trasa[kolejka[i].poziom] << ": " << kolejka[i].granica << endl;
        }
    }

    // dodanie nowego wierzcholka na koniec kolejki
    void addNew(Wierzcholek nowy)
    {
        Wierzcholek *nowaKolejka = new Wierzcholek[rozmiar+1];

        for(int i=0; i<rozmiar; i++)
            nowaKolejka[i] = kolejka[i];

        nowaKolejka[rozmiar++] = nowy;
        delete[] kolejka;
        kolejka = nowaKolejka;
    }

    // usuniecie wybranego elementu z tablicy

    void deleteElem(Wierzcholek wierzcholek)
    {
        int index;

        // Szukanie indeksu elementu do usuniecia
        for(int i=0; i<rozmiar; i++)
        {
            if(kolejka[i].poziom == wierzcholek.poziom && kolejka[i].granica == wierzcholek.granica && kolejka[i].koszt == wierzcholek.koszt)
            {
                bool same=true;
                // Porownanie tras
                for(int j=0; j<kolejka[i].poziom+1; j++)
                {
                    if(kolejka[i].trasa[j] != wierzcholek.trasa[j])
                        same = false;
                }

                if(same == true)
                    index = i;
            }
        }

        // Usuniecie indeksu

        Wierzcholek *nowaKolejka = new Wierzcholek[rozmiar-1];

        for(int i=0; i<index; i++)
        {
            nowaKolejka[i] = kolejka[i];
        }

        for(int i=index; i<rozmiar-1; i++)
        {
            nowaKolejka[i] = kolejka[i+1];
        }

        delete[] kolejka;
        kolejka = nowaKolejka;
        rozmiar--;
    }

    void deleteAll(int najlepszaGranica)
    {
        for(int i=0; i<rozmiar; i++)
        {
            if(kolejka[i].granica > najlepszaGranica)
            {
                // usuniecie elementu z kolejki
                deleteElem(kolejka[i]);
                i=-1;                        // po usunieciu powrot do poczatku tak, zeby przegladac od nowa
            }
        }
    }

    // Funkcja znajdujaca najlepsza mozliwa granice w kolejce i zwracajaca znaleziony wierzcholek

    Wierzcholek bestNode()
    {
        Wierzcholek best = kolejka[0];

        for(int i=0; i<rozmiar; i++)
        {
            if(kolejka[i].granica < best.granica)
                best = kolejka[i];
        }

        return best;
    }

    ~KolejkaPriorytetowa()
    {
        delete[] kolejka;
    }

};

#endif // KOLEJKAPRIORYTETOWA_H_INCLUDED
