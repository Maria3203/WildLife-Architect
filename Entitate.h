#ifndef ENTITATE_H
#define ENTITATE_H

#include <iostream>
#include <vector>
#include <string>


enum class Gen { Masculin, Feminin, Nedeterminat };
enum class TipEntitate { Pradator, Prada, Planta };


class Statistici {
private:
    int energie;
    int putere;
    int viteza;
    int varsta;
    int varstaMaxima;
    Gen gen;
    bool areFamilie;

public:
    Statistici(int e = 100, int p = 10, int v = 1, Gen g = Gen::Nedeterminat, int vMax = 20)
        : energie(e), putere(p), viteza(v), varsta(0), varstaMaxima(vMax), gen(g), areFamilie(false) {}


    int getEnergie() const { return energie; }
    int getPutere() const { return putere; }
    int getViteza() const { return viteza; }
    int getVarsta() const { return varsta; }
    Gen getGen() const { return gen; }
    bool hasFamily() const { return areFamilie; }
    bool ePreaBatran() const { return varsta >= varstaMaxima; }
    bool poateSaSeReproduca() const { return energie > 70 && areFamilie; }



    void modificaEnergie(int cantitate) { energie += cantitate; }
    void imbatraneste() { varsta++; putere += 1; }
    void setFamilie(bool stare) { areFamilie = stare; }
    void consumaEnergieReproducere() { energie -= 50; }
};


class Pozitie;


class Entitate {
private:
    std::string nume;
    char simbol;
    TipEntitate tip;
    Pozitie* pos;            // Pointer pentru Rule of 3
    Statistici stats;
    std::vector<std::string> inventar;

public:
    bool operator>(const Entitate& alta) const;
    bool operator==(const Entitate& alta) const;
    Entitate& operator++();

    Entitate(const std::string& n, char s, TipEntitate t, int x, int y, const Statistici& st);


    Entitate(const Entitate& alta);
    Entitate& operator=(const Entitate& alta);
    ~Entitate();


    void deplasareManual(int maxW, int maxH);
    void urmaresteSauFuge(const std::vector<Entitate>& alteEntitati, int maxW, int maxH);


    void interactioneaza(Entitate& alta);
    bool incearcaFamilie(Entitate& partener);
    bool incearcaReproducere(std::vector<Entitate>& populatie);
    void gestioneazaResurse();
    bool poateVedea(const Entitate& alta) const;


    bool esteVie() const;
    int getX() const;
    int getY() const;
    char getSimbol() const { return simbol; }
    TipEntitate getTip() const { return tip; }
    const std::string& getNume() const { return nume; }
    Statistici& getStats() { return stats; }
    const Statistici& getStats() const { return stats; }



    friend std::ostream& operator<<(std::ostream& os, const Entitate& e);
};

#endif