#include "Entitate.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

class Pozitie {
private:
    int x, y;
public:
    Pozitie(int _x, int _y) : x(_x), y(_y) {}
    int getX() const { return x; }
    int getY() const { return y; }
    void set(int _x, int _y) { x = _x; y = _y; }
};
bool Entitate::esteVie() const {
    return (stats.getEnergie() > 0) && (!stats.ePreaBatran());
}

Entitate::Entitate(const std::string& n, char s, TipEntitate t, int x, int y, const Statistici& st)
    : nume(n), simbol(s), tip(t), stats(st) {
    pos = new Pozitie(x, y);
}

Entitate::~Entitate() {
    delete pos;
}

Entitate::Entitate(const Entitate& alta)
    : nume(alta.nume), simbol(alta.simbol), tip(alta.tip), stats(alta.stats), inventar(alta.inventar) {
    pos = new Pozitie(alta.pos->getX(), alta.pos->getY());
}

Entitate& Entitate::operator=(const Entitate& alta) {
    if (this != &alta) {
        delete pos;
        nume = alta.nume;
        simbol = alta.simbol;
        tip = alta.tip;
        stats = alta.stats;
        inventar = alta.inventar;
        pos = new Pozitie(alta.pos->getX(), alta.pos->getY());
    }
    return *this;
}


void Entitate::deplasareManual(int maxW, int maxH) {
    char tasta;
    std::cout << "\n[" << nume << "] WASD pentru miscare: ";
    if (!(std::cin >> tasta)) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        return;
    }
    std::cin.ignore(1000, '\n'); // Curățăm buffer-ul

    int v = stats.getViteza();
    int nx = pos->getX(), ny = pos->getY();

    if (tasta == 'w' || tasta == 'W') ny -= v;
    else if (tasta == 's' || tasta == 'S') ny += v;
    else if (tasta == 'a' || tasta == 'A') nx -= v;
    else if (tasta == 'd' || tasta == 'D') nx += v;

    pos->set(std::max(0, std::min(maxW - 1, nx)),
             std::max(0, std::min(maxH - 1, ny)));

    stats.modificaEnergie(-5);
    stats.imbatraneste();
}

void Entitate::urmaresteSauFuge(const std::vector<Entitate>& alteEntitati, int maxW, int maxH) {
    if (tip == TipEntitate::Planta || !esteVie()) return;

    int tx = -1, ty = -1;
    double distMin = 999.0;

    for (const auto& alta : alteEntitati) {
        if (&alta == this || !alta.esteVie()) continue;
        if (!this->poateVedea(alta)) continue;

        double d = std::sqrt(std::pow(pos->getX() - alta.getX(), 2) +
                            std::pow(pos->getY() - alta.getY(), 2));

        bool eTinta = (this->tip == TipEntitate::Pradator && alta.tip == TipEntitate::Prada) ||
                      (this->tip == TipEntitate::Prada && alta.tip == TipEntitate::Pradator);

        if (eTinta && d < distMin) {
            distMin = d;
            tx = alta.getX();
            ty = alta.getY();
        }
    }

    int pasX = 0, pasY = 0;
    if (tx != -1) {
        pasX = (tx > pos->getX()) ? 1 : -1;
        pasY = (ty > pos->getY()) ? 1 : -1;
        if (this->tip == TipEntitate::Prada) { pasX *= -1; pasY *= -1; } // Fugim!
    } else {
        pasX = (rand() % 3 - 1);
        pasY = (rand() % 3 - 1);
    }

    int v = stats.getViteza();
    int nx = std::max(0, std::min(maxW - 1, pos->getX() + pasX * v));
    int ny = std::max(0, std::min(maxH - 1, pos->getY() + pasY * v));

    pos->set(nx, ny);
    stats.modificaEnergie(-2);
    stats.imbatraneste();
}


void Entitate::interactioneaza(Entitate& alta) {
    if (!this->esteVie() || !alta.esteVie()) return;

    if (this->tip == TipEntitate::Pradator && alta.tip == TipEntitate::Prada) {
        this->stats.modificaEnergie(40);
        alta.stats.modificaEnergie(-500); // Moare
        this->inventar.push_back("Carne_de_" + alta.nume);
    }

    else if (this->tip == TipEntitate::Pradator && alta.tip == TipEntitate::Pradator) {
        if (this->stats.getPutere() >= alta.stats.getPutere()) {
            alta.stats.modificaEnergie(-30);
        } else {
            this->stats.modificaEnergie(-30);
        }
    }
}

bool Entitate::incearcaReproducere(std::vector<Entitate>& populatie) {
    if (stats.poateSaSeReproduca() && (rand() % 100 < 10)) { // 10% șansă
        Statistici sPui(80, stats.getPutere() / 2, stats.getViteza(),
                       (rand() % 2 == 0 ? Gen::Masculin : Gen::Feminin), 30);
        populatie.emplace_back("Pui_" + nume, tolower(simbol), tip, pos->getX(), pos->getY(), sPui);
        stats.modificaEnergie(-40);
        return true;
    }
    return false;
}

void Entitate::gestioneazaResurse() {
    if (stats.getEnergie() < 40 && !inventar.empty()) {
        stats.modificaEnergie(25);
        inventar.pop_back();
    }
}

bool Entitate::incearcaFamilie(Entitate& partener) {
    if (this->tip == partener.tip && this->stats.getGen() != partener.stats.getGen() &&
        !this->stats.hasFamily() && !partener.stats.hasFamily()) {
        this->stats.setFamilie(true);
        partener.stats.setFamilie(true);
        return true;
    }
    return false;
}


int Entitate::getX() const { return pos->getX(); }
int Entitate::getY() const { return pos->getY(); }

bool Entitate::operator>(const Entitate& alta) const {
    return this->stats.getPutere() > alta.stats.getPutere();
}

bool Entitate::operator==(const Entitate& alta) const {
    return this->nume == alta.nume;
}

Entitate& Entitate::operator++() {
    this->stats.imbatraneste();
    this->stats.modificaEnergie(-10);
    return *this;
}
bool Entitate::poateVedea(const Entitate& alta) const {
    int distanta = std::abs(this->getX() - alta.getX()) + std::abs(this->getY() - alta.getY());
    return distanta <= 5;
}
void Entitate::aplicaEfecteTura() {
    stats.modificaEnergie(-1);
    if (stats.getEnergie() > 90) {
        stats.imbatraneste();
    }

    if (stats.getVarsta() > 15) {
        stats.modificaEnergie(-2);
    }
}
std::ostream& operator<<(std::ostream& os, const Entitate& e) {
    os << "[" << e.simbol << "] " << e.nume
       << " | Energie: " << e.stats.getEnergie()
       << " | Putere: " << e.stats.getPutere()
       << " | Varsta: " << e.stats.getVarsta()
       << " | Inv: " << e.inventar.size();
    return os;
}