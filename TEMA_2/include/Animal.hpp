

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
    Animal(int x, int y, int energie, std::string numeSpecie, char sex);
    virtual ~Animal() = default;

    const std::vector<std::string>& getInventar() const { return inventarMancare; }
    void adaugaInInventar(const std::string& obiect) { inventarMancare.push_back(obiect); }

    virtual int calculeazaPutere() const = 0;

    virtual bool esteAmenintare(const std::shared_ptr<Entitate>& alta) const = 0;

    void imbatraneste() { varsta++; energie -= 2; }
    void acumuleazaExperienta(int exp) { experienta += exp; }

    bool estePrieten(int id) const;
    bool esteDusman(int id) const;
    void adaugaPrieten(int id);
    void adaugaDusman(int id);
};