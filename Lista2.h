#ifndef LISTA2_H_INCLUDED
#define LISTA2_H_INCLUDED

/// b) Lista dwukierunkowa

struct ListaElem //dla pojedynczego elementu
{

public:
    int data;
    struct ListaElem *next, *prev; //wskaŸnik na nastêpny i kolejny element
};

class Lista2
{

 public:
    ListaElem *head, *tail;
    int rozmiar;
    HANDLE hOut;

 public:

    // konstruktor domyslny

    Lista2()
    {
        this->head = NULL;
        this->tail = NULL;
        this->rozmiar = 0;
        this->hOut = NULL;
    }

    //konstruktor

    Lista2(int rozmiar, HANDLE h)
    {
        this->head = NULL;
        this->tail = NULL;
        this->rozmiar = rozmiar;    //rozmiar wczytany z pliku
        this->hOut = h;
    }

    void menu()
     {
         cout << "MENU LISTY DWUKIERUNKOWEJ:" << endl;
         cout << "1. Wyswietlenie listy" << endl;
         cout << "2. Wyszukanie danego elementu na liscie" << endl;
         cout << "3. Wyszukanie danej wartosci na liscie" << endl;
         cout << "4. Dodanie nowego elementu na poczatek listy" << endl;
         cout << "5. Dodanie nowego elementu na koniec listy" << endl;
         cout << "6. Dodanie nowego elementu w wybrane miejsce na liscie" << endl;
         cout << "7. Usuniecie elementu z poczatku listy" << endl;
         cout << "8. Usuniecie elementu z konca listy" << endl;
         cout << "9. Usuniecie elementu z dowolnego miejsca na liscie" << endl;
         cout << "0. EXIT" << endl;
     }

