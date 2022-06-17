#include<iostream>
#include<cstring>
#include<fstream>
#include<string>
#include<chrono>
#include<limits.h>

using namespace std;

// sekcja funkcyjna
void inicjalizacja(string nazwa_ini);
void sprawdzenie_inicjalizacji();
void utworzenie_pliku_z_czasami(string nazwa_pliku_z_czasami);
void wczytanie_danych_finalne(int* wsk, int rozmiar_macierzy, string nazwa_pliku_z_danymi);
void wczytanie_danych(int* wsk, int rozmiar_macierzy, string nazwa_pliku_z_danymi);
void sprawdzenie_tablicy(int* wsk, int ilosc_wczytywanych_liczb);
void referencja_macierz(string nazwa_pliku, int rozmiar_referencji);
void sprawdzenie_tablicy(int* wsk, int ilosc_wczytywanych_liczb);
void konwersja_z_1D_do_2D(int* wsk, int** tab, int ilosc_liczb);
void sprawdzenie_2D(int** tab, int ilosc_liczb);
void zapis_pomiarow(string nazwa_pliku, unsigned  long int* tab_pomiarow, int liczba_pomiarow, int jaki_rozmiar);

// algorytm
int minDistance(int* dist, bool* sptSet, int V);
void printSolution(int* dist, int V);
void dijkstra(int** graph, int src, int V);
void dijkstraNoPreview(int** graph, int src, int V);

// sekcja zmiennych globalnych
string nazwa_pliku_z_macierz;
int instancje[13];
int liczba_pomiarow;
string nazwa_ref_macierz;
int rozmiar_ref_macierz;
string nazwa_pliku_z_pomiarami;

// ==================================== FUNKCJA MAIN ====================================

int main(){
    inicjalizacja("inicjalizacja.ini");
    //sprawdzenie_inicjalizacji();
    referencja_macierz(nazwa_ref_macierz, rozmiar_ref_macierz);

    cout<<"\nRozpoczecie pomiarow czasow dla macierzy o wprowadzonych rozmiarach\n"<<endl;
    for (int i = 0; i < 13; i++){
        unsigned  long int* pomiary_czasow = new unsigned  long int[liczba_pomiarow];
        cout<<"Dijsktra dla rozmiaru macierzy: "<<instancje[i]<<endl;
        for (int k = 0; k < liczba_pomiarow; k++){
            // Utworzenie dynamicznego wektora oraz tablic
            int* wsk = new int[instancje[i]*instancje[i]];
            int** tablica = new int*[instancje[i]];
            for (int j = 0; j < instancje[i]; j++)
            {
                tablica[j] = new int[instancje[i]];
            }
            // wybranie odpowiedniego wczytania danych
            if (i == 12){
                wczytanie_danych_finalne(wsk, instancje[i], nazwa_pliku_z_macierz);
            }
            else{
                wczytanie_danych(wsk, instancje[i], nazwa_pliku_z_macierz);
            }
            
            konwersja_z_1D_do_2D(wsk, tablica, instancje[i]);

            // rozpoczecie pomiaru czasu sortowania
            chrono::steady_clock::time_point begin = chrono::steady_clock::now();
            dijkstraNoPreview(tablica, 0, instancje[i]);
            // zakonczenie pomiaru czasu sortowania
            chrono::steady_clock::time_point end = chrono::steady_clock::now();
            unsigned long int time_dif = chrono::duration_cast<chrono::microseconds>(end-begin).count();
            pomiary_czasow[k]=time_dif;

            // usunięcie zalokowanej pamięci
            delete[] wsk;
            for(int j=0; j < instancje[i]; j++){
                delete[] tablica[j];
            }
            delete[] tablica;
        }
        zapis_pomiarow(nazwa_pliku_z_pomiarami+"_macierzy.csv", pomiary_czasow, liczba_pomiarow, instancje[i]);
        delete[] pomiary_czasow;
    }

    return 0;
}

// ==================================== KONIEC FUNKCJI MAIN ====================================

void inicjalizacja(string nazwa_ini){
    fstream plik;
    plik.open(nazwa_ini, ios::in);
    // wczytwanie danych z pliku inicjujacego
    if (plik.good() == true){
       plik>>nazwa_pliku_z_macierz;
        for (int i = 0; i < 13; i++){
            plik>>instancje[i];
        }
        plik>>liczba_pomiarow;
        plik>>nazwa_ref_macierz;
        plik>>rozmiar_ref_macierz;
        plik>>nazwa_pliku_z_pomiarami;
    }
    else{
        cout<<"Wystapil problem z wczytaniem danych z pliku inicjujacego"<<endl;
        exit(-1);        
    }
    plik.close();
    // utworzenie plikow przechowujacych pomiary czasow
    ofstream pomiary_macierzy;
    pomiary_macierzy.open(nazwa_pliku_z_pomiarami+"_macierzy.csv");
    if (pomiary_macierzy.good() == true){
        pomiary_macierzy<<"Liczebnosc instancji";
        for (int i = 0; i < liczba_pomiarow; i++){
            pomiary_macierzy<<"; "<<i+1<<" pomiar";
        }
        pomiary_macierzy<<"; srednia"<<endl;
    }
    else{
        cout<<"Wystapil problem przy tworzeniu pliku przechowujacego pomiary czasu wykonania dla macierzy"<<endl;
        exit(-1);
    }
    pomiary_macierzy.close();  
}

