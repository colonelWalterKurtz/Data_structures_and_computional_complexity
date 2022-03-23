#include<iostream>
#include<chrono>
#include<fstream>
#include<string>

using namespace std;

// zmienne globalne
string nazwa_pliku_wejsciowego;
int instancje[17];
int liczba_pomiarow;
int jakie_sortowanie;
string nazwa_pliku_wyjciowego;
string nazwa_pliku_z_czasami;

// zmienne globalne
string nazwa_pliku_wejsciowego;
int instancje[17];
int liczba_pomiarow;
int jakie_sortowanie;
string nazwa_pliku_wyjciowego;
string nazwa_pliku_z_czasami;

// sekcja funkcyjna
void inicjalizacja(string nazwa_ini);
void sprawdzenie_inicjalizacji();
void wczytanie_danych(int* wsk, int ilosc_wczytywanych_liczb, string nazwa_pliku_z_danymi);
void sprawdzenie_tablicy(int* wsk, int ilosc_wczytywanych_liczb);
void zapisz_posortowane(int* wsk, int ile_elementow_w_tablicy, string nazwa_pliku);
void utworzenie_pliku_z_pomiarami(string nazwa_pliku_z_pomiarami, int liczba_prob);
long double policz_srednia(unsigned long long int* wsk, int ilosc_elementow_w_tablicy);
void zapisanie_pomiarow_instancji(string nazwa_pliku_z_pomiarami, int liczba_instancji, unsigned long long int* wsk_na_czas_pomiaru, int liczba_prob, long double srednia);

// sekcja sortowań
void sort_przez_zliczanie();
void sort_przez_kopcenie();


int main()
{
    inicjalizacja("inicjalizacja.ini");
    /*sprawdzenie_inicjalizacji();*/
    cout<<liczba_pomiarow<<endl;
    utworzenie_pliku_z_pomiarami(nazwa_pliku_z_czasami, liczba_pomiarow);

    for (int i = 0; i < 17; i++)
    {
        // utworzenie tablicy zbierającej pomiary czasu
        unsigned long long int* wsk_na_pomiary = new unsigned long long int[liczba_pomiarow];
        cout<<"Rozpoczecie pomiarow dla "<<instancje[i]<<" liczby instancji"<<endl;

        for (int j = 0; j < liczba_pomiarow; j++)
        {
            // alokacja pamieci na tablice z wczytanymi liczbami
            int* tab=new int[instancje[i]];
            wczytanie_danych(tab, instancje[i], nazwa_pliku_wejsciowego);
            /*sprawdzenie_tablicy(tab, instancje[i]);*/

            // rozpoczecie pomiaru czasu sortowania
            chrono::steady_clock::time_point begin = chrono::steady_clock::now();

            switch (jakie_sortowanie)
            {
            case 1: // przez zliczanie
                quick_sort(tab, 0, instancje[i]);
                break;
            
            case 2: // przez kopcenie
                bubble_sort(tab, instancje[i]);
                break;

            default:
                cout<<"Blednie wybrane sortowanie"<<endl;
                exit(-1);
                break;
            }
            /*sprawdzenie_tablicy(tab, instancje[i]);*/

            // zakonczenie pomiaru czasu sortowania
            chrono::steady_clock::time_point end = chrono::steady_clock::now();
            unsigned long long int time_dif = chrono::duration_cast<chrono::microseconds>(end-begin).count();
            /*cout<<j+1<<".\t"<<time_dif<<endl;*/
            wsk_na_pomiary[j]=time_dif;


            // zapis do pliku posortowanych liczb z ostaniej instancji
            if (i==16 && j==(liczba_pomiarow-1))
            {
                string nazwa_pliku_z_posortowanymi_liczbami = nazwa_pliku_wyjciowego;
                switch (jakie_sortowanie)
                {
                case 1:
                    nazwa_pliku_z_posortowanymi_liczbami += "_przez_zliczanie";
                    break;
                case 2:
                    nazwa_pliku_z_posortowanymi_liczbami += "_przez_kopcenie";
                    break;
                default:
                    cout<<"Blednie wybrane sortowanie"<<endl;
                    exit(-1);
                    break;
                }
                nazwa_pliku_z_posortowanymi_liczbami+=".txt";
                cout<<"Zapis posortowanych liczb do pliku "<<nazwa_pliku_z_posortowanymi_liczbami<<endl;
                zapisz_posortowane(tab, instancje[i], nazwa_pliku_z_posortowanymi_liczbami);
            }
            // zwolnienie miejsca w pamieci tablicy zawierajacej wczytane liczby
            delete[] tab;
        }
        // zapisanie pomiarow dla danej instancji do pliku z pomiarami 
        //cout<<"Srednia: "<<policz_srednia(wsk_na_pomiary, liczba_pomiarow)<<endl;
        zapisanie_pomiarow_instancji(nazwa_pliku_z_czasami, instancje[i], wsk_na_pomiary, liczba_pomiarow, policz_srednia(wsk_na_pomiary,liczba_pomiarow));

        // zwolnienie miejsca w pamieci tablicy zawierajacej pomiary
        delete[] wsk_na_pomiary;
    }


    //koniec programu
    return 0;
}





