#include <iostream>
#include <string>
#include "include/Ecosistem.hpp"

int main() {
    char alegereReplay;

    do {
#ifdef _WIN32
        std::system("cls");
#else
        std::system("clear");
#endif

        std::cout << "=== BINE AI VENIT IN SIMULATORUL DE ECOSISTEM ===\n";

        int categorieJoc;
        int selectieAnimal;
        char sexJucator;

        std::cout << "Alege categoria (1 - Pradator, 2 - Prada): ";
        std::cin >> categorieJoc;

        if (categorieJoc == 1) {
            std::cout << "Alege animal (1-Lup, 2-Vulpe, 3-Urs, 4-Uliu): ";
        } else {
            std::cout << "Alege animal (1-Iepure, 2-Caprioara, 3-Pasare, 4-Veverita): ";
        }
        std::cin >> selectieAnimal;

        std::cout << "Alege sexul (M / F): ";
        std::cin >> sexJucator;
        sexJucator = std::toupper(sexJucator);

        Ecosistem eco(20);
        eco.initJoc(categorieJoc, selectieAnimal, sexJucator);

        eco.ruleazaJoc();

        std::cout << "\n=========================================================\n";
        std::cout << " Vrei sa joci din nou o runda noua? (D/N): ";
        std::cin >> alegereReplay;
        alegereReplay = std::toupper(alegereReplay);

    } while (alegereReplay == 'D');

    std::cout << "\n[!] Ecosistemul a fost inchis. La revedere!\n";
    return 0;
}