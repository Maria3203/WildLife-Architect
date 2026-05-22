

#ifndef OOP_ANIMAL_HPP
#define OOP_ANIMAL_HPP

#endif


#pragma once
#include "Entitate.hpp"
#include <vector>

class Animal : public Entitate {
protected:
    int experienta;
    int varsta;
    std::vector<int> listaPrieteni;
    std::vector<int> listaDusmani;
    std::vector<std::string> inventarMancare;

public:
    Animal(int x, int y, int energie, const std::string& numeSpecie, char sex);
    ~Animal() override = default;


    virtual int calculeazaPutere() const = 0;

    virtual bool esteAmenintare(const std::shared_ptr<Entitate>& alta) const = 0;

    void imbatraneste() { varsta++; energie -= 2; }
    void acumuleazaExperienta(int exp) { experienta += exp; }

    bool estePrieten(int idCautat) const;
    void adaugaPrieten(int idAdaugat);
};