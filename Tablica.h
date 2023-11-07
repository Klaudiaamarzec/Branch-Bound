#ifndef TABLICA_H_INCLUDED
#define TABLICA_H_INCLUDED

using namespace std;

/// a) Tablica

class Tablica
{

 public:
    int* head;        //wskaŸnik na pocz¹tek tablicy
    int rozmiar;      //liczba elementów w tablicy
    HANDLE hOut;

 public:

     //konstruktor tablicy
     Tablica(int rozmiar, HANDLE h)
     {
          this->rozmiar = rozmiar;
          this->head = new int[rozmiar];
          this->hOut = h;
     }

     //Menu dla tablicy

     void menu()
     {
         cout << "MENU TABLICA:" << endl;
         cout << "1. Wyswietlenie tablicy" << endl;
         cout << "2. Wyszukanie danego elementu w tablicy" << endl;
         cout << "3. Dodanie nowego elementu na poczatek tablicy" << endl;
         cout << "4. Dodanie nowego elementu na koniec tablicy" << endl;
         cout << "5. Dodanie nowego elementu w wybrane miejsce w tablicy" << endl;
         cout << "6. Usuniecie elementu z poczatku tablicy" << endl;
         cout << "7. Usuniecie elementu z konca tablicy" << endl;
         cout << "8. Usuniecie elementu z dowolnego miejsca w tablicy" << endl;
         cout << "0. EXIT" << endl;
     }

     void choice()
     {
         int wybor, idx, data, zwrot, w;
         do
         {
            this->menu();
            cin >> wybor;
            system("cls");

            switch(wybor)
            {
                case 1:
                    display();
                    break;

                case 2:
                    display();
                    cout << endl;
                    cout << "Podaj liczbe, ktora chcesz znalezc w tablicy: ";
                    cin >> w;
                    idx = findElem(w);
                    cout << endl;
                    if(idx == -1)
                        cout << "Nie znaleziono podanej liczby w tablicy\n";
                    else
                        displayColor(idx);
                    break;

                case 3:
                    display();
                    cout << endl;
                    cout << "Podaj nowa liczbe: ";
                    cin >> data;
                    addFirst(data);
                    break;

                case 4:
                    display();
                    cout << endl;
                    cout << "Podaj nowa liczbe: ";
                    cin >> data;
                    addLast(data);
                    break;

                case 5:
                    display();
                    cout << endl;
                    cout << "Podaj indeks, w ktorym chcesz umiescic nowa liczbe: ";
                    cin >> idx;
                    cout << "Podaj liczbe: ";
                    cin >> data;
                    zwrot = addAnywhere(idx, data);
                    cout << endl;

                    if(zwrot == 2)
                        cout << "Podano indeks wiekszy od tablicy\n";

                    displayColor(idx);
                    break;

                case 6:
                    display();
                    cout << endl;
                    zwrot = deleteElemFirst();

                    if(zwrot == 3)
                        cout << "Tablica jest pusta! Najpierw nalezy ja uzupelnic\n";

                    cout << endl;
                    display();
                    break;

                case 7:
                    display();
                    cout << endl;
                    zwrot = deleteElemLast();

                    if(zwrot == 3)
                        cout << "Tablica jest pusta! Najpierw nalezy ja uzupelnic\n";

                    cout << endl;
                    display();
                    break;

                case 8:
                    display();
                    cout << endl;
                    cout << "Podaj indeks liczby, ktora chcesz usunac z tablicy: ";
                    cin >> idx;
                    zwrot = deleteElemAny(idx);

                    if(zwrot == 3)
                        cout << "Tablica jest pusta! Najpierw nalezy ja uzupelnic\n";

                    if(zwrot == 2)
                        cout << "Podano indeks spoza zakresu tablicy " << endl;

                    cout << endl;
                    display();
                    break;

            }
            cout << endl;

         }while(wybor!=0);
     }

     //Uzupe³nienie tablicy wartosciami z pliku tekstowego

     void complete(int indeks, int liczba)
     {
         //if(head[rozmiar] == head[rozmiar-1])
         if(indeks == rozmiar)
         {
             return;
         }
         else
            head[indeks] = liczba;
     }

     //Wyswietlenie tablicy

