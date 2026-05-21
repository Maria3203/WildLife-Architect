#include "../include/Prada.hpp"
#include "../include/Pradator.hpp"
#include <memory>

Prada::Prada(int x, int y, int energie, std::string numeSpecie, char sex, int valoare)
    : Animal(x, y, energie, numeSpecie, sex),
      valoareNutritiva(valoare),
      tureAlergate(0),
      esteObosita(false) {}

bool Prada::esteAmenintare(const std::shared_ptr<Entitate>& alta) const {
    if (!alta) return false;

    auto pradatorVecin = std::dynamic_pointer_cast<Pradator>(alta);

    return pradatorVecin != nullptr;
}

void Prada::actualizeazaOboseala() {
    if (tureAlergate > 0) {
        tureAlergate++;
        if (tureAlergate > 2) {
            esteObosita = true;
            tureAlergate = 0;
        }
    } else if (esteObosita) {
        esteObosita = false;
    }
}

void Prada::forteazaAlergare() {
    if (!esteObosita && tureAlergate == 0) {
        tureAlergate = 1;
    }
}