void sprawdzenie_inicjalizacji(){
    cout<<nazwa_pliku_z_macierz<<endl;
    for (int i = 0; i < 13; i++){
        cout<<instancje[i]<<endl;
    }
    cout<<liczba_pomiarow<<endl;
    cout<<nazwa_ref_macierz<<endl;
    cout<<rozmiar_ref_macierz<<endl;
    cout<<nazwa_pliku_z_pomiarami<<endl;
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

void wczytanie_danych_finalne(int* wsk, int rozmiar_macierzy, string nazwa_pliku_z_danymi){
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
    for (int i = 0; i < ilosc_wczytywanych_liczb*ilosc_wczytywanych_liczb; i++)
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

void referencja_macierz(string nazwa_pliku, int rozmiar_referencji){
    // zalokowanie dynamiczne pamięci
    int* ptr = new int[rozmiar_referencji*rozmiar_referencji];
    int** wsk = new int*[rozmiar_referencji];
    for(int i = 0; i < rozmiar_referencji; ++i){
        wsk[i] = new int[rozmiar_referencji];
    }
    wczytanie_danych_finalne(ptr,rozmiar_referencji,nazwa_ref_macierz);
    konwersja_z_1D_do_2D(ptr, wsk, rozmiar_referencji);
    cout<<"Wczytana macierz referencji:"<<endl;
    sprawdzenie_2D(wsk,rozmiar_referencji);
    dijkstra(wsk, 0, rozmiar_referencji);
    // zwolnienie zalokowanej pamięci
    delete[] ptr;
    for (int i = 0; i < rozmiar_referencji; i++){
    delete[] wsk[i];
    }
    delete[] wsk;
    cout<<endl;
}

void zapis_pomiarow(string nazwa_pliku, unsigned long int* tab_pomiarow, int liczba_pomiarow, int jaki_rozmiar){
    fstream plik;
    plik.open(nazwa_pliku, ios::out|ios::app);
    long double srednia=0;
    if(plik.good() == true){
        plik<<jaki_rozmiar;
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
// ################################### SEKCJA ALGORYTMU ###################################
// The program is for adjacency matrix representation of the graph
int minDistance(int* dist, bool* sptSet, int V)
{
   
    // Initialize min value
    int min = INT_MAX, min_index;
 
    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
 
    return min_index;
}
 
// A utility function to print the constructed distance array
void printSolution(int* dist, int V)
{
    cout <<"Wierzcholek \tOdleglosc od 0" << endl;
    for (int i = 0; i < V; i++)
        cout  << i << " \t\t"<<dist[i]<< endl;
}
 
// Function that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(int** graph, int src, int V)
{
    int* dist = new int[V]; // The output array.  dist[i] will hold the shortest
    // distance from src to i
 
    bool* sptSet = new bool[V]; // sptSet[i] will be true if vertex i is included in shortest
    // path tree or shortest distance from src to i is finalized
 
    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
 
    // Distance of source vertex from itself is always 0
    dist[src] = 0;
 
    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not
        // yet processed. u is always equal to src in the first iteration.
        int u = minDistance(dist, sptSet, V);
 
        // Mark the picked vertex as processed
        sptSet[u] = true;
 
        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < V; v++)
 
            // Update dist[v] only if is not in sptSet, there is an edge from
            // u to v, and total weight of path from src to  v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }
 
    // print the constructed distance array
    printSolution(dist, V);

    // free memory
    delete[] dist;
    delete[] sptSet;
}
 
 void dijkstraNoPreview(int** graph, int src, int V){
    int* dist = new int[V]; // The output array.  dist[i] will hold the shortest
    // distance from src to i
 
    bool* sptSet = new bool[V]; // sptSet[i] will be true if vertex i is included in shortest
    // path tree or shortest distance from src to i is finalized
 
    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
 
    // Distance of source vertex from itself is always 0
    dist[src] = 0;
 
    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not
        // yet processed. u is always equal to src in the first iteration.
        int u = minDistance(dist, sptSet, V);
 
        // Mark the picked vertex as processed
        sptSet[u] = true;
 
        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < V; v++)
 
            // Update dist[v] only if is not in sptSet, there is an edge from
            // u to v, and total weight of path from src to  v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    // free memory
    delete[] dist;
    delete[] sptSet;
 }