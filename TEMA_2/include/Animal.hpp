#ifndef OOP_ANIMAL_HPP
#define OOP_ANIMAL_HPP

#include "Entitate.hpp"

class Animal : public Entitate {
protected:
    char sex;           // numeSpecie a disparut de aici!
    int experienta;
    int varsta;
    std::vector<int> listaPrieteni;



public:
    Animal(int x, int y, int energie, const std::string& numeSpecieParam, char sexParam);
    ~Animal() override = default;

    char getSex() const { return sex; }
    void executaMiscareAleatorieAI(const MatriceHarta& harti);
    // Alte metode pe care le mai aveai tu...
    virtual int calculeazaPutere() const = 0;
    virtual bool esteAmenintare(const std::shared_ptr<Entitate>& alta) const = 0;
    
    void adaugaPrieten(int idPrieten);
    bool estePrieten(int idPrieten) const;
    void imbatraneste();
    void acumuleazaExperienta(int exp);
};

#endif