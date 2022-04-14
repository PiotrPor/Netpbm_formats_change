/*
 Klasa: Obraz
 Opis: Klasa (bazowa) abstrakcyjna, w której są zmienne i metody wspólne dla pozostałych klas pochodnych
       Każda klasa pochodna zajmuje się innym formatem obrazu
 Autor: Piotr Porembiński
 Data utworzenia: 17.02.2021
 Data edycji: 
   - 18.02.2021 - napisanie metod, zmiennych itd; program już się kompiluje
   - 19.02.2021 - debug, poprawki
   - 20.02.2021 - komentarze, estetyka/stylistyka
*/

#ifndef OBRAZ_H
#define OBRAZ_H

//wszystki klasy pochodne to odziedziczą
#include <string>
#include <vector>
#include <fstream>

struct KolorRGB
{
	int R;
	int G;
	int B;
};

class Obraz
{
protected:
	std::vector<KolorRGB> pxtab; //tablica z pikselami (każda komórka to liczby o jednym pikselu)
	int wysokosc;
	int szerokosc;
	bool zaladowany; //czy już wczytano obraz?
	bool dobryplik; //czy plik który dano do obróbki został poprawnie otwarty i/lub czy istnieje
	std::string tytul;
	std::ifstream obrazek;
public:
	Obraz(); //konstruktor bezparametrowy
	Obraz(const Obraz& O2); //konstruktor kopiujący
	~Obraz(); //destruktor
	Obraz& operator=(Obraz& O2); //przeładowany operator '='

	//metody abstrakcyjne (w każdej klasie pochodnej musi być definiowana na nowo)
	virtual void loadFromFile(std::string nazwaPliku) = 0; //każda klasa trochę inaczej czyta z pliku
	virtual void load(Obraz* obraz) = 0; //zależy od formatu jakim zajmuje się nasz obiekt  
	virtual void saveToFile(std::string nazwaPliku) = 0; //trochę inne zasady zapisu każdego formatu

	//setter'y i getter'y
	void set_size(int a, int b); //szerokosc, wysokosc
	int get_wysokosc();
	int get_szerokosc();
	bool check_whether_loaded(); //czy już załadowano obraz?
	void set_load_completness(bool cc); //czy już skończono ładować obraz
	void set_tytul(std::string tt);
	std::string get_tytul();
	int value_from_table(int w, char n); //zwraca konkretną wartość z tabeli pikseli
	std::vector<KolorRGB> return_table(); //zwraca całą tablicę pikseli
	void set_dobryplik(bool ff); //setter dla 'dobryplik'
	bool get_dobryplik(); //getter dla 'dobryplik'

	//jeszcze jedna metoda
	//Przepisze do innego pliku plik obrazu, ale bez komentarzy. Zwraca jego tytuł.
	//'przedrostek' i 'rozszerzenie' służą do utworzenia tytułu tego bezkomentarzowego pliku
	std::string bez_komentarzy(std::string przedrostek, std::string rozszerzenie);
};

#endif
