

#include "../include/Animal.hpp"
#include <algorithm> // Pentru std::find

Animal::Animal(int x, int y, int energie, std::string numeSpecie, char sex_param)
    : Entitate(x, y, energie, numeSpecie, sex_param),
      experienta(0),
      varsta(0) {

}

bool Animal::estePrieten(int nouId) const {
    return std::find(listaPrieteni.begin(), listaPrieteni.end(), nouId) != listaPrieteni.end();
}

bool Animal::esteDusman(int nouId) const {
    return std::find(listaDusmani.begin(), listaDusmani.end(), nouId) != listaDusmani.end();
}

void Animal::adaugaPrieten(int nouId) {
    if (!estePrieten(nouId)) {
        listaPrieteni.push_back(nouId);
    }
}

void Animal::adaugaDusman(int nouId) {
    if (!esteDusman(nouId)) {
        listaDusmani.push_back(nouId);
    }
}