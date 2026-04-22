#include "Ecosistem.h"
#include <iostream>
#include <ctime>
#include <limits>

void afiseazaMeniu() {
    std::cout << "========================================\n";
    std::cout << "       WILDLIFE ARCHITECT v0.1          \n";
    std::cout << "========================================\n";
    std::cout << "Scop: Ajunge in coltul opus (19, 9)!\n";
    std::cout << "Controale: w, a, s, d + Enter\n\n";
    std::cout << "Alege modul de joc:\n";
    std::cout << "1. Mod PRADATOR (Lup)\n";
    std::cout << "2. Mod PRADA (Iepure)\n";
    std::cout << "Optiunea ta: ";
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    afiseazaMeniu();
    int optiune;

    if (!(std::cin >> optiune)) {
        optiune = 1;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Ecosistem padure(20, 10);
    padure.incarcaHarta("date.txt", optiune);

    while (!padure.esteFinalizat()) {
        std::cout << padure << std::endl;
        padure.ruleazaTura();
    }
    padure.genereazaRaportFinal();

    std::cout << "========================================\n";
    std::cout << "     JOC TERMINAT!                      \n";
    std::cout << "========================================\n";

    return 0;
}