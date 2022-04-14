#include "Obraz.h"

//======== KONSTRUKTORY, DESTRUKTORY, OPERATORY
//konstruktor bezparametrowy
Obraz::Obraz()
{
	set_load_completness(false);
	set_dobryplik(false); //domyślnie plik nie został jeszcze poprawnie otwarty
}

//konstruktor kopiujący
Obraz::Obraz(const Obraz& O2)
{
	pxtab = O2.pxtab; //pxtab = O2.return_table();
	set_size(O2.szerokosc, O2.wysokosc); //set_size(O2.get_szerokosc(), O2.get_wysokosc());
	set_load_completness(O2.zaladowany); //set_load_completness(O2.check_whether_loaded());
	tytul = O2.tytul; //tytul = O2.get_tytul();
	set_dobryplik(O2.dobryplik);
}

//destruktor
Obraz::~Obraz()
{
	if (obrazek.is_open())
	{
		obrazek.close();
	}
	//std::vector ma swój destruktor
	//std::string ma swój destruktor
}

Obraz& Obraz::operator=(Obraz& O2)
{
	//sprawdzenie czy to nie ten sam obiekt
	if (this == &O2)
	{
		return *this;
	}

	this->pxtab = O2.pxtab;
	this->set_size(O2.get_szerokosc(), O2.get_wysokosc());
	this->set_load_completness(O2.check_whether_loaded());
	this->set_tytul(O2.get_tytul());
	this->set_dobryplik(O2.get_dobryplik());

	return *this;
}

//muszą być czysto wirtualna w klasie abstrakcyjnej
  //void Obraz::loadFromFile(std::string nazwaPliku); 
  //void Obraz::load(Obraz* obraz);   
  //void Obraz::saveToFile(std::string nazwaPliku);


//======== SETTERy i GETTERy

//argumenty metody: (szerokosc, wysokosc)
void Obraz::set_size(int a, int b)
{
	if (a >= 1 && a <= 1920) //zakladam max rozdzielczosc 1920x1080
	{
		szerokosc = a;
	}
	else
	{
		szerokosc = 1;
	}
	//teraz wysokość
	if (b >= 1 && b <= 1080)//?
	{
		wysokosc = b;
	}
	else
	{
		wysokosc = 1;
	}

	return;
}

int Obraz::get_wysokosc()
{
	return wysokosc;
}

int Obraz::get_szerokosc()
{
	return szerokosc;
}

bool Obraz::check_whether_loaded()
{
	return zaladowany;
}

void Obraz::set_load_completness(bool cc)
{
	zaladowany = cc;
	return;
}

void Obraz::set_tytul(std::string tt)
{
	tytul = tt;
	return;
}

std::string Obraz::get_tytul()
{
	return tytul;
}

//getter by poznać pojedyńcza konkretną wartość z listy pikseli
int Obraz::value_from_table(int w, char n)
{
	switch (n)
	{
	  case 'R':
	  {return pxtab[w].R; break;}
	  case 'G':
	  {return pxtab[w].G; break; }
	  case 'B':
	  {return pxtab[w].B; break; }
	  default:
	  {return pxtab[w].R; }
	}
}

//ten getter zwraca całą listę pikseli
std::vector<KolorRGB> Obraz::return_table()
{
	return pxtab;
}

void Obraz::set_dobryplik(bool ff)
{
	dobryplik = ff;
	return;
}

bool Obraz::get_dobryplik()
{
	return dobryplik;
}

//stworzy plik, który ma treść jak plik badanego obrazka, ale nie ma w sobie komentarzy
std::string Obraz::bez_komentarzy(std::string przedrostek, std::string rozszerzenie)
{
	//tytuł pliku bez komentarzy powstaje ze sklejenia 3 stringów
	std::string tytul_czystego = przedrostek + "_without_comments." + rozszerzenie;
	std::ofstream nc;
	nc.open(tytul_czystego); // tworzy/otwiera plik bez komentarzy 

	std::string linijka; //plik obrazka będziemy czytać linijka po linijce
	std::string nowa; //pomocniczy string
	unsigned int a; //dla pętli

	while (!obrazek.eof())
	{
		std::getline(obrazek, linijka); //getline() nadpisze string'a "linijka"
		//kolejna linijka z pliku nie jest pusta i nie jest cała komentarzem
		if (!(linijka.find_first_of('#') == 0) && !linijka.empty())
		{
			for (a = 0; a < linijka.size(); a++)
			{
				//przepisujemy linijkę do pomocniczego stringa znak po znaku
				//chyba że jest ona od pewnego punktu komentarzem (wtedy resztę dalej ignorujemy)
				if (linijka[a] != '#')
				{
					nowa.push_back(linijka[a]);
				}
				else
				{
					break;
				}
			}
			nc << nowa << "\n"; //dopisujemy do bezkomentarzowego pliku kolejną linijkę
		}
		nowa.clear(); //bo od nowej linii znów będzie X.push_back()
	}

	nc.close(); //zamykamy plik po skończonej pracy
	return tytul_czystego; //funkcja zwraca nazwę bezkomentarzowego pliku
}

