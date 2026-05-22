
#include "../include/Planta.hpp"

Planta::Planta(int x, int y, int energie, std::string numeSpecie, int bonus, bool otrava)
    : Entitate(x, y, energie, numeSpecie, 'N'), bonusEnergie(bonus), esteOtravitoare(otrava){}

void Planta::actioneaza(const MatriceHarta&) {
}