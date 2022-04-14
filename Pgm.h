/*
 Klasa: Pgm
 Opis:  Klasa pochodna. Zapisze do tabeli pikseli listę pikseli z obrazu zapisanego w PGM (forma ASCII).
	Może załadować listę pikseli z obrazu
	W pliku ignoruje linijki będące komentarzami
 Autor: Piotr Porembiński
 Data utworzenia: 17.02.2021
 Data edycji: 
   - 18.02.2021 - napisanie metod, zmiennych itd; program już się kompiluje
   - 19.02.2021 - debug, poprawki
   - 20.02.2021 - komentarze, estetyka/stylistyka
*/

#ifndef PGM_H
#define PGM_H

#include "Obraz.h"

class Pgm : public Obraz
{
 private:
	//wszystkie zmienne dziedziczy
 public:
	Pgm(); //konstruktor bezparametrowy
	Pgm(const Pgm& P2); //konstruktor kopiujący
	~Pgm(); //destruktor
	Pgm& operator=(Pgm& P2); //przeładowanie operatora '='

	//obowiązkowo trzeba zadeklarować ponownie metodę czysto wirtualną i ją zdefiniować
	void loadFromFile(std::string nazwaPliku); //inaczej ta klasa też stałaby się wirtualna
	void saveToFile(std::string nazwaPliku); //to też była metoda czysto wirtualna
	void load(Obraz* obraz); //tu tak samo

	//inna metoda
	void wpiszdotablicy(std::string tmp_title); //wypełnij tabelkę z pikselami (czyta z bezkomentarzowego pliku)
};

#endif
