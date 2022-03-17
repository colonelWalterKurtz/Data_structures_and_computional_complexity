#include<iostream>
#include<fstream>
#include<typeinfo>
#include<chrono>


using namespace std;

// sekcja funkcyjna
void wczytaj_liczby(string nazwa_pliku, int ilosc_wczytywanych_liczb, int* zalokowana_tablica);
void pokaz_liczby(int ilosc_wczytanych_elementow_tablicy, int* tablica);

void bubble_sort(int ile_elementow_w_tablicy, int* tablica);
void quick_sort(int lewa_strona, int prawa_strona,  int* tablica);
void insertion_sort(int wielkosc_tablicy, int* tablica);

void zapisz_pomiary(string nazwa_pliku, int ilosc_liczb, int tabela_pomiarow[10]);
void zapisz_liczby(string nazwa_pliku, int ilosc_liczb, int* tablica);



int main()
{
    bool working=true;
    while (working)
    {
        system("CLS");
        cout<<"##########################\tMENU\t##########################"<<endl;
        cout<<"1. Wczytaj liczby i posortuj"<<endl;
        cout<<"2. Generuj wyniki"<<endl;
        cout<<"3. Koniec programu"<<endl;
        int wybor;
        cin>>wybor;
        string stop;
        switch (wybor)
        {
        case 1:
        {
            cout<<"Ile liczb chcesz wczytac?";
            int ilosc=10;
            cin>>ilosc;
            cout<<"*********************\tPodglad\t*********************"<<endl;
            // utworzenie dynamicznej tablicy przechowujacej wczytane liczby
            int* tablica=new int[ilosc];
            wczytaj_liczby("liczby.txt", ilosc, tablica);
            pokaz_liczby(ilosc, tablica);

            // wybor sortowania
            int jakie_sortowanie=0;
            cout<<"Wybierz sposob sortowania:"<<endl;
            cout<<"1. Bubble sort"<<endl;
            cout<<"2. Quick sort"<<endl;
            cout<<"3. Inseretion sort"<<endl;
            cin>>jakie_sortowanie;
            switch (jakie_sortowanie)
            {
            case 1:
            {
                bubble_sort(ilosc, tablica);
                break;
            }
            case 2:
            {
                quick_sort(0, ilosc, tablica);
                break;
            }
            case 3:
            {
                insertion_sort(ilosc, tablica);
                break;
            }
            default:
            {
                exit(-1);
            }
            }
            cout<<"*********************\tPodglad\t*********************"<<endl;
                pokaz_liczby(ilosc, tablica);
                zapisz_liczby("posortowane.txt", ilosc, tablica);
                cout<<"Wpisz cokolwiek, aby przejsc dalej:\t";
                cin>>stop;

            // usuniecie zalokowanej pamieci
            delete[] tablica; 

            break;
        }
        case 2:
        {
            // tablica z kolejną licznością elementów tablicy
            long int pomiary[17]={10, 50, 100, 500, 1000, 2000, 5000, 10000, 20000, 50000, 100000, 200000, 300000, 500000, 700000, 900000, 1000000};
            
            // inicjacja pliku przechowującego pomiary 
            string nazwa_pliku="short_pomiary.csv";
            ofstream file(nazwa_pliku);
            if (file.good()==true)
            {
                file<<"ilosc liczb";
                for(int i=0;i<10;i++)
                {
                    file<<','<<i+1;
                }
                file<<endl;
            }
            else
            {
                exit(-1);
            }
            file.close();

            // uruchomienie petli pomiarow
            int czasy[10];
            for(int s=0;s<8;s++)   //8,12
            {
                cout<<"Rozpoczeto pomiary czasu ilosci "<<pomiary[s]<<" liczb."<<endl;
                for (int i = 0; i < 10; i++)    //10
                {
                int* point=new int[pomiary[s]];
                wczytaj_liczby("liczby.txt", pomiary[s], point);
                // tutaj start time
                std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

                bubble_sort(pomiary[s], point);

                // tutaj koniec czasu
                std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
                //std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
                
                int time_dif=chrono::duration_cast<chrono::microseconds>(end-begin).count();
                
                // wpisanie czasu do tablicy
                czasy[i]=time_dif;

                delete[] point;
                    
                }
                zapisz_pomiary(nazwa_pliku, pomiary[s], czasy);
            }
            cout<<"Wpisz cokolwiek, aby przejsc dalej: ";
            cin>>stop;
            break;
        }
        case 3:
        {
            working=false;
            break;
        }
        default:
        {
            break;
        }
        }
    }
    
     
    system("CLS");
    return 0;
}

