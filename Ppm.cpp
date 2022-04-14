#include "Ppm.h"

Ppm::Ppm() : Obraz()
{
 //konstuktor klasy Obraz sam wszystko zrobi
}

Ppm::Ppm(const Ppm& P2) : Obraz(P2)
{
    //konstruktor klasy bazowej wszystko zrobi
}

Ppm::~Ppm()
{
    //nie ma co robić
}

//operator '=' jako jedyny operator nie jest dziedziczony
Ppm& Ppm::operator=(Ppm& P2)
{
    if (this == &P2)
    {
        return *this;
    }

    //operator nie jest dziedziczony więc trzeba tu wpisać te wszystki zmienne z klasy 'Obraz'
    this->pxtab = P2.return_table();
    this->set_size(P2.get_szerokosc(), P2.get_wysokosc());
    this->set_load_completness(P2.check_whether_loaded());
    this->tytul = P2.get_tytul();
    this->set_dobryplik(P2.get_dobryplik());

    return *this;
}

//musi tu mieć swoją definicję bo inaczej klasa stanie się abstrakcyjna
void Ppm::loadFromFile(std::string nazwaPliku)
{
    set_tytul(nazwaPliku);
    obrazek.open(get_tytul()); //otwiera plik obrazka z którego odczytamy piksele

    if (obrazek.good())
    {
        set_dobryplik(true); //stwierdziliśmy, że poprawnie otworzyliśmy plik obrazka
        //powstanie bezkomentarzowy plik i uzyskamy jego nazwę
        std::string tymczasowy = bez_komentarzy("ppm", "ppm"); //"ppm_without_comments.ppm"
        obrazek.close(); //zamykamy plik obrazka (piksele mamy już w pliku bezkomentarzowym)
        //wpisuje listę pikseli do tabeli na podstawie bezkomentarzowego pliku
        wpiszdotablicy(tymczasowy);
    }
    else
    {
        set_dobryplik(false); //plik nie istniał i/lub nie udało się go otworzyć
    }

    return;
}

void Ppm::saveToFile(std::string nazwaPliku)
{
    //nie ma sensu zapisywać do pliku, jeśli nic nie odczytaliśmy (bo nie było skąd)
    if (get_dobryplik())
    {
        std::string tytul_celu = nazwaPliku + ".ppm"; //nazwa będzie podawana bez podania rozszerzenia
        std::ofstream cel; //by można zapisywać do pliku
        int a = 0, b = 0, nr_px = -1; //potrzebne do pętli
        int wysk = get_wysokosc(); //wysokość tworzonego obrazka
        int szer = get_szerokosc(); //szerokość tworzonego obrazka

        if (szer * wysk == pxtab.size()) //czy mamy wystarczająco dużo pikseli?
        {
            cel.open(tytul_celu); //'otwarcie' pliku stworzy/nadpisze go
            cel << "P3" << std::endl; //pierwsza linijka to oznaczenie formatu (tu: PPM w ASCII)
            cel << szer << " " << wysk << std::endl; //druga linijka to 2 liczby oznaczające rozmiar
            cel << "255" << std::endl; //trzecia linijka to liczba z maksymalnym nasyceniem koloru

            //czas wpisywać piksele
            for (a = 0; a < wysk; a++)
            {
                for (b = 0; b < szer; b++)
                {
                    nr_px++; //każdy kolejny piksel to kolejna komórka/wers w tablicy pikseli
                    cel << pxtab[nr_px].R << " ";
                    cel << pxtab[nr_px].G << " ";
                    cel << pxtab[nr_px].B << " ";
                }
                cel << std::endl; //każda linia w pliku to jeden wiersz obrazu
            }
            cel.close(); //po skończonym zapisywaniu zamykamy plik
        } //koniec 'if' dla dobrej ilości pikseli
    } //koniec 'if' dla poprawnie otwartego pliku źródłowego

    return;
}

//ma załadować listę pikseli z obiektu klasy pochodnej wskazany przez wskaźnik do klasy abstrakcyjnej (bazowej)
void Ppm::load(Obraz* obraz)
{
    int a;
    long int ilosc;
    KolorRGB bialoczarny;
    szerokosc = obraz->get_szerokosc();
    wysokosc = obraz->get_wysokosc();
    ilosc = wysokosc * szerokosc;
    pxtab.clear();
    for (a = 0; a < ilosc; a++)
    {
        //przepisujemu wartosci
        bialoczarny.R = obraz->value_from_table(a, 'R');
        bialoczarny.G = obraz->value_from_table(a, 'G');
        bialoczarny.B = obraz->value_from_table(a, 'B');
        pxtab.push_back(bialoczarny);
    }
    set_dobryplik(true); //mieliśmy skąd zczytać piksele
    return;
}

//zapełni listę pikseli
void Ppm::wpiszdotablicy(std::string noncomment)
{    
    KolorRGB tenpiksel{0, 0, 0}; //informacja o pojedyńczym pikselu: R, G, B
    int wys = 0, szer = 0; //tymczasowe zmienne na rozmiar
    std::string linijka; //pomocniczy string

    std::ifstream abcd;
    abcd.open(noncomment); //otworzyliśmy plik bezkomentarzowy
    std::getline(abcd, linijka); //pierwsza linijka jest nam po nic, bo to format
    //potem odczytuje rozmiar
    abcd >> szer;
    abcd >> wys;
    set_size(szer, wys); //ustawienie rozmiaru
    //potem odczytuje maksymalną wartość nasycenia koloru (zbędne)
    abcd >> linijka;

    //przed stworzeniem listy pikseli musimy mieć pustą listę
    if (pxtab.size() > 0)
    {
        pxtab.clear();
    }

    //odczytywanie pikseli z pliku obrazka
    while (!abcd.eof())
    {
        abcd >> tenpiksel.R;
        abcd >> tenpiksel.G;
        abcd >> tenpiksel.B;
        pxtab.push_back(tenpiksel);
    }
    abcd.close(); //po skończonym odczytywaniu zamykamy plik bezkomentarzowy
    pxtab.pop_back(); //ostatni piksel wpisał się 2 razy
   
    set_load_completness(true);
    //string i vector mają destruktory
    return;
}