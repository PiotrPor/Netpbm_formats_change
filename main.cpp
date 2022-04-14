/*
 INNE KOMENTARZE W PLIKACH *.h
 Program wykorzystuje klasę: Obraz (abtrakcyjna), Ppm, Pgm, Pbm
 Tworzy listę pikseli odczytanych z *.ppm i przepisuje do formatu *.pgm i *.pbm
*/

#include "Ppm.h"
#include "Pgm.h"
#include "Pbm.h"


int main()
{
    Obraz* ppm = new Ppm();
    Obraz* pgm = new Pgm();
    Obraz* pbm = new Pbm();

    ppm->loadFromFile("lena.ppm");

    pgm->load(ppm);
    pgm->saveToFile("lena");

    pbm->load(ppm);
    pbm->saveToFile("lena");

    return 0;
}

