#include "../include/Animal.hpp"
#include <algorithm>

Animal::Animal(int x, int y, int energie, const std::string &numeSpecie, char sex_param)
    : Entitate(x, y, energie, numeSpecie, sex_param),
      experienta(0),
      varsta(0) {

}

// Am schimbat 'nouId' in 'idCautat' / 'idAdaugat' pt a nu se mai suprapune absolut niciodata cu variabilele din clase
bool Animal::estePrieten(int idCautat) const {
    return std::find(listaPrieteni.begin(), listaPrieteni.end(), idCautat) != listaPrieteni.end();
}


void Animal::adaugaPrieten(int idAdaugat) {
    if (!estePrieten(idAdaugat)) {
        listaPrieteni.push_back(idAdaugat);
    }
}


