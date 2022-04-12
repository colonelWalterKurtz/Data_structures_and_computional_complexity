#include<iostream>
#include<cstring>
#include<fstream>
#include<string>
#include<chrono>

using namespace std;

#define INF 9999999

// sekcja funkcyjna
void inicjalizacja(string nazwa_ini);
void sprawdzenie_inicjalizacji();
void utworzenie_pliku_z_czasami(string nazwa_pliku);
void wczytanie_danych(int* wsk, int ilosc_wczytywanych_liczb, string nazwa_pliku_z_danymi);
void sprawdzenie_tablicy(int* wsk, int ilosc_wczytywanych_liczb);
void konwersja_z_1D_do_2D(int* wsk, int** tab, int ilosc_liczb);
void sprawdzenie_2D(int** tab, int ilosc_liczb);

void referencja();

int minKey(int* key, bool* mstSet, int V){
    // Initialize min value
    int min = INT_MAX, min_index;
 
    for (int v = 0; v < V; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;
 
    return min_index;
}

void printMST(int* parent, int** graph, int V)
{
    cout<<"Edge \tWeight\n";
    for (int i = 1; i < V; i++)
        cout<<parent[i]<<" - "<<i<<" \t"<<graph[i][parent[i]]<<" \n";
}

void primMST(int** graph, int V)
{
    // Array to store constructed MST
    int* parent = new int[V];
    // Key values used to pick minimum weight edge in cut
    int* key = new int[V];
    // To represent set of vertices included in MST
    bool* mstSet = new bool[V];
 
    // Initialize all keys as INFINITE
    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;
 
    // Always include first 1st vertex in MST.
    // Make key 0 so that this vertex is picked as first vertex.
    key[0] = 0;
    parent[0] = -1; // First node is always root of MST
 
    // The MST will have V vertices
    for (int count = 0; count < V - 1; count++)
    {
        // Pick the minimum key vertex from the
        // set of vertices not yet included in MST
        int u = minKey(key, mstSet, V);
 
        // Add the picked vertex to the MST Set
        mstSet[u] = true;
 
        // Update key value and parent index of
        // the adjacent vertices of the picked vertex.
        // Consider only those vertices which are not
        // yet included in MST
        for (int v = 0; v < V; v++)
 
            // graph[u][v] is non zero only for adjacent vertices of m
            // mstSet[v] is false for vertices not yet included in MST
            // Update the key only if graph[u][v] is smaller than key[v]
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }
 
    // print the constructed MST
    printMST(parent, graph, V);
    delete[] mstSet;
    delete[] key;
    delete[] parent;
}

void primMST_nopreview(int** graph, int V)
{
    // Array to store constructed MST
    int* parent = new int[V];
    // Key values used to pick minimum weight edge in cut
    int* key = new int[V];
    // To represent set of vertices included in MST
    bool* mstSet = new bool[V];
 
    // Initialize all keys as INFINITE
    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;
 
    // Always include first 1st vertex in MST.
    // Make key 0 so that this vertex is picked as first vertex.
    key[0] = 0;
    parent[0] = -1; // First node is always root of MST
 
    // The MST will have V vertices
    for (int count = 0; count < V - 1; count++)
    {
        // Pick the minimum key vertex from the
        // set of vertices not yet included in MST
        int u = minKey(key, mstSet, V);
 
        // Add the picked vertex to the MST Set
        mstSet[u] = true;
 
        // Update key value and parent index of
        // the adjacent vertices of the picked vertex.
        // Consider only those vertices which are not
        // yet included in MST
        for (int v = 0; v < V; v++)
 
            // graph[u][v] is non zero only for adjacent vertices of m
            // mstSet[v] is false for vertices not yet included in MST
            // Update the key only if graph[u][v] is smaller than key[v]
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }
 
    delete[] mstSet;
    delete[] key;
    delete[] parent;
}
// sekcja zmiennych globalnych
int rozmiary[13];
int rozmiar_referencji;
string nazwa_pliku_z_czasami;
string nazwa_pliku_referyncyjnego;
string nazwa_pliku_z_liczbami;


// =================================== FUNKCJA MAIN ===================================
int main(){
    inicjalizacja("inicjalizacja.ini");

    referencja();
    
    for (int i = 0; i < 12; i++){
        // Utworzenie dynamicznego wektora oraz tablic
        int* wsk = new int[rozmiary[i]*rozmiary[i]];
        int** tablica = new int*[rozmiary[i]];
        for (int j = 0; j < rozmiary[i]; j++)
        {
            tablica[j] = new int[rozmiary[i]];
        }

        wczytanie_danych(wsk, rozmiary[i]*rozmiary[i], nazwa_pliku_z_liczbami);
        //sprawdzenie_tablicy(wsk, rozmiary[i]*rozmiary[i]);
        konwersja_z_1D_do_2D(wsk, tablica, rozmiary[i]);
        //sprawdzenie_2D(tablica, rozmiary[i]);

        cout<<"Drzeewo MST dla rozmiaru: "<<rozmiary[i]<<endl;
        primMST_nopreview(tablica, rozmiary[i]);

        // usunięcie zalokowanej pamięci
        delete[] wsk;
        for(int j=0; j < rozmiary[i]; j++){
            delete[] tablica[j];
        }
        delete[] tablica;
    }
    

    return 0;
}


void inicjalizacja(string nazwa_ini){
    fstream plik;
    plik.open(nazwa_ini, ios::in);
    if(plik.good() == true){
        plik>>nazwa_pliku_z_liczbami;
        for (int i = 0; i < 13; i++)
        {
            plik>>rozmiary[i];
        }
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
        plik<<"Rozmiary macierzy;";
        for(int i; i<13; i++){
            plik<<rozmiary[i]<<';';
        }
        // zdefiniowanie drugiego wiersza
        plik<<endl<<"czas pomiaru [us];";
    }
    plik.close();
}

void wczytanie_danych(int* wsk, int ilosc_wczytywanych_liczb, string nazwa_pliku_z_danymi){
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
    wczytanie_danych(ptr, rozmiar_referencji*rozmiar_referencji, nazwa_pliku_referyncyjnego);
    //sprawdzenie_tablicy(ptr, rozmiar_referencji*rozmiar_referencji);
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