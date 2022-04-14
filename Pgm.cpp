#include "Pgm.h"


Pgm::Pgm() : Obraz()
{
    //kontruktor Obraz::Obraz() wszystko zrobi
}

Pgm::Pgm(const Pgm& P2) : Obraz(P2)
{
    //kontruktor klasy Obraz wszystko skopiuje
}

Pgm::~Pgm()
{
    //string ma własny destruktor
}

//klasy pochodne nie dziedziczą operatora '='
Pgm& Pgm::operator=(Pgm& P2)
{
    if (this == &P2)
    {
        return *this;
    }

    //trzeba napisać tu te zmienne, bo nie dziedziczy się operatora
    this->pxtab = P2.return_table();
    this->set_size(P2.get_szerokosc(), P2.get_wysokosc());
    this->set_load_completness(P2.check_whether_loaded());
    this->tytul = P2.get_tytul();
    this->set_dobryplik(P2.get_dobryplik());

    return *this;
}

//metoda musi tu mieć swoją definicję bo inaczej klasa stanie się abstrakcyjna
void Pgm::loadFromFile(std::string nazwaPliku)
{
    set_tytul(nazwaPliku);
    obrazek.open(get_tytul()); //otwiera plik obrazka

    if (obrazek.good())
    {
        set_dobryplik(true); //reszta metod klasy (i nie tylko) wie że udało się otworzyć plik
        //powstanie bezkomentarzowy plik i uzyskamy jego nazwę
        std::string tmp = bez_komentarzy("test", "pgm"); // "test_without_comments.pgm"
        obrazek.close(); //już nie potrzebujemy pliku obrazka, bo mamy plik  bezkomentarzowy
        //tworzymy liste pikseli na podstawie pliku bez komentarzy
        wpiszdotablicy(tmp);
    }
    else
    {
        set_dobryplik(false); //plik obrazka nie został otwarty
    }

    return;
}

void Pgm::saveToFile(std::string nazwaPliku)
{
    //tylko jeśli nasz obiekt mógł skądkolwiek wziąć listę pikseli
    if (get_dobryplik())
    {
        std::string tytul_celu = nazwaPliku + ".pgm"; //nazwa będzie podawana bez podania rozszerzenia
        std::ofstream cel; //plik do którego zapisujemy
        int a = 0, b = 0, nr_px = -1; //potrzebne do pętli
        int wysk = get_wysokosc(); //rozmiary dla tworzonego obrazka/pliku
        int szer = get_szerokosc();

        if (wysk * szer == pxtab.size()) //czy mamy odpowiednią ilość pikseli
        {
            cel.open(tytul_celu); //otwieramy plik, z którego zrobimy obraz
            cel << "P2" << std::endl; //pierwsza linijka ma oznaczenie formatu
            cel << szer << " " << wysk << std::endl; //w drugiej linijce jest szerokość i wysokość
            cel << "15" << std::endl; //w trzeciej linijce zapisano maksymalną wartość odcienia szarości 
            //czas wpisywać piksele
            for (a = 0; a < wysk; a++)
            {
                for (b = 0; b < szer; b++)
                {
                    nr_px++; //kolejny piksel z listy
                    cel << pxtab[nr_px].R << " "; //w PGM są wartości 0-15
                }
                cel << std::endl; //wiersz w obrazie to linijka w pliku
            }
            cel.close(); //po skończonym zapisywaniu zamykamy plik
        } //koniec 'if' dla poprawnej ilości pikseli
    } //koniec 'if' dla poprawnie otwartego/odczytanego pliku

    return;
}

//na różne sposoby przepisze listę pikseli z obiektu jednej z 3 klas pochodnych
void Pgm::load(Obraz* obraz)
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
        bialoczarny.R = obraz->value_from_table(a, 'R') / 16;
        bialoczarny.G = obraz->value_from_table(a, 'G') / 16;
        bialoczarny.B = obraz->value_from_table(a, 'B') / 16;
        pxtab.push_back(bialoczarny);
    }
    set_dobryplik(true); //mieliśmy skąd zczytać piksele
    return;
}

//stwórz listę pikseli z danego obrazka
void Pgm::wpiszdotablicy(std::string tmp_title)
{
    KolorRGB tenpiksel{0, 0, 0}; //do listy pikseli będziemy wrzucać opisy całych pikseli

    int wys = 0, szer = 0; //tymczasowo na rozmiar
    pxtab.clear(); //przed wypełnieniem listy kolorów trzeba ją najpierw opróżnić
    std::string linijka; //pomocniczy string
    int liczba; //pomocnicze
    
    std::ifstream abcd;
    abcd.open(tmp_title); //otwieramy plik bezkomentarzowy
    std::getline(abcd, linijka); //pierwsza linijka to format, jest teraz zbędna
    
    //odczytujemy rozmiar obrazka z nastepnej linijki
    abcd >> szer;
    abcd >> wys;
    set_size(szer, wys);
    //potem jest maksymalna wartość koloru (szarości)
    abcd >> linijka;

    //odczytywanie pikseli aż do końca pliku
    while (!abcd.eof())
    {
        abcd >> liczba; //każda liczba to jeden piksel
        tenpiksel.R = 16 * liczba;
        tenpiksel.G = tenpiksel.R;
        tenpiksel.B = tenpiksel.R;
        pxtab.push_back(tenpiksel);
    }//plik się skończył
    pxtab.pop_back(); //ostatni piksel wpisał się 2 razy

    abcd.close(); //zamykamy plik bezkomentarzowy
    set_load_completness(true); //załadowaliśmy listę pikseli (tu: odczytaliśmy z pliku)
 
    return;
}

