#ifndef OOP_ECOSISTEM_HPP
#define OOP_ECOSISTEM_HPP

#include "Entitate.hpp"
#include "Animal.hpp"
#include <vector>
#include <memory>

class Ecosistem {
private:
    int dimensiune;

    MatriceHarta harti;

    std::shared_ptr<Animal> jucator;
    int invPrey;
    int invGoodFruit;
    int invBadFruit;

    void curataEcranul() const;
    void afiseazaHartaCurenta() const;
    void afiseazaStatusJucator() const;
    void proceseazaTuraAI();
    void interactiuneCelulVeche(int vechiX, int vechiY, int noulX, int noulY);

public:
    explicit Ecosistem(int dim);


    Ecosistem(const Ecosistem& altul);
    Ecosistem& operator=(Ecosistem altul);
    ~Ecosistem() = default;

    friend void swap(Ecosistem& primul, Ecosistem& alDoilea) noexcept;


    void initJoc(int categorieJoc, int selectieAnimal, char sexJucator);
    void ruleazaJoc();


    void actualizeazaCelulaPeEcran(int x, int y);
};


#endif