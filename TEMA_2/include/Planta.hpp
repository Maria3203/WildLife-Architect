#ifndef OOP_PLANTA_HPP
#define OOP_PLANTA_HPP

#include "Entitate.hpp"

class Planta : public Entitate {
protected:
    int bonusEnergie;
    bool esteOtravitoare;
    bool inspectata;

public:
    Planta(int x, int y, int energie, std::string numeSpecie, int bonus, bool otrava);
    virtual ~Planta() = default;

    int getBonusEnergie() const { return bonusEnergie; }
    bool aFostInspectata() const { return inspectata; }


    void actioneaza(const MatriceHarta& harti) override;
};

#endif