#include "Ecosistem.h"
#include <iostream>
#include <algorithm>
#include <fstream>

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
    adaugaEveniment("Harta a fost incarcata cu succes din " + numeFisier);
}

void Ecosistem::ruleazaTura() {
    // 1. Curățăm harta și desenăm entitățile vii
    reprezentare.curata();
    for (const auto& e : populatie) {
        if (e.esteVie()) {
            reprezentare.adauga(e.getX(), e.getY(), e.getSimbol());
        }
    }

    // 2. Afișăm harta și statusul jucătorului pe ecran
    reprezentare.afiseaza();
    afiseazaStatusJucator();

    // 3. Aplicăm logica de stare pentru TOATE entitățile
    for (auto& e : populatie) {
        if (e.esteVie()) {
            e.gestioneazaResurse();
            e.aplicaEfecteTura();
        }
    }

    // 4. Mișcarea Jucătorului (Manual)
    populatie[indexJucator].deplasareManual(latime, inaltime);

    // 5. Mișcarea celorlalte entități (AI)
    for (size_t i = 0; i < populatie.size(); ++i) {
        if (i == (size_t)indexJucator) continue; // Sărim peste jucător, el s-a mișcat deja
        populatie[i].urmaresteSauFuge(populatie, latime, inaltime);
    }

    // 6. Rezolvăm interacțiunile (Lupte, Familii, Reproducere)
    proceseazaInteractiuni();

    // 7. Afișăm jurnalul de evenimente sub hartă
    afiseazaIstoric();

    // 8. Incrementăm numărul de ture supraviețuite
    tureSupravietuite++;
}

void Ecosistem::proceseazaInteractiuni() {
    for (size_t i = 0; i < populatie.size(); ++i) {
        if (!populatie[i].esteVie()) continue;
        
        for (size_t j = 0; j < populatie.size(); ++j) {
            if (i == j || !populatie[j].esteVie()) continue;

            if (populatie[i].getX() == populatie[j].getX() && 
                populatie[i].getY() == populatie[j].getY()) {

                if (populatie[i].incearcaFamilie(populatie[j])) {
                    adaugaEveniment(populatie[i].getNume() + " a format o familie!");
                }
                if (populatie[i].incearcaReproducere(populatie)) {
                    adaugaEveniment("S-a nascut un pui nou!");
                }
                populatie[i].interactioneaza(populatie[j]);;
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
void Ecosistem::genereazaRaportFinal() const {
    if (populatie.empty()) {
        std::cout << "Nu exista entitati pentru raport.\n";
        return;
    }

    const Entitate* ceaMaiPuternica = &populatie[0];

    int nrPradatori = 0;
    int nrPrada = 0;

    for (const auto& e : populatie) {
        if (e.getTip() == TipEntitate::Pradator) nrPradatori++;
        if (e.getTip() == TipEntitate::Prada) nrPrada++;

        if (e.getStats().getPutere() > ceaMaiPuternica->getStats().getPutere()) {
            ceaMaiPuternica = &e;
        }
    }

    std::cout << "Pradatori: " << nrPradatori << " | Prazi: " << nrPrada << "\n";
    std::cout << "Cea mai puternica entitate: " << ceaMaiPuternica->getNume()
              << " (Putere: " << ceaMaiPuternica->getStats().getPutere() << ")\n";
    std::cout << "==========================================\n";
}
void Ecosistem::adaugaEveniment(const std::string& text) {
    std::string mesajComplet = "[Tura " + std::to_string(tureSupravietuite) + "] " + text;
    istoricEvenimente.push_back(mesajComplet);

    if (istoricEvenimente.size() > 5) {
        istoricEvenimente.erase(istoricEvenimente.begin());
    }
}

void Ecosistem::afiseazaIstoric() const {
    if (istoricEvenimente.empty()) return;

    std::cout << "\n--- JURNALUL ECOSISTEMULUI ---\n";
    for (const auto& ev : istoricEvenimente) {
        std::cout << ev << "\n";
    }
    std::cout << "------------------------------\n";
}
void Ecosistem::afiseazaStatusJucator() const {
    const auto& j = populatie[indexJucator];
    int distaX = std::abs((latime - 1) - j.getX());
    int distaY = std::abs((inaltime - 1) - j.getY());
    int distantaTotala = distaX + distaY;

    std::cout << "\n================ STATISTICI JUCATOR ================\n";
    std::cout << " Nume: " << j.getNume() << " | Simbol: " << j.getSimbol() << "\n";
    std::cout << " Energie: " << j.getStats().getEnergie() << " | Putere: " << j.getStats().getPutere() << "\n";
    std::cout << " Pozitie curenta: (" << j.getX() << ", " << j.getY() << ")\n";
    std::cout << " Distanta pana la tinta: " << distantaTotala << " pasi\n";
    if (distantaTotala < 5) std::cout << " [ALERTA] Esti foarte aproape de finish!\n";
    std::cout << "====================================================\n";
}

std::ostream& operator<<(std::ostream& os, const Ecosistem& eco) {
    os << "\n========================================\n";
    os << "   STARE SISTEM: " << eco.latime << "x" << eco.inaltime << "\n";
    os << "   Entitati vii: " << eco.populatie.size() << "\n";
    os << "   Ture scurse:  " << eco.tureSupravietuite << "\n";

    if (!eco.populatie.empty()) {
        os << "   Ultimul eveniment notabil: " << eco.populatie[0] << "\n";
    }
    os << "========================================\n";
    return os;
}