    void choice()
     {
         int wybor, dane, ind, zwrot, w;
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
                    cout << "Podaj indeks liczby, ktora chcesz wyswietlic: " << endl;
                    cin >> ind;
                    zwrot = findElem(ind);
                    cout << endl;

                    if(zwrot == 2)
                        cout << "Podano nieprawidlowy indeks " << endl;
                    else
                        displayColor(ind);     //cout << "Znaleziony element to: " << zwrot << endl;

                    break;

                case 3:
                    display();
                    cout << endl;
                    cout << "Podaj wartosc, ktora chcesz znalezc na liscie: " << endl;
                    cin >> w;
                    ind = find2(w);
                    cout << endl;
                    if(ind == -1)
                        cout << "Nie znaleziono podanej liczby w tablicy\n";
                    else
                        displayColor(ind);
                    break;

                case 4:
                    display();
                    cout << endl;
                    cout << "Podaj liczbe, ktora chcesz dodac do listy: ";
                    cin >> dane;
                    addFirst(dane);
                    cout << endl;
                    displayColor(1);
                    break;

                case 5:
                    display();
                    cout << endl;
                    cout << "Podaj liczbe, ktora chcesz dodac do listy: ";
                    cin >> dane;
                    addLast(dane);
                    cout << endl;
                    displayColor(rozmiar);
                    break;

                case 6:
                    display();
                    cout << endl;
                    cout << "Podaj indeks, gdzie chcesz dodac element do listy: ";
                    cin >> ind;
                    cout << "Podaj liczbe, ktora chcesz dodac do listy: ";
                    cin >> dane;
                    addAnywhere(ind, dane);
                    cout << endl;
                    if(ind>rozmiar)
                        displayColor(rozmiar);
                    else
                        displayColor(ind);
                    break;

                case 7:
                    display();
                    cout << endl;
                    zwrot = deleteFirst();

                    if(zwrot == 3)
                        cout << "Lista jest pusta! Najpierw nalezy ja uzupelnic\n";

                    cout << endl;
                    display();
                    break;

                case 8:
                    display();
                    cout << endl;
                    zwrot = deleteLast();

                    if(zwrot == 3)
                        cout << "Lista jest pusta! Najpierw nalezy ja uzupelnic\n";

                    cout << endl;
                    display();
                    break;

                case 9:
                    display();
                    cout << endl;
                    cout << "Podaj indeks elementu, ktory chcesz usunac z listy: ";
                    cin >> ind;
                    zwrot = deleteAny(ind);

                    if(zwrot == 3)
                        cout << "Lista jest pusta! Najpierw nalezy ja uzupelnic\n";
                    if(zwrot == 2)
                        cout << "Bledny indeks! " << endl;

                    cout << endl;
                    display();
                    break;

            }
            cout << endl;

         }while(wybor!=0);
     }

    //dodawanie elementu na pocz¹tek listy

    void addFirst(int value)
    {
        ListaElem *p = new ListaElem;
        p->data = value;

        if(head == NULL)
        {
            cout << "Glowa pusta\n";
            head = p;
            tail = p;
            p->next = NULL;
            p->prev = NULL;
        }

        else if(head!=NULL)
        {
            head->prev = p;
            p->next = head;
            p->prev =NULL;
            head = p;
        }
        rozmiar++;
    }

    //Funkcja uzupe³niaj¹ca listê na samym pocz¹tku, bez zmiany jej rozmiaru

    void addElements(int value)
    {
        ListaElem *p = new ListaElem;
        p->data = value;

        if (tail == NULL)
        {
            tail = p;
            head = p;
            p->next = NULL;
            p->prev = NULL;
        }
        else
        {
            tail->next = p;
            p->prev = tail;
            p->next = NULL;
            tail = p;

            //if (tail->data == value)    //Warunek po to, zeby ostatni element nie zosta³ dodany dwa razy
           // {
           //     delete p;
            //    return;
          //  }
            //else
        }

    }

    //dodawanie elementu na koniec listy

    void addLast(int value)
    {
        ListaElem *p = new ListaElem;
        p->data = value;

        if(tail == NULL || rozmiar == 0)
        {
            tail = p;
            head = p;
            p->next = NULL;
            p->prev = NULL;
        }

        else if(tail!=NULL)
        {
            tail->next = p;
            p->prev = tail;
            p->next = NULL;
            tail = p;
        }
        rozmiar++;
    }

    //dodawanie elementu w dowolne miejsce listy

    void addAnywhere(int indeks, int value)
    {

        float liczba = rozmiar/2.0;

        ListaElem *p = new ListaElem;   //nowy element
        p->data = value;
        ListaElem *currentElem;

        if(rozmiar==0)
        {
            head = p;
            tail = p;
            p->next = NULL;
            p->prev = NULL;
        }
        else
        {
            if(indeks<=liczba)           //indeks znajduj¹cy siê miêdzy pocz¹tkiem a po³ow¹ listy - startujemy od g³owy
            {
                currentElem = head;     //aktualny element, start od g³owy
                for(int i=1; i<indeks; i++)
                {
                    currentElem = currentElem->next;
                }
            }

            if(indeks>liczba)                             //indeks znajduj¹cy siê miêdzy po³ow¹ a koñcem listy, wiêc start od ogona
            {
                currentElem = tail;                       //aktualny element, start od ogona
                for(int i = rozmiar-1; i >= indeks; i--)
                {
                    currentElem = currentElem->prev;
                }
            }

            if(indeks>rozmiar+1)
                cout << "Podano za duzy indeks. Element zostal dodany na koniec listy" << endl;

            p->prev = currentElem->prev;
            p->next = currentElem;
            currentElem->prev->next = p;
            currentElem->prev = p;
        }

        rozmiar++;
    }

    //wyœwietlenie listy

    void display()
    {
        ListaElem *currentElem = head;

        for(int i=1; i<=this->rozmiar; i++)
        {
            cout << currentElem->data << " ";
            currentElem = currentElem->next;
        }
        //cout << endl;
    }

    void displayColor(int index)
    {
        ListaElem *currentElem = head;
        //int i=1;

        for(int i=1; i<=rozmiar; i++)
        {
            if(i == index)
            {
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN );
                cout << currentElem->data << " ";
                SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            else
            {
                cout << currentElem->data << " ";
            }
            currentElem = currentElem->next;
            //i++;
        }
        cout << endl;
    }

    //Wyszukanie elementu

    int findElem(int indeks)
    {
        float liczba = rozmiar/2.0;
        ListaElem *currentElem;

        if(indeks>rozmiar || indeks <= 0)
        {
            return 2;
        }
        else
        {
            if(indeks<=liczba)                 //indeks znajduj¹cy siê miêdzy pocz¹tkiem a po³ow¹ listy - startujemy od g³owy
            {
                currentElem = head;             //aktualny element, start od g³owy
                for(int i=1; i<indeks; i++)
                {
                    currentElem = currentElem->next;
                }
            }
            else if(indeks>liczba)                  //indeks znajduj¹cy siê miêdzy po³ow¹ a koñcem listy, wiêc start od ogona
            {
                currentElem = tail;                 //aktualny element, start od ogona
                for(int i = rozmiar; i >indeks; i--)
                {
                    currentElem = currentElem->prev;
                }
            }

            return currentElem->data;
        }
    }

    int find2(int value)
    {
        ListaElem *currentElem = head;
        for(int i=1; i<=this->rozmiar; i++)
        {
            if(currentElem->data == value)
            {
                return i;
            }
            currentElem = currentElem->next;
        }
        return -1;
    }

    //Usuniecie pierwszego elementu z listy

    int deleteFirst()
    {
        if(rozmiar<=0)
            return 3;
        else
        {
            if(rozmiar == 1)
            {
                delete head;
            }
            else
            {
                head = head->next;
                delete head->prev;
                head->prev = NULL;

            }

            rozmiar--;
        }
    }

    //Usuniecie ostatniego elementu z listy

    int deleteLast()
    {
        if(rozmiar<=0)
            return 3;
        else
        {
            if(rozmiar==1)
            {
                delete tail;
            }
            else
            {
                tail = tail->prev;
                delete tail->next;
                tail->next = NULL;
            }
            rozmiar--;
        }
    }

    //Usuniecie wybranego elementu z listy

    int deleteAny(int indeks)
    {
        if(rozmiar<=0)
            return 3;
        else
        {
            if(rozmiar==1)
            {
                delete head;
            }
            else
            {
                float liczba = rozmiar/2.0;

                ListaElem *currentElem;

                if(indeks>rozmiar || indeks<=0)
                {
                    return 2;
                }
                else
                {
                    if(indeks<=liczba)                  //indeks znajduj¹cy siê miêdzy pocz¹tkiem a po³ow¹ listy - startujemy od g³owy
                    {
                        if(indeks == 1)
                        {
                            deleteFirst();
                            return 5;
                        }
                        else
                        {
                            currentElem = head;             //aktualny element, start od g³owy
                            for(int i=1; i<indeks; i++)
                            {
                                currentElem = currentElem->next;
                            }
                        }
                    }

                    if(indeks>liczba)                               //indeks znajduj¹cy siê miêdzy po³ow¹ a koñcem listy, wiêc start od ogona
                    {
                        if(indeks == rozmiar)
                        {
                            deleteLast();
                            return 5;
                        }
                        else
                        {
                            currentElem = tail;                         //aktualny element, start od ogona
                            for(int i = rozmiar; i > indeks; i--)
                            {
                                currentElem = currentElem->prev;
                            }
                        }
                    }

                    currentElem->prev->next = currentElem->next;
                    currentElem->next->prev = currentElem->prev;
                    delete currentElem;
                }

            }
        rozmiar--;
        }
    }

    //dekonstruktor

    ~Lista2()
    {
        if(rozmiar!=0)
        {
            ListaElem *currentElem = head;

            for(int i=0; i<this->rozmiar-1; i++)
            {
                currentElem = currentElem->next;
                delete currentElem->prev;
            }
            delete currentElem;

            /*this->head = NULL;
            this->tail = NULL;*/
        }
    }
};

#endif // LISTA2_H_INCLUDED

