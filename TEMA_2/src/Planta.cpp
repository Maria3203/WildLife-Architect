
#include "../include/Planta.hpp"

Planta::Planta(int x, int y, int energie, const std::string& numeSpecie, int bonus, bool otrava)
    : Entitate(x, y, energie, numeSpecie, 'N'), bonusEnergie(bonus), esteOtravitoare(otrava),inspectata(false){}

void Planta::actioneaza(const MatriceHarta&) {
}