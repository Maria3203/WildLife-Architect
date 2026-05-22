#include <iostream>
#include <string>
#include "include/Ecosistem.hpp"
#include "../include/Exceptii.hpp"

int main() {
    char alegereReplay;

    do {
#ifdef _WIN32
        std::system("cls");
#else
        std::system("clear");
#endif

        std::cout << "=== WILDLIFE ARCHITECT ===\n";

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
    try {
        // Aici cream ecosistemul (poți testa cu dim = 3 ca să vezi cum pică pe catch)
        Ecosistem eco(20);

        eco.initJoc(1, 1, 'M'); // 1 = Pradator, 1 = Lup
        eco.ruleazaJoc();

    } catch (const ExceptieSetariJoc& e) {
        std::cerr << "\n[EROARE FATALA INIT] " << e.what() << "\nJocul se va inchide.\n";
    } catch (const ExceptieLogicaJoc& e) {
        std::cerr << "\n[EROARE FATALA LOGICA] " << e.what() << "\nJocul se va inchide.\n";
    } catch (const EcosistemException& e) {
        std::cerr << "\n[EROARE JOC] " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "\n[EROARE STANDARD] " << e.what() << "\n";
    }
    return 0;
}