#ifndef OOP_PLANTA_HPP
#define OOP_PLANTA_HPP

#include "Entitate.hpp"

class Planta : public Entitate {
protected:
    int bonusEnergie;
    bool esteOtravitoare;
    bool inspectata;

public:
    Planta(int x, int y, int energie, const std::string& numeSpecie, int bonus, bool otrava);
    ~Planta() override = default;

    int getBonusEnergie() const { return bonusEnergie; }



    void actioneaza(const MatriceHarta& harti) override;
};

#endif