// definicje funkcji
void wczytaj_liczby(string nazwa_pliku, int ilosc_wczytywanych_liczb, int* zalokowana_tablica)
{
    // otworzenie pliku .txt z danymi
    fstream plik;
    plik.open(nazwa_pliku, ios::in);
    if(plik.good()==true)
    {
        // wczytanie danych do tablicy dynamicznej
        for (int i = 0; i < ilosc_wczytywanych_liczb; i++)
        {
            int bufor;
            plik>>bufor;
            zalokowana_tablica[i]=bufor;
        }
        
    }
    else
    {
        cout<<"Nie udalo sie prawidlowo wczytac pliku"<<endl;
    }
    plik.close();
}


void pokaz_liczby(int ilosc_wczytanych_elementow_tablicy, int* tablica)
{
    for (int i = 0; i < ilosc_wczytanych_elementow_tablicy; i++)
    {
        cout<<i+1<<".\t"<<tablica[i]<<endl;
    }
    cout<<"------------------------\tKONIEC\t------------------------"<<endl;
}

// algorytmy sortowania
void bubble_sort(int ile_elementow_w_tablicy, int* tablica)
{
    for (int i = 0; i < ile_elementow_w_tablicy; i++)
    {
        for (int j = 0; j < ile_elementow_w_tablicy-1; j++)
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

void quick_sort(int lewa_strona, int prawa_strona,  int* tablica)
{
    int i = lewa_strona;
    int j = prawa_strona;
    int x = tablica[( lewa_strona + prawa_strona ) / 2 ];
    do
    {
        while( tablica[ i ] < x )
             i++;
       
        while( tablica[ j ] > x )
             j--;
       
        if( i <= j )
        {
            swap( tablica[ i ], tablica[ j ] );
           
            i++;
            j--;
        }
    } while( i <= j );
   
    if( lewa_strona < j ) quick_sort(lewa_strona, j, tablica);
   
    if( prawa_strona > i ) quick_sort(i, prawa_strona, tablica);
   
}

void insertion_sort(int wielkosc_tablicy, int* tablica)
{
    int temp, j;
   
    for( int i = 1; i < wielkosc_tablicy; i++ )
    {
        temp = tablica[ i ];
       
        for( j = i - 1; j >= 0 && tablica[ j ] > temp; j-- )
             tablica[ j + 1 ] = tablica[ j ];
       
        tablica[ j + 1 ] = temp;
    }
}

void zapisz_pomiary(string nazwa_pliku, int ilosc_liczb, int tabela_pomiarow[10])
{
    fstream plik;
    plik.open(nazwa_pliku, ios::out|ios::app);
    if(plik.good()==true)
    {
        plik<<ilosc_liczb;
        for(int i=0;i<10;i++)
        {
            plik<<','<<tabela_pomiarow[i];
        }
        plik<<endl;
    }
    else
    {
        cout<<"Nie udalo sie zapisac danych"<<endl;
    }
    plik.close();
}

void zapisz_liczby(string nazwa_pliku, int ilosc_liczb, int* tablica)
{
    ofstream file(nazwa_pliku);
    if (file.good()==true)
    {
        for (int i = 0; i < ilosc_liczb; i++)
        {
            file<<tablica[i]<<", ";
        }
    }
    else
    {
        exit(-1);
    }
    file.close();  
}

