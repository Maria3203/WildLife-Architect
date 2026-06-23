
#include "../include/Planta.hpp"

Planta::Planta(int x, int y, int energie, const std::string& numeSpecie_param, int bonus, bool otrava)
    : Entitate(x, y, energie, numeSpecie_param), // <--- SCHIMBAREA AICI
      bonusEnergie(bonus),
      esteOtravitoare_var(otrava),
      inspectata(false) {
}
void Planta::actioneaza(const MatriceHarta&) {
}