#ifndef OOP_PLANTA_HPP
#define OOP_PLANTA_HPP

#include "Entitate.hpp"

class Planta : public Entitate {
protected:
    int bonusEnergie;
    bool esteOtravitoare_var;
    bool inspectata;

public:
    Planta(int x, int y, int energie, const std::string& numeSpecie, int bonus, bool otrava);
    ~Planta() override = default;

    int getBonusEnergie() const override { return bonusEnergie; }
    bool estePlanta() const override { return true; }
    virtual bool esteOtravitoare() const  {return false;}

    void actioneaza(const MatriceHarta& harti) override;
};

#endif