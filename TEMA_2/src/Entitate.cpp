
#include "../include/Entitate.hpp"

int Entitate::contorID = 0;

Entitate::Entitate(int x, int y, int energie, const std::string& numeSpecie, char sex)
    : id_(++contorID), numeSpecie(numeSpecie), sex(sex), x(x), y(y), energie(energie) {}

void Entitate::afiseaza(std::ostream& os) const {
    doAfiseaza(os);
}

void Entitate::modificaEnergie(int cantitate) {
    this->energie += cantitate;
    if (this->energie < 0) this->energie = 0;
}

void Entitate::setPozitie(int nouX, int nouY) {
    this->x = nouX;
    this->y = nouY;
}



std::ostream& operator<<(std::ostream& os, const Entitate& entitate) {
    entitate.afiseaza(os);
    return os;
}