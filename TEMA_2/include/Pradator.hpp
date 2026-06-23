#ifndef OOP_PRADATOR_HPP
#define OOP_PRADATOR_HPP

#include "Animal.hpp"

class Pradator : public Animal {
protected:
    int dauneAtac;

public:
    Pradator(int x, int y, int energie, const std::string& numeSpecie, char sex, int daune);
    ~Pradator() override = default;


    bool estePradator() const override { return true; }

    int calculeazaPutere() const override { return energie + dauneAtac + (experienta * 2); }
    bool esteAmenintare(const std::shared_ptr<Entitate>& alta) const override;

    void actioneazaPradatorStandard(const MatriceHarta& harti, int bonusEnergieAtac, int bonusExperienta = 0);
};

#endif