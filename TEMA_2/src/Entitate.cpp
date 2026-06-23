
#include "../include/Entitate.hpp"

static int contorID_global = 0;


Entitate::Entitate(int x, int y,  int energie, const std::string& numeSpecieParam)
    : x(x), y(y), id(++contorID_global), energie(energie), numeSpecie(numeSpecieParam) {
}


std::ostream& operator<<(std::ostream& os, const Entitate& entitate) {
    entitate.afiseaza(os);
    return os;
}