#include<iostream>
#include<cstring>
#include<fstream>
#include<string>
#include<chrono>

using namespace std;

// sekcja funkcyjna
void inicjalizacja(string nazwa_ini);
void sprawdzenie_inicjalizacji();
void utworzenie_pliku_z_czasami(string nazwa_pliku);
void wczytanie_danych(int* wsk, int rozmiar_macierzy, string nazwa_pliku_z_danymi);
void wczytanie_danych_final(int* wsk, int rozmiar_macierzy, string nazwa_pliku_z_danymi);
void sprawdzenie_tablicy(int* wsk, int ilosc_wczytywanych_liczb);
void konwersja_z_1D_do_2D(int* wsk, int** tab, int ilosc_liczb);
void sprawdzenie_2D(int** tab, int ilosc_liczb);
void zapis_pomiarow(string nazwa_pliku, unsigned long long int* tab_pomiarow, int liczba_pomiarow, int jaki_rozmiar);
void referencja();

// sekcja zmiennych globalnych
int rozmiary[13];
int liczba_pomiarow;
int rozmiar_referencji;
string nazwa_pliku_z_czasami;
string nazwa_pliku_referyncyjnego;
string nazwa_pliku_z_liczbami;


int minKey(int* key, bool* mstSet, int V){
    int min = INT_MAX, min_index;
 
    for (int v = 0; v < V; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;
 
    return min_index;
}

void printMST(int* parent, int** graph, int V){
    cout<<"Edge \tWeight\n";
    for (int i = 1; i < V; i++)
        cout<<parent[i]<<" - "<<i<<" \t"<<graph[i][parent[i]]<<" \n";
}

void primMST(int** graph, int V){
    int* parent = new int[V];
    int* key = new int[V];
    bool* mstSet = new bool[V];
    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;
    key[0] = 0;
    parent[0] = -1; 
    for (int count = 0; count < V - 1; count++)
    {
        int u = minKey(key, mstSet, V);
        mstSet[u] = true;
        for (int v = 0; v < V; v++)
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }
    printMST(parent, graph, V);
    delete[] mstSet;
    delete[] key;
    delete[] parent;
}

void primMST_nopreview(int** graph, int V)
{
    int* parent = new int[V];
    int* key = new int[V];
    bool* mstSet = new bool[V];
    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;
    key[0] = 0;
    parent[0] = -1; 

    for (int count = 0; count < V - 1; count++)
    {
        int u = minKey(key, mstSet, V);
        mstSet[u] = true;
        for (int v = 0; v < V; v++)
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }
 
    delete[] mstSet;
    delete[] key;
    delete[] parent;
}


// =================================== FUNKCJA MAIN ===================================
int main(){
    inicjalizacja("inicjalizacja.ini");
    cout<<"Macierz referencyjna:"<<endl;
    referencja();
    cout<<"\nRozpoczecie pomiarow czasow dla macierzy o wprowadzonych rozmiarach\n"<<endl;
    for (int i = 0; i < 13; i++){
        unsigned long long int* pomiary_czasow = new unsigned long long int[liczba_pomiarow];
        cout<<"Drzewo MST dla rozmiaru: "<<rozmiary[i]<<endl;
        for (int k = 0; k < liczba_pomiarow; k++){
            // Utworzenie dynamicznego wektora oraz tablic
            int* wsk = new int[rozmiary[i]*rozmiary[i]];
            int** tablica = new int*[rozmiary[i]];
            for (int j = 0; j < rozmiary[i]; j++)
            {
                tablica[j] = new int[rozmiary[i]];
            }
            // wybranie odpowiedniego wczytania danych
            if (i == 12){
                wczytanie_danych_final(wsk, rozmiary[i], nazwa_pliku_z_liczbami);
            }
            else{
                wczytanie_danych(wsk, rozmiary[i], nazwa_pliku_z_liczbami);
            }
            
            konwersja_z_1D_do_2D(wsk, tablica, rozmiary[i]);

            // rozpoczecie pomiaru czasu sortowania
            chrono::steady_clock::time_point begin = chrono::steady_clock::now();
            primMST_nopreview(tablica, rozmiary[i]);
            // zakonczenie pomiaru czasu sortowania
            chrono::steady_clock::time_point end = chrono::steady_clock::now();
            unsigned long long int time_dif = chrono::duration_cast<chrono::microseconds>(end-begin).count();
            pomiary_czasow[k]=time_dif;

            // usunięcie zalokowanej pamięci
            delete[] wsk;
            for(int j=0; j < rozmiary[i]; j++){
                delete[] tablica[j];
            }
            delete[] tablica;
        }
        zapis_pomiarow(nazwa_pliku_z_czasami, pomiary_czasow, liczba_pomiarow, i);
        delete[] pomiary_czasow;
    }

    return 0;
}
// =================================== KONIEC FUNKCJI MAIN ===================================

void inicjalizacja(string nazwa_ini){
    fstream plik;
    plik.open(nazwa_ini, ios::in);
    if(plik.good() == true){
        plik>>nazwa_pliku_z_liczbami;
        for (int i = 0; i < 13; i++)
        {
            plik>>rozmiary[i];
        }
        plik>>liczba_pomiarow;
        plik>>nazwa_pliku_referyncyjnego;
        plik>>rozmiar_referencji;
        plik>>nazwa_pliku_z_czasami;
    }
    else{
        cout<<"Blad inicjalizacji"<<endl;
        exit(-1);
    }
    //zamknięcie pliku
    plik.close();
    utworzenie_pliku_z_czasami(nazwa_pliku_z_czasami);
}


void sprawdzenie_inicjalizacji(){
    cout<<nazwa_pliku_z_liczbami<<endl;
    cout<<nazwa_pliku_z_czasami<<endl;
    cout<<nazwa_pliku_referyncyjnego<<endl;
    for (int i = 0; i < 13; i++)
    {
        cout<<rozmiary[i]<<"\t";
    }
}


void utworzenie_pliku_z_czasami(string nazwa_pliku){
    // utworzenie pliku
    nazwa_pliku+=".csv";
    ofstream plik;
    plik.open(nazwa_pliku);
    if(plik.good() == true){
        plik<<"Rozmiary macierzy";
        for(int i; i<liczba_pomiarow; i++){
            plik<<"; pomiar nr "<<i+1;
        }
        // zdefiniowanie drugiego wiersza
        plik<<"; srednia czasow"<<endl;
    }
    plik.close();
}

void wczytanie_danych(int* wsk, int rozmiar_macierzy, string nazwa_pliku_z_danymi){
    ifstream plik;
    plik.open(nazwa_pliku_z_danymi, ios::in);
    int miejsce_w_tablicy=0;
    if(plik.good() == true)
    {
        for(int i=0; i<rozmiar_macierzy; i++)
        {
            for (int j = 0; j < rozmiar_macierzy; j++)
            {
                string bufor;
                int konwersja;
                getline(plik, bufor, ',');
                konwersja=stoi(bufor);
                wsk[miejsce_w_tablicy]=konwersja; // konwersja string do int   
                ++miejsce_w_tablicy;
            }
            string skip;
            getline(plik, skip);
        }
    }
    else
    {
        cout<<"Blad przy wczytywaniu pliku"<<endl;
        exit(-1);
    }
    plik.close();
}

void wczytanie_danych_final(int* wsk, int rozmiar_macierzy, string nazwa_pliku_z_danymi){
    ifstream plik;
    plik.open(nazwa_pliku_z_danymi, ios::in);
    int miejsce_w_tablicy=0;
    if(plik.good() == true)
    {
        for(int i=0; i<rozmiar_macierzy; i++)
        {
            for (int j = 0; j < rozmiar_macierzy; j++)
            {
                string bufor;
                int konwersja;
                if (j == rozmiar_macierzy-1)
                {
                    getline(plik,bufor,'\n');
                    konwersja=stoi(bufor);
                    wsk[miejsce_w_tablicy]=konwersja;   
                }
                else
                {
                    getline(plik, bufor, ',');
                    konwersja=stoi(bufor);
                    wsk[miejsce_w_tablicy]=konwersja; // konwersja string do int   
                }
                ++miejsce_w_tablicy;
            }
        }
    }
    else
    {
        cout<<"Blad przy wczytywaniu pliku"<<endl;
        exit(-1);
    }
    plik.close();    
}



void sprawdzenie_tablicy(int* wsk, int ilosc_wczytywanych_liczb){
    for (int i = 0; i < ilosc_wczytywanych_liczb; i++)
    {
        cout<<i+1<<".\t"<<wsk[i]<<endl;
    }
    
}

void konwersja_z_1D_do_2D(int* wsk, int** tab, int ilosc_liczb){
    int kopiowalnik = 0;
    for (int i = 0; i < ilosc_liczb; i++)
    {
        for (int j = 0; j < ilosc_liczb; j++)
        {
            tab[i][j] = wsk[kopiowalnik];
            kopiowalnik++;
        }
    }
}
void sprawdzenie_2D(int** tab, int ilosc_liczb){
    for (int i = 0; i < ilosc_liczb; i++)
    {
        for (int j = 0; j < ilosc_liczb; j++)
        {
            cout<<tab[i][j]<<"\t";
        }
        cout<<endl;
    }
}


void referencja(){
    int* ptr = new int[rozmiar_referencji*rozmiar_referencji];
    wczytanie_danych_final(ptr, rozmiar_referencji, nazwa_pliku_referyncyjnego);
    int** tablica = new int*[rozmiar_referencji];
    for (int j = 0; j < rozmiar_referencji; j++)
    {
        tablica[j] = new int[rozmiar_referencji];
    }
    konwersja_z_1D_do_2D(ptr, tablica, rozmiar_referencji);
    sprawdzenie_2D(tablica, rozmiar_referencji);
    
    primMST(tablica, rozmiar_referencji);
    for(int j=0; j < rozmiar_referencji; j++){
        delete[] tablica[j];
    }
    delete[] tablica;
    delete[] ptr;
}

void zapis_pomiarow(string nazwa_pliku, unsigned long long int* tab_pomiarow, int liczba_pomiarow, int jaki_rozmiar){
    fstream plik;
    nazwa_pliku+=".csv";
    plik.open(nazwa_pliku, ios::out|ios::app);
    long double srednia=0;
    if(plik.good() == true){
        plik<<rozmiary[jaki_rozmiar];
        for (int j = 0; j < liczba_pomiarow; j++)
        {
            plik<<';'<<tab_pomiarow[j];
            srednia+=tab_pomiarow[j];
        }
        plik<<';'<<srednia/liczba_pomiarow<<endl;
    }
    else{
        cout<<"Blad przy zapisywaniu pomiarow"<<endl;
        exit(-1);
    }
}
