#include "../include/GeneratorID.hpp"
#include "../include/Entitate.hpp"




Entitate::Entitate(int x, int y,  int energie, const std::string& numeSpecieParam)
    : x(x), y(y), id(GeneratorID::getInstance().genereazaID()), energie(energie), numeSpecie(numeSpecieParam) {
}


std::ostream& operator<<(std::ostream& os, const Entitate& entitate) {
    entitate.afiseaza(os);
    return os;
}