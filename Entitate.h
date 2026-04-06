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

    void modificaEnergie(int cantitate) { energie += cantitate; }
    void imbatraneste() {
        varsta++;
        putere += 2; // Puterea creste cu varsta (pana la un punct)
    }
    bool ePreaBatran() const { return varsta >= varstaMaxima; }
    void setFamilie(bool stare) { areFamilie = stare; }
};

class Entitate {
private:
    std::string nume;
    char simbol;
    TipEntitate tip;
    class Pozitie* pos;
    Statistici stats;
    std::vector<std::string> inventar;

public:
    Entitate(std::string n, char s, TipEntitate t, int x, int y, Statistici st);

    Entitate(const Entitate& alta);
    Entitate& operator=(const Entitate& alta);
    ~Entitate();

    void deplasareManual(int maxW, int maxH);
    void deplasareAI(int maxW, int maxH);

    void adaugaInInventar(std::string obiect);
    void interactioneaza(Entitate& alta);
    bool incearcaFamilie(Entitate& partener);

    bool esteVie() const {
        return stats.getEnergie() > 0 && !stats.ePreaBatran();
    }

    int getX() const;
    int getY() const;
    char getSimbol() const { return simbol; }
    std::string getNume() const { return nume; }

    friend std::ostream& operator<<(std::ostream& os, const Entitate& e);
};

#endif