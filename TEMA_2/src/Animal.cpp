

#include "../include/Animal.hpp"
#include <algorithm> // Pentru std::find

Animal::Animal(int x, int y, int energie, std::string numeSpecie, char sex_param)
    : Entitate(x, y, energie, numeSpecie, sex_param),
      experienta(0),
      varsta(0) {

}

bool Animal::estePrieten(int id) const {
    return std::find(listaPrieteni.begin(), listaPrieteni.end(), id) != listaPrieteni.end();
}

bool Animal::esteDusman(int id) const {
    return std::find(listaDusmani.begin(), listaDusmani.end(), id) != listaDusmani.end();
}

void Animal::adaugaPrieten(int id) {
    if (!estePrieten(id)) {
        listaPrieteni.push_back(id);
    }
}

void Animal::adaugaDusman(int id) {
    if (!esteDusman(id)) {
        listaDusmani.push_back(id);
    }
}