     void display()
     {
          cout << "[";
          for(int i=0; i<rozmiar; i++)
          {
               cout << head[i];
               if(i<rozmiar-1)
                    cout << " ";
          }
          cout << "]"<< endl;

     }

     void displayColor(int index)
     {
         cout << "[";
          for(int i=0; i<rozmiar; i++)
          {
               if(i == index)
               {
                    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN );
                    cout << head[i];
                    SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
               }
               else
               {
                   cout << head[i];
               }

               if(i<rozmiar-1)
                    cout << " ";
          }
          cout << "]" << endl;
     }

     //dodawanie elementów na poczatek tablicy

     void addFirst(int dane)
     {
         int* new_tablica = new int[rozmiar + 1];

         for(int i=0; i<rozmiar+1; i++)
         {
             new_tablica[i] = head[i-1];
         }

         delete[] head; //to juz sie nie wykonuje
         head = new_tablica;
         head[0] = dane;
         rozmiar++;

         displayColor(0);
     }

     //dodawanie elementów na koñcu tablicy

     void addLast(int dane)
     {
        int* nowa_tablica = new int[rozmiar + 1];

        for(int i=0; i<rozmiar; i++)
        {
            nowa_tablica[i] = head[i];
        }
        delete[] head;
        head = nowa_tablica;
        head[rozmiar] = dane;
        rozmiar++;

        //displayColor(rozmiar-1);
     }

     //dodawanie elementów w dowolnym miejscu tablicy

     int addAnywhere(int indeks, int dane)
     {
         indeks--;

         if(indeks>rozmiar)
            return 2;
         else
         {
             int* nowa_tablica = new int[rozmiar+1];

             for(int i=0; i<indeks; i++)
             {
                 nowa_tablica[i] = head[i];
             }

             for(int i=indeks+1; i<rozmiar+1; i++)
             {
                 nowa_tablica[i] = head[i-1];
             }

             delete[] head;
             head = nowa_tablica;
             head[indeks] = dane;
             rozmiar++;
         }
     }

     //Wyszukiwanie elementu w tablicy

     int findElem(int value)
     {

         /*if(indeks<= 0 || indeks > rozmiar)
         {
             cout << "\nPodano indeks spoza zakresu tablicy!\n";
         }
         else
         {
             cout << "\nZnaleziona liczba to: " <<head[indeks-1] << endl;
         }*/

         for(int i=0; i<rozmiar; i++)
         {
             if(head[i] == value)
                return i;
         }
        return -1;
     }

     int returnValue(int index)
     {
         return head[index];
     }

     int findLast()
     {
         return head[rozmiar-1];
     }

     //usuwanie elementu w dowolnym miejscu tablicy

     int deleteElemAny(int indeks)
     {
         if(rozmiar<=0)
            return 3;
         else
         {
            if(indeks>=rozmiar)
            {
                return 2;
            }
            else
            {
                int* nowa_tablica = new int[rozmiar-1];

                for(int i=0; i<indeks; i++)
                {
                    nowa_tablica[i] = head[i];
                }

                for(int i=indeks; i<rozmiar-1; i++)
                {
                    nowa_tablica[i] = head[i+1];
                }

                delete[] head;
                head = nowa_tablica;
                rozmiar--;
            }
         }

     }

     //Usuniecie pierwszego elementu z tablicy

     int deleteElemFirst()
     {
        if(rozmiar<=0)
            return 3;
        else
        {
            int* nowa_tablica = new int[rozmiar-1];

            for(int i=1; i<rozmiar; i++)
            {
                nowa_tablica[i-1] = head[i];
            }

            delete[] head;
            head = nowa_tablica;
            rozmiar--;
        }
     }

     //Usuniecie ostatniego elementu z tablicy

     int deleteElemLast()
     {
        if(rozmiar<=0)
            return 3;
        else
        {
            int* nowa_tablica = new int[rozmiar-1];

            for(int i=0; i<rozmiar-1; i++)
            {
                nowa_tablica[i] = head[i];
            }

            delete[] head;
            head = nowa_tablica;
            rozmiar--;
        }

     }

     //destruktor
     ~Tablica()
     {
          if(rozmiar != 0)
              delete[] head;
     }
};


#endif // TABLICA_H_INCLUDED
