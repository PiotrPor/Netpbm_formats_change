/*
 Klasa: Pbm
 Opis: Klasa pochodna. Zapisze do tabeli pikseli listę pikseli z obrazu zapisanego w PBM (forma ASCII).
       Może załadować listę pikseli z obrazu
       W pliku ignoruje linijki będące komentarzami
 Autor: Piotr Porembiński
 Data utworzenia: 17.02.2021
 Data edycji: 
   - 18.02.2021 - napisanie metod, zmiennych itd; program już się kompiluje
   - 19.02.2021 - debug, poprawki
   - 20.02.2021 - komentarze, estetyka/stylistyka
*/

#ifndef PBM_H
#define PBM_H

#include "Obraz.h"

class Pbm : public Obraz
{
private:
	//odziedziczy wszystkie zmienne
public:
	Pbm(); //konstruktor bezparametrowy
	Pbm(const Pbm& P2); //konstruktor kopiujący
	~Pbm(); //destruktor
	Pbm& operator=(Pbm& P2); //przeładowany operator '='

	//obowiązkowo trzeba zadeklarować ponownie metodę czysto wirtualną i ją zdefiniować
	void loadFromFile(std::string nazwaPliku); //inaczej ta klasa też stałaby się wirtualna
	void saveToFile(std::string nazwaPliku); //też wymaga definicji
	void load(Obraz* obraz); //też wymaga definicji

	//inna metoda
	//wypełnij tabelkę z pikselami (przyjmuje nazwę pliku bezkomentarzowego)
	void wpiszdotablicy(std::string tt); 
};

#endif
