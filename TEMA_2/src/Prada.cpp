#include "../include/Prada.hpp"
#include "SpeciiPrazi.hpp"


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
void Iepure::actualizeazaOboseala() {
    // Momentan goala
}
void Iepure::actioneaza(const MatriceHarta& harti) {
    this->actioneazaPradaStandard(harti);
}

// --- CAPRIOARA ---
void Caprioara::actualizeazaOboseala() { }
void Caprioara::actioneaza(const MatriceHarta& harti) {
    this->actioneazaPradaStandard(harti);
}

// --- PASARE ---
void Pasare::actualizeazaOboseala() { }
void Pasare::actioneaza(const MatriceHarta& harti) {
    this->actioneazaPradaStandard(harti);
}

// --- VEVERITA ---
void Veverita::actualizeazaOboseala() { }
void Veverita::actioneaza(const MatriceHarta& harti) {
    this->actioneazaPradaStandard(harti);
}