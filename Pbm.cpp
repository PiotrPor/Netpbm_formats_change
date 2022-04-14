#include "Pbm.h"


Pbm::Pbm() : Obraz()
{
    //nie ma co robić
}

Pbm::Pbm(const Pbm& P2) : Obraz(P2)
{
    //tamten konstruktor wszystko zrobi
}

Pbm::~Pbm()
{
    //string ma swój destruktor
}

//klasa pochodna nie dziedziczy operatora '='
Pbm& Pbm::operator=(Pbm& P2)
{
    if (this == &P2)
    {
        return *this;
    }

    //tu zmienne trzeba tu wspomnieć, bo operator nie jest dziedziczony 
    this->pxtab = P2.return_table();
    this->set_size(P2.get_szerokosc(), P2.get_wysokosc());
    this->set_load_completness(P2.check_whether_loaded());
    this->tytul = P2.get_tytul();
    this->set_dobryplik(P2.get_dobryplik());

    return *this;
}

//musi tu mieć swoją definicję bo inaczej klasa stanie się abstrakcyjna
void Pbm::loadFromFile(std::string nazwaPliku)
{
    set_tytul(nazwaPliku);
    obrazek.open(get_tytul()); //otwiera plik obrazu do przeanalizowania

    if (obrazek.good())
    {
        set_dobryplik(true); //udało się otworzyć plik obrazka
        //stworzy plik bezkomentarzowy, uzyskamy nazwę tego pliku
        std::string temp_title = bez_komentarzy("empty", "pbm"); //"empty_without_comments.pbm"
        obrazek.close(); //po skończonej pracy zamknie plik obrazka
        //stworzymy liste pikseli na podstawie pliku bez komentarzy
        wpiszdotablicy(temp_title);
    }
    else
    {
        set_dobryplik(false); //niech będzie wiadome, że nie otworzyliśmy i odczytaliśmy pliku
    }

    return;
}

void Pbm::saveToFile(std::string nazwaPliku)
{
    if (get_dobryplik())
    {
        std::string tytul_celu = nazwaPliku + ".pbm"; //nazwa będzie podawana bez podania rozszerzenia
        std::ofstream cel;
        int a = 0, b = 0, nr_px = -1; //potrzebne do pętli
        long int srednia;
        int wysk = get_wysokosc(); //rozmiary tworzonego obrazka
        int szer = get_szerokosc();

        if (wysk * szer == pxtab.size()) //czy mamy wystarczająco dużo pikseli?
        {
            cel.open(tytul_celu); //otwarcie pliku
            cel << "P1" << std::endl; //w pierwszej linijce jest oznaczenie formatu
            cel << szer << " " << wysk << std::endl; //w drugiej linijce jest szerokość i wysokość obrazu
            //czas wpisywać piksele
            for (a = 0; a < wysk; a++)
            {
                for (b = 0; b < szer; b++)
                {
                    nr_px++; //kolejny piksel z listy
                    srednia = 0;
                    srednia += pxtab[nr_px].R;
                    srednia += pxtab[nr_px].G;
                    srednia += pxtab[nr_px].B;
                    srednia /= 3;
                    if (srednia < 128)
                    {cel << "0 ";}
                    else
                    {cel << "1 ";}
                }
                cel << std::endl; //jedna linijka w pliku to jeden wiersz obrazu
            }
            cel.close(); //na koniec zamykamy plik
        }
    }

    return;
}

void Pbm::load(Obraz* obraz)
{
    int a;
    long int srednia, ilosc;
    KolorRGB bialoczarny;
    szerokosc = obraz->get_szerokosc();
    wysokosc = obraz->get_wysokosc();
    ilosc = wysokosc * szerokosc;
    pxtab.clear();
    for (a = 0; a < ilosc; a++)
    {
        srednia = 0;
        srednia += obraz->value_from_table(a, 'R');
        srednia += obraz->value_from_table(a, 'G');
        srednia += obraz->value_from_table(a, 'B');
        srednia = srednia/3;
        //srednia = (pxtab[a].R + pxtab[a].G + pxtab[a].B)/3;
        if (srednia > 127)
        {
            //czarny
            bialoczarny.R = 0;
            bialoczarny.G = 0;
            bialoczarny.B = 0;
        }
        else
        {
            //bialy
            bialoczarny.R = 255;
            bialoczarny.G = 255;
            bialoczarny.B = 255;
        }
        pxtab.push_back(bialoczarny);
    }
    set_dobryplik(true); //mieliśmy skąd zczytać piksele
    return;
}

//wypełnia listę pikseli
void Pbm::wpiszdotablicy(std::string tt)
{
    KolorRGB tenpiksel{0, 0, 0}; //do listy pikseli będziemy wrzucać opisy całych pikseli
    //informacja o pikselu: wartość
    int wys = 0, szer = 0; //tymczasowo na rozmiar
    int wartosc; //pomocnicze
    std::string linijka; //pomocniczy string

    //przed wczytywaniem trzeba opróżnić listę pikseli
    if (pxtab.size() > 0)
    {
        pxtab.clear();
    }

    std::ifstream abcd;
    abcd.open(tt); //otwieramy plik bezkomentarzowy
    std::getline(abcd, linijka); //pierwsza linijka to format (pomijamy)
    //Odczytamy rozmiar obrazka z następnej linijki
    abcd >> szer;
    abcd >> wys;
    set_size(szer, wys);

    //po tej linijce dalej są już wypisane wartości dla pikseli
    //teraz będzie odczytywał piksele
    while (!obrazek.eof())
    {
        abcd >> wartosc;
        if (wartosc == 1)
        {
            //czarny
            tenpiksel.R = 0; //trzy liczby to jeden piksel
            tenpiksel.G = tenpiksel.R;
            tenpiksel.B = tenpiksel.R;
        }
        else
        {
            tenpiksel.R = 255; //trzy liczby to jeden piksel
            tenpiksel.G = tenpiksel.R;
            tenpiksel.B = tenpiksel.R;
        }
            
        
        pxtab.push_back(tenpiksel); //dodajemy do listy
    }//plik się skończył
    pxtab.pop_back(); //ostatni piksel wpisał się 2 razy

    abcd.close(); //zamykamy plik po skończonym wczytywaniu pikseli
    set_load_completness(true); //odczytaliśmy już listę pikseli (tu: z pliku)
    
    return;
}
