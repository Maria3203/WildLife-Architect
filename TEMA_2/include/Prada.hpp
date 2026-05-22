#ifndef OOP_PRADA_HPP
#define OOP_PRADA_HPP

#include "Animal.hpp"

class Prada : public Animal {
protected:
    int valoareNutritiva;
    int tureAlergate;
    bool esteObosita;

public:
    Prada(int x, int y, int energie, std::string numeSpecie, char sex, int valoare);
    virtual ~Prada() = default;


    bool getEsteObosita() const { return esteObosita; }
    
    int calculeazaPutere() const override { return energie + experienta; }


    bool esteAmenintare(const std::shared_ptr<Entitate>& alta) const override;

    void actualizeazaOboseala();
    void forteazaAlergare();
};


#endif