/*
  Klasa: Ppm
  Opis: Klasa pochodna. Zapisze do tabeli pikseli listę pikseli z obrazu zapisanego w PPM (forma ASCII).
	Może załadować listę pikseli z obrazu
	W pliku ignoruje linijki będące komentarzami
  Autor: Piotr Porembiński
  Data utworzenia: 17.02.2021
  Data edycji: 
   - 18.02.2021 - napisanie metod, zmiennych itd; program już się kompiluje
   - 19.02.2021 - debug, poprawki
   - 20.02.2021 - komentarze, estetyka/stylistyka
*/

#ifndef PPM_H
#define PPM_H

#include "Obraz.h"

class Ppm : public Obraz
{
private:
	//wszytko jest dziedziczone
public:
	Ppm(); //konstruktor bezparametrowy
	Ppm(const Ppm& P2); //konstruktor kopiujący
	~Ppm(); //destruktor
	Ppm& operator=(Ppm& P2); //przeładowanie operatora '='

	//obowiązkowo trzeba zadeklarować ponownie metodę czysto wirtualną i ją zdefiniować
	void loadFromFile(std::string nazwaPliku); //inaczej ta klasa też stałaby się abstrakcyjna
	void saveToFile(std::string nazwaPliku); //to też była metoda czysto wirtualna
	void load(Obraz* obraz); //tu tak samo

	//inna metoda
	//wypełnij listę pikseli (podajemy nazwę bezkomentarzowego pliku)
	void wpiszdotablicy(std::string noncomment);
};

#endif
