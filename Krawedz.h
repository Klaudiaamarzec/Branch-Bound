#ifndef KRAWEDZ_H_INCLUDED
#define KRAWEDZ_H_INCLUDED

struct Krawedzz          // Struktura dla pojedynczej krawedzi
{
public:
    unsigned int przepustowosc;
    int poczatek;       // wierzcholek poczatkowy
    int koniec;         // wierzcholek koncowu

    /*Krawedzz(int p, int k, int prz)
    {
        this->poczatek = p;
        this->koniec = k;
        this->przepustowosc = prz;
    }*/
};

#endif // KRAWEDZ_H_INCLUDED