void inicjalizacja(string nazwa_ini)
{
    // otworzenie i wczytanie instrukcji z pliku .ini
    fstream plik;
    plik.open(nazwa_ini, ios::in);
    if(plik.good() == true)
    {
        plik>>nazwa_pliku_wejsciowego;
        for (int i = 0; i < 17; i++)
        {
            plik>>instancje[i];
        }
        plik>>liczba_pomiarow;
        plik>>jakie_sortowanie;
        plik>>nazwa_pliku_wyjciowego;
        plik>>nazwa_pliku_z_czasami;
    }
    else
    {
        cout<<"Blad inicjalizacji"<<endl;
        exit(-1);
    }
    // zamkniecie pliku
    plik.close();
}

void sprawdzenie_inicjalizacji()
{
    cout<<nazwa_pliku_wejsciowego<<endl;
    for (int i = 0; i < 17; i++)
    {
        cout<<instancje[i]<<endl;
    }
    cout<<liczba_pomiarow<<endl;
    cout<<jakie_sortowanie<<endl;
    cout<<nazwa_pliku_wyjciowego<<endl;
    cout<<nazwa_pliku_z_czasami<<endl;
}

void wczytanie_danych(int* wsk, int ilosc_wczytywanych_liczb, string nazwa_pliku_z_danymi)
{
    ifstream plik;
    plik.open(nazwa_pliku_z_danymi, ios::in);
    if(plik.good() == true)
    {
        for(int i=0; i<ilosc_wczytywanych_liczb; i++)
        {
            string bufor;
            int konwersja;
            getline(plik, bufor, ',');
            konwersja=stoi(bufor);
            wsk[i]=konwersja; // konwersja string do int
        }
    }
    else
    {
        cout<<"Blad przy wczytywaniu pliku"<<endl;
        exit(-1);
    }
    plik.close();
}
void sprawdzenie_tablicy(int* wsk, int ilosc_wczytywanych_liczb)
{
    for (int i = 0; i < ilosc_wczytywanych_liczb; i++)
    {
        cout<<i+1<<".\t"<<wsk[i]<<endl;
    }
    
}

void zapisz_posortowane(int* wsk, int ile_elementow_w_tablicy, string nazwa_pliku)
{
    fstream plik;
    plik.open(nazwa_pliku, ios::out);
    if(plik.good()==true)
    {
        for(int i=0; i<ile_elementow_w_tablicy; i++)
        {
            plik<<wsk[i]<<", ";
        }
    }
    else
    {
        cout<<"Blad przy zapisie posortowanych liczb"<<endl;
    }
    plik.close();
}

void utworzenie_pliku_z_pomiarami(string nazwa_pliku_z_pomiarami, int liczba_prob)
{
    // utworzenie nazwy pliku
    switch (jakie_sortowanie)
    {
    case 1:
        nazwa_pliku_z_pomiarami += "_przez_zliczanie";
        break;
    case 2:
        nazwa_pliku_z_pomiarami += "_przez_kopcenie";
        break;
    default:
        cout<<"Blednie wybrane sortowanie"<<endl;
        exit(-1);
        break;
        }
    nazwa_pliku_z_pomiarami+=".csv";

    // utworzenie pliku
    ofstream plik;
    plik.open(nazwa_pliku_z_pomiarami);
    if(plik.good()==true)
    {
        // utworzenie tabeli
        plik<<"liczba instancji"<<",";
        // kolejne
        for (int i = 0; i < liczba_prob; i++)
        {
            plik<<i+1<<" pomiar,";
        }
        
        plik<<"srednia"<<endl;
    }
    else
    {
        cout<<"Blad przy utworzenie pliku zawierajacego pomiary"<<endl;
    }
    plik.close();
}

long double policz_srednia(unsigned long long int* wsk, int ilosc_elementow_w_tablicy)
{
    long double suma=0;
    for(int i=0; i<ilosc_elementow_w_tablicy; i++)
    {
        suma+=wsk[i];
    }
    long double srednia = suma/ilosc_elementow_w_tablicy;
    return srednia;
}


void zapisanie_pomiarow_instancji(string nazwa_pliku_z_pomiarami, int liczba_instancji, unsigned long long int* wsk_na_czas_pomiaru, int liczba_prob, long double srednia)
{
    // znalezienie nazwy pliku
    switch (jakie_sortowanie)
    {
    case 1:
        nazwa_pliku_z_pomiarami += "_przez_zliczanie";
        break;
    case 2:
        nazwa_pliku_z_pomiarami += "_przez_kopcenie";
        break;
    default:
        cout<<"Blednie wybrane sortowanie"<<endl;
        exit(-1);
        break;
        }
    nazwa_pliku_z_pomiarami+=".csv";

    // dodanie pomiarow do pliku
    fstream plik;
    plik.open(nazwa_pliku_z_pomiarami, ios::out|ios::app);
    if(plik.good()==true)
    {
        plik<<liczba_instancji<<",";
        for (int i = 0; i < liczba_prob; i++)
        {
            plik<<wsk_na_czas_pomiaru[i]<<",";
        }
        plik<<srednia<<endl;
    }
    else
    {
        cout<<"Wystapil problem z zapisem pomiarow"<<endl;
        exit(-1);
    }
    plik.close();
}

// sekcja sortowań
void sort_przez_zliczanie()
{

}

void sort_przez_kopcenie()
{

}