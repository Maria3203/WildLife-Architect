#ifndef ECOSISTEM_H
#define ECOSISTEM_H

#include "Entitate.h"
#include <vector>
#include <string>
#include <fstream>

class Harta {
private:
    int L, I;
    std::vector<std::string> grid;
public:
    Harta(int _L, int _I);
    void curata();
    void adauga(int x, int y, char simbol);
    void afiseaza() const;
};

class Ecosistem {
private:
    int latime, inaltime;
    std::vector<Entitate> populatie;
    Harta reprezentare;
    int indexJucator;
    int tureSupravietuite;

public:
    Ecosistem(int l, int i);
    
    // Incarcare date (Cerința T1: Fara date in cod)
    void incarcaHarta(const std::string& numeFisier, int modJoc);

    void ruleazaTura();
    bool esteFinalizat() const;
    
    // Logica Netriviala
    void proceseazaInteractiuni();
    bool verificareVictorie() const;
    void afiseazaStatusJucator() const;

    ~Ecosistem() = default;
};

#endif