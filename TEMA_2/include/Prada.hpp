#ifndef OOP_PRADA_HPP
#define OOP_PRADA_HPP

#include "Animal.hpp" // Foarte important!


class Prada : public Animal {
protected:
    bool esteObosita;

public:

    Prada(int x, int y, int energie, const std::string& numeSpecie, char sex);
    ~Prada() override = default;

    bool estePrada() const override { return true; }
    void actioneazaPradaStandard(const MatriceHarta& harti);
    virtual void actualizeazaOboseala() = 0;

    int calculeazaPutere() const override { return energie; }


    bool esteAmenintare(const std::shared_ptr<Entitate>& alta) const override { return false; }
};

#endif