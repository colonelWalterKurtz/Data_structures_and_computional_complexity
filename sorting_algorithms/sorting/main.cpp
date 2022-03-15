#include <iostream>
#include <chrono>
#include <Windows.h>
#include <cstdio>
#include <fstream>
#include <typeinfo>

using namespace std;

void wczytaj_liczby(fstream& plik, string odwolanie_do_pliku, int ilosc_liczb, int* wskaznik_na_tablice);
void wyswietl_liczby(int* tablica, int rozmiar_tablicy);
void bubble_sort(int* tablica, int rozmiar_tablicy);
//void quick_sort(int* tablica, int rozmiar_tablicy);

int main()
{
    // zmienna pliku z liczbami
    fstream file;
    // nazwa pliku, z którego będą wczytywane liczby
    string nazwa_pliku = "liczby.txt";
    // inicjalizacja pliku tekstowego

    //przechowalnia wskaźników
    int* num_10 = new int[10];
    int* num_50 = new int[50];
    int* num_100 = new int[100];
    int* num_1k = new int[1000];
    int* num_2k = new int[2000];
    int* num_5k = new int[5000];
    int* num_10k, num_20k, num_50k, num_100k, num_200k, num_300k, num_500k, num_700k, num_900k, num_1M;


    int opcja = 0;
    int stop = 0;
    while (opcja!=7)
    {
        // pokazanie MENU
        system("CLS");
        cout << "-----------------------MENU----------------------------------" << endl;
        cout << "\t1. Wczytaj dane z pliku liczby.txt" << endl;
        cout << "\t2. Wykonaj sortowanie (od 10 liczb do 1 miliona" << endl;
        cout << "\t3. Wykonaj krotkie sortowanie (od 10 do 5 tysiecy)" << endl;
        cout << "\t4. Zapisz plik .csv z pomiarami" << endl;
        cout << "\t5. Zapisz plik .txt z posrtowanymi liczbami"<<endl;
        cout << "\t7. Zakoncz dzialanie programu" << endl;

        cout << "Wybor: ";
        cin >> opcja;
        switch (opcja)
        {
        case 1: // wczytanie danych
        {
            wczytaj_liczby(file, nazwa_pliku, 10, num_10);
            wczytaj_liczby(file, nazwa_pliku, 50, num_50);
            wczytaj_liczby(file, nazwa_pliku, 100, num_100);
            wczytaj_liczby(file, nazwa_pliku, 1000, num_1k);
            wczytaj_liczby(file, nazwa_pliku, 2000, num_2k);
            wczytaj_liczby(file, nazwa_pliku, 5000, num_5k);
            break;
        }
        case 3: // sortowanie tablic
        {
            int jakie_sortowanie = 0;
            cout << "\nJakie sortowanie?" << endl;
            cout << "1. bubble sort" << endl;
            cout << "2. quick sort" << endl;
            cout << "3. merge sort" << endl;
            cin >> jakie_sortowanie;
            switch (jakie_sortowanie)
            {
            default:
                break;
            case 1:
            {
                bubble_sort(num_10, 10);
                bubble_sort(num_50, 50);
                bubble_sort(num_100, 100);
                bubble_sort(num_1k, 1000);
                bubble_sort(num_2k, 2000);
                bubble_sort(num_5k, 5000);

            }
            }
            break;
        }
        case 6: // wyswietlanie tablic
        {
            cout << "10:" << endl;
            wyswietl_liczby(num_10, 10);
            cout << "50:" << endl;
            wyswietl_liczby(num_50, 50);
            cout << "100:" << endl;
            wyswietl_liczby(num_100, 100);
            cout << "1k:" << endl;
            wyswietl_liczby(num_1k, 1000);
            cout << "2k:" << endl;
            wyswietl_liczby(num_2k, 2000);
            cout << "5k:" << endl;
            wyswietl_liczby(num_5k, 5000);
            cin >> stop;
        }
        default:
            break;
        }


    }
    delete[] num_10, num_50, num_100, num_1k, num_2k, num_5k;
    return 0;
}


// sekcja funkcyjna
void wczytaj_liczby(fstream& plik, string odwolanie_do_pliku, int ilosc_liczb, int* wskaznik_na_tablice)
{
    int* arr = new int[ilosc_liczb];
    //otwarcie pliku tekstowego oraz sprawdzenie czy potok danych jest prawidłowy
    plik.open(odwolanie_do_pliku, ios::in);
    if (plik.good() == true)
    {
        for (int i = 0; i < ilosc_liczb; i++)
        {
            int bufor;
            plik >> bufor;
            //cout << bufor << endl;
            //cout << typeid(bufor).name() << endl;
            wskaznik_na_tablice[i] = bufor;
        }
    }
    else
    {
        cout << "Nie udało się poprawnie wczytac danych" << endl;
        exit(-1);
    }
    plik.close();
};

void wyswietl_liczby(int* tablica, int rozmiar_tablicy)
{
    for (int i = 0; i < rozmiar_tablicy; i++)
    {
        cout << tablica[i] << "\t" << endl;
        //cout << typeid(tablica[i]).name() << endl;
    }
    cout << "############################"<<endl;
}

void bubble_sort(int* tablica, int rozmiar_tablicy)
{
    for (int i = 0; i < rozmiar_tablicy; i++)
    {
        for (int j = 0; j < rozmiar_tablicy-1; j++)
        {
            if (tablica[j] > tablica[j + 1])
            {
                int bufor;
                bufor = tablica[j];
                tablica[j] = tablica[j + 1];
                tablica[j + 1] = bufor;
            }
        }
    }
}

//void quick_sort(int* tablica, int rozmiar_tablicy)
//{
//
//}