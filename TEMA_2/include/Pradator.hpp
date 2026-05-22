#ifndef OOP_PRADATOR_HPP
#define OOP_PRADATOR_HPP

#include "Animal.hpp"

class Pradator : public Animal {
protected:
    int dauneAtac;

public:
    Pradator(int x, int y, int energie, std::string numeSpecie, char sex, int daune);
    virtual ~Pradator() = default;

    int calculeazaPutere() const override { return energie + dauneAtac + (experienta * 2); }


    bool esteAmenintare(const std::shared_ptr<Entitate>& alta) const override;

};

#endif