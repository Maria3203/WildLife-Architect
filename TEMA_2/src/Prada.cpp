#include "../include/Prada.hpp"


Prada::Prada(int x, int y, int energie, const std::string& numeSpecie, char sex)
    : Animal(x, y, energie, numeSpecie, sex), esteObosita(false) {
}
void Prada::actioneazaPradaStandard(const MatriceHarta& harti) {
    this->actualizeazaOboseala();

    if (this->esteObosita) {
        return;
    }

    executaMiscareAleatorieAI(harti);
    this->imbatraneste();
}