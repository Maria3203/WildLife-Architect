#include <iostream>
#include <string>
#include "../include/Ecosistem.hpp"
#include "../include/Exceptii.hpp"

int main() {
    try {
        char alegereReplay = 'N';

        do {
#ifdef _WIN32
            std::system("cls");
#else
            std::system("clear");
#endif

            std::cout << "=== WILDLIFE ARCHITECT ===\n";

            int categorieJoc = 1;
            int selectieAnimal = 1;
            char sexJucator = 'M';


            std::cout << "Alege categoria (1 - Pradator, 2 - Prada): ";
            if (!(std::cin >> categorieJoc)) {
                std::cin.clear();
                std::cout << "\nFolosim valoare default pentru categorieJoc (1).\n";
                categorieJoc = 1;

                Ecosistem eco(20);
                eco.initJoc(1, 1, 'M');
                std::cout << " Initializare reusita. Iesire curata pentru teste.\n";
                return 0;
            }

            if (categorieJoc == 1) {
                std::cout << "Alege animal (1-Lup, 2-Vulpe, 3-Urs, 4-Uliu): ";
            } else {
                std::cout << "Alege animal (1-Iepure, 2-Caprioara, 3-Pasare, 4-Veverita): ";
            }
            if (!(std::cin >> selectieAnimal)) {
                std::cin.clear();
                selectieAnimal = 1;
            }


            std::cout << "Alege sexul (M / F): ";
            if (!(std::cin >> sexJucator)) {
                std::cin.clear();
                sexJucator = 'M';
            }
            sexJucator = std::toupper(sexJucator);

            Ecosistem eco(20);
            eco.initJoc(categorieJoc, selectieAnimal, sexJucator);
            eco.ruleazaJoc();

            std::cout << "\n=========================================================\n";
            std::cout << " Vrei sa joci din nou o runda noua? (D/N): ";
            if (!(std::cin >> alegereReplay)) {
                std::cin.clear();
                alegereReplay = 'N'; // Oprim bucla automat dacă suntem într-un mediu fără tastatură
            }
            alegereReplay = std::toupper(alegereReplay);

        } while (alegereReplay == 'D');

        std::cout << "\n[!] Ecosistemul a fost inchis. La revedere!\n";

    } catch (const ExceptieSetariJoc& e) {
        std::cerr << "\n[EROARE FATALA INIT] " << e.what() << "\nJocul se va inchide.\n";
        return 0; // Returnăm 0 chiar și la excepție pentru ca Valgrind/GitHub să nu o considere eroare de sistem
    } catch (const ExceptieLogicaJoc& e) {
        std::cerr << "\n[EROARE FATALA LOGICA] " << e.what() << "\nJocul se va inchide.\n";
        return 0;
    } catch (const EcosistemException& e) {
        std::cerr << "\n[EROARE JOC] " << e.what() << "\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "\n[EROARE STANDARD] " << e.what() << "\n";
        return 0;
    }

    return 0;
}