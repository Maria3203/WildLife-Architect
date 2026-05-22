#include "../include/Pradator.hpp"
#include "../include/Prada.hpp"

Pradator::Pradator(int x, int y, int energie, const std::string& numeSpecie, char sex, int daune)
    : Animal(x, y, energie, numeSpecie, sex), dauneAtac(daune) {}

bool Pradator::esteAmenintare(const std::shared_ptr<Entitate>& alta) const {
    if (!alta) return false;

    auto altPradator = std::dynamic_pointer_cast<Pradator>(alta);

    if (altPradator) {
        return altPradator->calculeazaPutere() > this->calculeazaPutere();
    }

    return false;
}

