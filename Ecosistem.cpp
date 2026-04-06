#include "Ecosistem.h"
#include <iostream>
#include <algorithm>

Harta::Harta(int _L, int _I) : L(_L), I(_I) {
    grid.resize(I, std::string(L, '.'));
}

void Harta::curata() {
    for (auto& rand : grid) std::fill(rand.begin(), rand.end(), '.');
}

void Harta::adauga(int x, int y, char simbol) {
    if (x >= 0 && x < L && y >= 0 && y < I) grid[y][x] = simbol;
}

void Harta::afiseaza() const {
    std::cout << "\033[2J\033[1;1H"; // Clear screen (ANSI)
    std::cout << "   " << std::string(L * 2, '-') << "\n";
    for (int i = 0; i < I; ++i) {
        std::cout << (i < 10 ? "0" : "") << i << " | ";
        for (char c : grid[i]) {
             std::cout << c << " ";
        }
        std::cout << "|\n";
    }
    std::cout << "   " << std::string(L * 2, '-') << "\n";
}


Ecosistem::Ecosistem(int l, int i) 
    : latime(l), inaltime(i), reprezentare(l, i), indexJucator(-1), tureSupravietuite(0) {}

void Ecosistem::incarcaHarta(const std::string& numeFisier, int modJoc) {
    std::ifstream f(numeFisier);
    if (!f.is_open()) {
        std::cerr << "Eroare: Nu am putut deschide fisierul " << numeFisier << "\n";
        return;
    }

    if (modJoc == 1) {
        populatie.emplace_back("Player_Lup", 'L', TipEntitate::Pradator, 0, 0, Statistici(100, 20, 1, Gen::Masculin, 50));
    } else { // Mod Prada
        populatie.emplace_back("Player_Iepure", 'I', TipEntitate::Prada, 1, 1, Statistici(80, 5, 2, Gen::Feminin, 30));
    }
    indexJucator = 0;

    std::string nume;
    char simbol;
    int tipInt, x, y, en, put, vit, genInt, vMax;
    
    while (f >> nume >> simbol >> tipInt >> x >> y >> en >> put >> vit >> genInt >> vMax) {
        TipEntitate t = static_cast<TipEntitate>(tipInt);
        Gen g = static_cast<Gen>(genInt);
        populatie.emplace_back(nume, simbol, t, x, y, Statistici(en, put, vit, g, vMax));
    }
    f.close();
}

void Ecosistem::ruleazaTura() {
    // 1. Afișăm Harta prima dată
    reprezentare.curata();
    for (const auto& e : populatie) {
        if (e.esteVie()) reprezentare.adauga(e.getX(), e.getY(), e.getSimbol());
    }
    reprezentare.afiseaza();
    afiseazaStatusJucator();

    // 2. Așteptăm inputul tău (AICI se blochează programul până scrii ceva)
    populatie[indexJucator].deplasareManual(latime, inaltime);

    // 3. Abia după ce te-ai mutat tu, se mută și restul
    for (size_t i = 1; i < populatie.size(); ++i) {
        populatie[i].deplasareAI(latime, inaltime);
    }

    proceseazaInteractiuni();
}

void Ecosistem::proceseazaInteractiuni() {
    for (size_t i = 0; i < populatie.size(); ++i) {
        if (!populatie[i].esteVie()) continue;
        
        for (size_t j = 0; j < populatie.size(); ++j) {
            if (i == j || !populatie[j].esteVie()) continue;

            if (populatie[i].getX() == populatie[j].getX() && 
                populatie[i].getY() == populatie[j].getY()) {

                if (populatie[i].incearcaFamilie(populatie[j])) {
                    std::cout << "[INFO] " << populatie[i].getNume() << " a format o familie cu " << populatie[j].getNume() << "!\n";
                }
                populatie[i].interactioneaza(populatie[j]);
            }
        }
    }

    populatie.erase(std::remove_if(populatie.begin() + 1, populatie.end(),
        [](const Entitate& e) { return !e.esteVie(); }), populatie.end());
}

bool Ecosistem::verificareVictorie() const {
    const auto& j = populatie[indexJucator];
    return (j.getX() == latime - 1 && j.getY() == inaltime - 1);
}

bool Ecosistem::esteFinalizat() const {
    if (!populatie[indexJucator].esteVie()) {
        std::cout << "\n--- GAME OVER ---\nAi murit dupa " << tureSupravietuite << " ture.\n";
        return true;
    }
    if (verificareVictorie()) {
        std::cout << "\n--- VICTORIE! ---\nAi ajuns la coordonatele de finish (" 
                  << latime-1 << "," << inaltime-1 << ")!\n";
        return true;
    }
    return false;
}

void Ecosistem::afiseazaStatusJucator() const {
    std::cout << "Jucator: " << populatie[indexJucator] << "\n";
    std::cout << "Scop: Ajunge la (" << latime-1 << "," << inaltime-1 << ")\n";
}