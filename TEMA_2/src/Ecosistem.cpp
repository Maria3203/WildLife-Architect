
#include "../include/Ecosistem.hpp"
#include "../include/SpeciiPradatori.hpp"
#include "../include/SpeciiPrazi.hpp"
#include "../include/SpeciiPlante.hpp"
#include "../include/Exceptii.hpp"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

void creeazaPuiAdiacent(const std::string& specie, int x, int y, MatriceHarta& harti, std::shared_ptr<Animal> jucator) {
    int dx[] = {-1, 1, 0, 0, -1, -1, 1, 1};
    int dy[] = {0, 0, -1, 1, -1, 1, -1, 1};
    char sexPui = (std::rand() % 2 == 0) ? 'M' : 'F';

    for (int i = 0; i < 8; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < harti.size() && ny >= 0 && ny < harti.size()) {
            if (!harti[nx][ny]) {
                if (specie == "Lup") harti[nx][ny] = std::make_shared<Lup>(nx, ny, sexPui);
                else if (specie == "Vulpe") harti[nx][ny] = std::make_shared<Vulpe>(nx, ny, sexPui);
                else if (specie == "Urs") harti[nx][ny] = std::make_shared<Urs>(nx, ny, sexPui);
                else if (specie == "Uliu") harti[nx][ny] = std::make_shared<Uliu>(nx, ny, sexPui);
                else if (specie == "Iepure") harti[nx][ny] = std::make_shared<Iepure>(nx, ny, sexPui);
                else if (specie == "Caprioara") harti[nx][ny] = std::make_shared<Caprioara>(nx, ny, sexPui);
                else if (specie == "Pasare") harti[nx][ny] = std::make_shared<Pasare>(nx, ny, sexPui);
                else if (specie == "Veverita") harti[nx][ny] = std::make_shared<Veverita>(nx, ny, sexPui);

                if (harti[nx][ny]) harti[nx][ny]->modificaEnergie(50);

                auto puiAnim = std::dynamic_pointer_cast<Animal>(harti[nx][ny]);
                if (puiAnim && jucator) {
                    jucator->adaugaPrieten(puiAnim->getId());
                    puiAnim->adaugaPrieten(jucator->getId());
                }

                std::cout << "\n[NATURA] Un pui nou de " << specie << " (" << sexPui << ") a fost nascut la pozitia (" << nx << "," << ny << ")!\n";
                return;
            }
        }
    }
    std::cout << "\n[NATURA] Nu s-a gasit spatiu liber in jur pentru nasterea puiului.\n";
}

void mutaCursorulLa(int rand, int coloana) { (void)rand; (void)coloana; }

void executaMiscareAleatorieAI(Animal* animal, const MatriceHarta& harti) {
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    int dir = std::rand() % 4;

    int n = harti.size();
    int nx = animal->getX() + dx[dir];
    int ny = animal->getY() + dy[dir];

    if (nx >= 0 && nx < harti.size() && ny >= 0 && ny < harti.size()) {
        auto tinta = harti[nx][ny];
        if (!tinta) {
            animal->setPozitie(nx, ny);
            animal->modificaEnergie(-1);
        } else {
            auto pl = std::dynamic_pointer_cast<Planta>(tinta);
            if (pl && std::dynamic_pointer_cast<Prada>(harti[animal->getX()][animal->getY()])) {
                animal->setPozitie(nx, ny);
                animal->modificaEnergie(pl->getBonusEnergie());
            }
        }
    }
}

Ecosistem::Ecosistem(int dim) : dimensiune(dim) {
    if (dim < 4) dimensiune = 20;
    harti.resize(dimensiune, std::vector<std::shared_ptr<Entitate>>(dimensiune, nullptr));
}

Ecosistem::Ecosistem(const Ecosistem& altul) : dimensiune(altul.dimensiune) {
    harti.resize(dimensiune, std::vector<std::shared_ptr<Entitate>>(dimensiune, nullptr));
    for (int i = 0; i < dimensiune; ++i) {
        for (int j = 0; j < dimensiune; ++j) {
            if (altul.harti[i][j]) {
                harti[i][j] = altul.harti[i][j]->clone();
            }
        }
    }
    if (altul.jucator) {
        jucator = std::dynamic_pointer_cast<Animal>(harti[altul.jucator->getX()][altul.jucator->getY()]);
    }
}

void swap(Ecosistem& primul, Ecosistem& alDoilea) noexcept {
    using std::swap;
    swap(primul.dimensiune, alDoilea.dimensiune);
    swap(primul.harti, alDoilea.harti);
    swap(primul.jucator, alDoilea.jucator);
}

Ecosistem& Ecosistem::operator=(Ecosistem altul) {
    swap(*this, altul); return *this;
}

void Ecosistem::curataEcranul() const {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void Ecosistem::initJoc(int categorieJoc, int selectieAnimal, char sexJucator) {
    if (categorieJoc != 1 && categorieJoc != 2) {
        throw ExceptieSetariJoc("Categoria jocului trebuie sa fie 1 (Pradator) sau 2 (Prada)!");
    }
    std::srand(std::time(nullptr));

    if (categorieJoc == 1) {
        switch (selectieAnimal) {
            case 1: jucator = std::make_shared<Lup>(0, 0, sexJucator); break;
            case 2: jucator = std::make_shared<Vulpe>(0, 0, sexJucator); break;
            case 3: jucator = std::make_shared<Urs>(0, 0, sexJucator); break;
            case 4: jucator = std::make_shared<Uliu>(0, 0, sexJucator); break;
            default: jucator = std::make_shared<Lup>(0, 0, sexJucator);
        }
    } else {
        switch (selectieAnimal) {
            case 1: jucator = std::make_shared<Iepure>(0, 0, sexJucator); break;
            case 2: jucator = std::make_shared<Caprioara>(0, 0, sexJucator); break;
            case 3: jucator = std::make_shared<Pasare>(0, 0, sexJucator); break;
            case 4: jucator = std::make_shared<Veverita>(0, 0, sexJucator); break;
            default: jucator = std::make_shared<Iepure>(0, 0, sexJucator);
        }
    }

    double sansaFlora = (categorieJoc == 2) ? 0.25 : 0.05;
    double sansaPrazi = (categorieJoc == 2) ? 0.05 : 0.25;
    double sansaPredatori = 0.05;

    for (int i = 0; i < dimensiune; ++i) {
        for (int j = 0; j < dimensiune; ++j) {
            if (i == 0 && j == 0) continue;
            if (i == dimensiune - 1 && j == dimensiune - 1) continue;

            double r = (double)std::rand() / RAND_MAX;
            char rSex = (std::rand() % 2 == 0) ? 'M' : 'F';

            double sansaPredatoriAjustata = sansaPredatori;
            if (categorieJoc == 2 && i <= 4 && j <= 4) sansaPredatoriAjustata = 0.0;

            if (r < sansaFlora) {
                int tipP = std::rand() % 3;
                if (tipP == 0) harti[i][j] = std::make_shared<FructBun>(i, j);
                else if (tipP == 1) harti[i][j] = std::make_shared<FructOtravitor>(i, j);
                else harti[i][j] = std::make_shared<Feriga>(i, j);
            }
            else if (r < sansaFlora + sansaPrazi) {
                int tipPr = std::rand() % 4;
                if (tipPr == 0) { harti[i][j] = std::make_shared<Iepure>(i, j, rSex); harti[i][j]->modificaEnergie(100); }
                else if (tipPr == 1) { harti[i][j] = std::make_shared<Caprioara>(i, j, rSex); harti[i][j]->modificaEnergie(100); }
                else if (tipPr == 2) { harti[i][j] = std::make_shared<Pasare>(i, j, rSex); harti[i][j]->modificaEnergie(100); }
                else { harti[i][j] = std::make_shared<Veverita>(i, j, rSex); harti[i][j]->modificaEnergie(100); }
            }
            else if (r < sansaFlora + sansaPrazi + sansaPredatoriAjustata) {
                int tipPred = std::rand() % 4;
                if (tipPred == 0) harti[i][j] = std::make_shared<Lup>(i, j, rSex);
                else if (tipPred == 1) harti[i][j] = std::make_shared<Vulpe>(i, j, rSex);
                else if (tipPred == 2) harti[i][j] = std::make_shared<Urs>(i, j, rSex);
                else harti[i][j] = std::make_shared<Uliu>(i, j, rSex);
            }
        }
    }

    harti[0][0] = jucator;
    jucator->setPozitie(0, 0);
    jucator->modificaEnergie(250);
}

void Ecosistem::afiseazaStatusJucator() const {
    std::cout << "=========================================================\n"
              << " STATUS JUCATOR: " << jucator->getNumeSpecie() << " (" << jucator->getSex() << ")\n"
              << " Energie Curenta: " << jucator->getEnergie() << " HP\n"
              << " Putere de Lupta: " << jucator->calculeazaPutere() << " puncte\n"
              << " Pozitie pe Harta: (" << jucator->getX() << "," << jucator->getY() << ")\n";
}

void Ecosistem::afiseazaHartaCurenta() const {
    bool esteModPrada = (std::dynamic_pointer_cast<Prada>(jucator) != nullptr);

    for (int i = 0; i < dimensiune; ++i) {
        for (int j = 0; j < dimensiune; ++j) {
            std::string cellStr;

            if (harti[i][j] && harti[i][j]->getId() == jucator->getId()) {
                cellStr = "[J]";
            }
            else if (harti[i][j]) {
                auto ent = harti[i][j];
                auto anim = std::dynamic_pointer_cast<Animal>(ent);
                std::ostringstream oss;
                oss << "[";
                ent->afiseaza(oss);

                if (anim && esteModPrada && std::dynamic_pointer_cast<Prada>(anim)) {
                    oss << anim->getSex();
                }
                oss << "]";
                cellStr = oss.str();
            }
            else if (i == dimensiune - 1 && j == dimensiune - 1) {
                cellStr = "[F]";
            }
            else {
                cellStr = ".";
            }
            std::cout << std::left << std::setw(6) << cellStr;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Ecosistem::actualizeazaCelulaPeEcran(int x, int y) { (void)x; (void)y; }
void Ecosistem::verificaVecinatatiJucator() { }

void Ecosistem::proceseazaTuraAI() {
    std::vector<int> entitatiProcesate;
    bool estePrada = (std::dynamic_pointer_cast<Prada>(jucator) != nullptr);
    int jX = jucator->getX();
    int jY = jucator->getY();
    bool predatorActivTuraAsta = false;

    for (int i = 0; i < dimensiune; ++i) {
        for (int j = 0; j < dimensiune; ++j) {
            auto ent = harti[i][j];
            if (ent && ent != jucator && ent->getId() != jucator->getId()) {

                if (std::find(entitatiProcesate.begin(), entitatiProcesate.end(), ent->getId()) != entitatiProcesate.end()) continue;

                int vechiX = i;
                int vechiY = j;

                if (estePrada && !std::dynamic_pointer_cast<Prada>(ent) && !std::dynamic_pointer_cast<Planta>(ent)) {
                    int distX = std::abs(vechiX - jX);
                    int distY = std::abs(vechiY - jY);

                    if (std::max(distX, distY) <= 4 && !predatorActivTuraAsta) {
                        predatorActivTuraAsta = true;
                        int pasAI = (ent->getEnergie() > 20) ? 2 : 1;

                        int dirX = 0; if (jX > vechiX) dirX = 1; else if (jX < vechiX) dirX = -1;
                        int dirY = 0; if (jY > vechiY) dirY = 1; else if (jY < vechiY) dirY = -1;

                        int nouX = std::max(0, std::min(dimensiune - 1, vechiX + (dirX * pasAI)));
                        int nouY = std::max(0, std::min(dimensiune - 1, vechiY + (dirY * pasAI)));

                        auto entitateTinta = harti[nouX][nouY];
                        if (!entitateTinta) {
                            harti[nouX][nouY] = ent; harti[vechiX][vechiY] = nullptr; ent->setPozitie(nouX, nouY);
                        } else if (entitateTinta->getId() == jucator->getId()) {
                            std::cout << "\n[DESTRUCTIE] Predatorul " << ent->getNumeSpecie() << " a sarit pe tine si te-a devorat!\n";
                            jucator->modificaEnergie(-jucator->getEnergie());
                            ent->setPozitie(vechiX, vechiY);
                        } else {
                            harti[nouX][nouY] = ent; harti[vechiX][vechiY] = nullptr; ent->setPozitie(nouX, nouY);
                        }

                        ent->modificaEnergie((pasAI == 2) ? -3 : -1);
                        entitatiProcesate.push_back(ent->getId());
                        continue;
                    }
                }

                ent->actioneaza(harti);
                entitatiProcesate.push_back(ent->getId());

                int nouX = ent->getX();
                int nouY = ent->getY();

                if (vechiX != nouX || vechiY != nouY) {
                    if (nouX >= 0 && nouX < dimensiune && nouY >= 0 && nouY < dimensiune) {
                        auto entitateTinta = harti[nouX][nouY];
                        if (!entitateTinta) {
                            harti[nouX][nouY] = ent; harti[vechiX][vechiY] = nullptr;
                        } else if (entitateTinta->getId() == jucator->getId()) {
                            if (estePrada) {
                                std::cout << "\n[DESTRUCTIE] Predatorul AI a dat peste tine din intamplare si te-a devorat!\n";
                                jucator->modificaEnergie(-jucator->getEnergie());
                            } else {
                                if (jucator->esteAmenintare(ent)) jucator->modificaEnergie(-15);
                                ent->setPozitie(vechiX, vechiY);
                            }
                        } else {
                            harti[nouX][nouY] = ent; harti[vechiX][vechiY] = nullptr;
                        }
                    } else {
                        ent->setPozitie(vechiX, vechiY);
                    }
                }
            }
        }
    }

    for (int i = 0; i < dimensiune; ++i) {
        for (int j = 0; j < dimensiune; ++j) {
            if (harti[i][j] && harti[i][j] != jucator && harti[i][j]->getId() != jucator->getId()) {
                if (harti[i][j]->getEnergie() <= 0) harti[i][j] = nullptr;
            }
        }
    }
}

void Ecosistem::ruleazaJoc() {
    bool jocInDesfasurare = true;
    int invPrey = 0;
    int invGoodFruit = 0;
    int invBadFruit = 0;
    bool estePrada = (std::dynamic_pointer_cast<Prada>(jucator) != nullptr);
    if (!jucator) {
        throw ExceptieLogicaJoc("Jucatorul nu a fost initializat! Apeleaza initJoc inainte.");
    }

    while (jocInDesfasurare) {
        curataEcranul();
        afiseazaStatusJucator();

        std::cout << " INVENTAR CURENT:\n";
        if (!estePrada) {
            std::cout << " -> Prazi capturate: " << invPrey << " disponibile\n";
        } else {
            std::cout << " -> Fructe Bune / Ferigi: " << invGoodFruit << "\n -> Fructe Otravitoare : " << invBadFruit << " (Momeala)\n";
        }
        std::cout << "=========================================================\n\n";

        afiseazaHartaCurenta();

        int jX = jucator->getX();
        int jY = jucator->getY();

        bool predatorInJur = false;
        if (estePrada) {
            for (int i = std::max(0, jX - 4); i <= std::min(dimensiune - 1, jX + 4); ++i) {
                for (int j = std::max(0, jY - 4); j <= std::min(dimensiune - 1, jY + 4); ++j) {
                    auto vecin = harti[i][j];
                    if (vecin && !std::dynamic_pointer_cast<Prada>(vecin) && !std::dynamic_pointer_cast<Planta>(vecin) && vecin->getId() != jucator->getId()) {
                        predatorInJur = true;
                    }
                }
            }
        }

        if (jucator->getEnergie() <= 0) {
            std::cout << "\n GAME OVER! Ai ramas fara energie (epuizare). Ecosistemul te-a invins.\n";
            break;
        }

        std::cout << "--- ACTIUNI: (W/A/S/D - Miscare, I - Consuma din Inventar, X - Iesire) ---\n";
        std::cout << "Alege actiunea: ";

        char optiune; std::cin >> optiune; optiune = std::toupper(optiune);
        int vechiX = jucator->getX(); int vechiY = jucator->getY();

        if (optiune == 'X') break;
        else if (optiune == 'I') {
            if (!estePrada && invPrey > 0) { invPrey--; jucator->modificaEnergie(50); std::cout << "\n[HRANA] Ai consumat o prada! (+50 HP)\n"; }
            else if (estePrada && invGoodFruit > 0) { invGoodFruit--; jucator->modificaEnergie(50); std::cout << "\n[HRANA] Ai consumat un fruct! (+50 HP)\n"; }
            else { std::cout << "\n[!] Rucsacul tau este gol!\n"; }
            std::cout << "Apasa ENTER..."; std::string dummy; std::getline(std::cin >> std::ws, dummy);
            continue;
        }
        else if (optiune == 'W' || optiune == 'A' || optiune == 'S' || optiune == 'D') {

            int pas = 1;
            if (estePrada && predatorInJur) {
                if (jucator->getEnergie() > 20) {
                    pas = 2; std::cout << "\n[SPRINT] Un predator e pe urmele tale! Alergi cu viteza dubla (Pas x2)!\n";
                } else {
                    pas = 1; std::cout << "\n[OBOSEALA CRITICA] Un predator te vaneaza, dar ai sub 20 HP! Epuizare!\n";
                }
            }

            int nX = vechiX, nY = vechiY;
            if (optiune == 'W') nX -= pas; if (optiune == 'S') nX += pas;
            if (optiune == 'A') nY -= pas; if (optiune == 'D') nY += pas;

            nX = std::max(0, std::min(dimensiune - 1, nX));
            nY = std::max(0, std::min(dimensiune - 1, nY));

            auto entitateTinta = harti[nX][nY];

            if (!entitateTinta) {
                harti[nX][nY] = jucator; harti[vechiX][vechiY] = nullptr;
                jucator->setPozitie(nX, nY); jucator->modificaEnergie((pas == 2) ? -3 : -1);
            }
            else {
                auto pl = std::dynamic_pointer_cast<Planta>(entitateTinta);
                auto targetAnimal = std::dynamic_pointer_cast<Animal>(entitateTinta);

                if (pl) {
                    if (estePrada) {
                        std::cout << "\n=========================================================\n";
                        bool esteOtravitor = (std::dynamic_pointer_cast<FructOtravitor>(pl) != nullptr);
                        if (esteOtravitor) {
                            std::cout << " [ATENTIE] Ai calcat pe un Fruct Otravitor!\n (M) - Il mananc (Pierzi HP!)\n (C) - Culeg in rucsac\n Alegere: ";
                        } else {
                            std::cout << " [CULEGERE] Ai gasit hrana!\n (M) - O mananc (+HP)\n (C) - Pun in inventar\n Alegere: ";
                        }
                        char dec; std::cin >> dec; dec = std::toupper(dec);
                        if (dec == 'C') {
                            if (esteOtravitor) invBadFruit++; else invGoodFruit++;
                            std::cout << "\n[INVENTAR] Stocat in rucsac!\n";
                        } else jucator->modificaEnergie(pl->getBonusEnergie());
                    } else jucator->modificaEnergie(-1);

                    harti[nX][nY] = jucator; harti[vechiX][vechiY] = nullptr;
                    jucator->setPozitie(nX, nY);
                    std::cout << "Apasa ENTER..."; std::string dummy; std::getline(std::cin >> std::ws, dummy);
                }
                else if (targetAnimal) {
                    if (jucator->estePrieten(targetAnimal->getId())) {
                        std::cout << "\n=========================================================\n";
                        if (targetAnimal->getNumeSpecie() == jucator->getNumeSpecie()) {
                            std::cout << " [REUNIUNE DE FAMILIE] Te-ai reintalnit cu un partener/pui!\n";
                            int eJucator = jucator->getEnergie(); int eTinta = targetAnimal->getEnergie(); int pTinta = targetAnimal->calculeazaPutere();
                            jucator->modificaEnergie(-(eJucator / 2));
                            jucator->modificaEnergie((eTinta / 2) + (pTinta / 2));
                            targetAnimal->modificaEnergie(eJucator / 2);
                            std::cout << " -> Oferit familiei: " << (eJucator / 2) << " HP.\n -> Absorbit: " << ((eTinta / 2) + (pTinta / 2)) << " vitalitate!\n";
                        } else {
                            std::cout << " [REVEDERE] Prietenul tau (" << targetAnimal->getNumeSpecie() << ") te ajuta!\n";
                            jucator->modificaEnergie(30); targetAnimal->modificaEnergie(-20);
                            if (!estePrada) { invPrey++; std::cout << " -> Primit +30 HP si 1 prada!\n"; }
                            else { invGoodFruit++; std::cout << " -> Primit +30 HP si 1 fruct!\n"; }
                        }
                        std::cout << "=========================================================\nApasa ENTER...";
                        std::string dummy; std::getline(std::cin >> std::ws, dummy);
                        continue;
                    }

                    bool aceeasiSpecie = (targetAnimal->getNumeSpecie() == jucator->getNumeSpecie());
                    bool sexOpus = (std::toupper(targetAnimal->getSex()) != std::toupper(jucator->getSex()));
                    bool aceeasiCategorie = (estePrada == (std::dynamic_pointer_cast<Prada>(targetAnimal) != nullptr));

                    if (aceeasiSpecie && sexOpus) {
                        std::cout << "\n---------------------------------------------------------\n [CURTARE] Partener (" << targetAnimal->getSex() << ")! Vrei sa curtezi? (D/N): ";
                        char decizieCurtare; std::cin >> decizieCurtare; decizieCurtare = std::toupper(decizieCurtare);

                        if (decizieCurtare == 'D') {
                            jucator->adaugaPrieten(targetAnimal->getId()); targetAnimal->adaugaPrieten(jucator->getId());
                            if (std::toupper(jucator->getSex()) == 'M') {
                                int hrana = (!estePrada) ? invPrey : invGoodFruit;
                                if (hrana < 2) std::cout << " [REFUZ] Nu ai 2 resurse pt curtare!\n";
                                else {
                                    std::cout << " [SUCCES] Ai oferit resurse!\n";
                                    if (!estePrada) invPrey -= 2; else invGoodFruit -= 2;
                                    creeazaPuiAdiacent(jucator->getNumeSpecie(), vechiX, vechiY, harti, jucator);
                                }
                            } else {
                                std::cout << " [SUCCES] Masculul ofera hrana!\n"; jucator->modificaEnergie(50);
                                creeazaPuiAdiacent(jucator->getNumeSpecie(), vechiX, vechiY, harti, jucator);
                            }
                        }
                        std::cout << "Apasa ENTER..."; std::string dummy; std::getline(std::cin >> std::ws, dummy);
                    }
                    else if (aceeasiCategorie) {
                        std::cout << "\n=========================================================\n [INSPECTIE] " << targetAnimal->getNumeSpecie() << " | E: " << targetAnimal->getEnergie() << " | P: " << targetAnimal->calculeazaPutere() << "\n (P) - Pace | (L) - LUPTA EXTREMA: ";
                        char conf; std::cin >> conf; conf = std::toupper(conf);

                        if (conf == 'P') {
                            jucator->adaugaPrieten(targetAnimal->getId()); targetAnimal->adaugaPrieten(jucator->getId());
                            std::cout << "\n[DIPLOMATIE] Pact incheiat!\n";
                        } else {
                            if (jucator->calculeazaPutere() >= targetAnimal->calculeazaPutere()) {
                                int eFurt = targetAnimal->getEnergie(); jucator->modificaEnergie(eFurt);
                                if (!estePrada) { int pFurt = std::rand() % 3 + 1; invPrey += pFurt; std::cout << "\n[VICTORIE] Absorbit +" << eFurt << " HP si +" << pFurt << " prazi!\n"; }
                                else { int fFurt = std::rand() % 2 + 1; invGoodFruit += fFurt; std::cout << "\n[VICTORIE] Absorbit +" << eFurt << " HP si +" << fFurt << " fructe!\n"; }
                                harti[nX][nY] = jucator; harti[vechiX][vechiY] = nullptr; jucator->setPozitie(nX, nY);
                            } else {
                                std::cout << "\n[DEFEAT] Ai pierdut 80 HP!\n"; jucator->modificaEnergie(-80);
                            }
                        }
                        std::cout << "Apasa ENTER..."; std::string dummy; std::getline(std::cin >> std::ws, dummy);
                    }
                    else {
                        if (estePrada) {
                            if (invBadFruit > 0) {
                                invBadFruit--; harti[nX][nY] = jucator; harti[vechiX][vechiY] = nullptr; jucator->setPozitie(nX, nY);
                                std::cout << "\n[TACTICA] Ai otravit predatorul!\n";
                            } else {
                                std::cout << "\n[DECES] Ai fost devorat!\n"; jucator->modificaEnergie(-jucator->getEnergie());
                            }
                            std::cout << "Apasa ENTER..."; std::string dummy; std::getline(std::cin >> std::ws, dummy);
                        } else {
                            std::cout << "\n[VANATOARE] Prins " << targetAnimal->getNumeSpecie() << "!\n (M) - Mananc (+50) | (I) - Rucsac\nAlegere: ";
                            char dec; std::cin >> dec; dec = std::toupper(dec);
                            if (dec == 'I') invPrey++; else jucator->modificaEnergie(50);
                            harti[nX][nY] = jucator; harti[vechiX][vechiY] = nullptr; jucator->setPozitie(nX, nY);
                        }
                    }
                }
            }
        }

        if (jucator->getX() == dimensiune - 1 && jucator->getY() == dimensiune - 1) {
            std::cout << "\n=========================================================\n [VICTORIE ABSOLUTA] Ai ajuns la Finish [F]!\n -> Energie ramasa: " << jucator->getEnergie() << " HP\n -> Putere: " << jucator->calculeazaPutere() << " pct\n=========================================================\nApasa ENTER...";
            std::string dummy; std::getline(std::cin >> std::ws, dummy); break;
        }

        proceseazaTuraAI();

        if (jucator->getEnergie() <= 0) {
            std::cout << "\n=========================================================\n GAME OVER FATAL! Ucis in tura inamicilor!\n=========================================================\n Apasa ENTER...";
            std::string dummy; std::getline(std::cin >> std::ws, dummy); break;
        }
    }
}

void Lup::actioneaza(const MatriceHarta& harti) {
    int tx = this->getX(), ty = this->getY(); bool gasitPradaLocala = false;
    int dx[] = {-1, 1, 0, 0}; int dy[] = {0, 0, -1, 1};
    for (int dir = 0; dir < 4; ++dir) {
        int nx = this->getX() + dx[dir]; int ny = this->getY() + dy[dir];
        if (nx >= 0 && nx < harti.size() && ny >= 0 && ny < harti.size()) {
            if (harti[nx][ny] && std::dynamic_pointer_cast<Prada>(harti[nx][ny])) { tx = nx; ty = ny; gasitPradaLocala = true; break; }
        }
    }
    if (gasitPradaLocala) { this->setPozitie(tx, ty); this->modificaEnergie(15); this->acumuleazaExperienta(5); }
    else executaMiscareAleatorieAI(this, harti);
    this->imbatraneste();
}

void Vulpe::actioneaza(const MatriceHarta& harti) {
    int tx = this->getX(), ty = this->getY(); bool gasitPradaLocala = false;
    int dx[] = {-1, 1, 0, 0}; int dy[] = {0, 0, -1, 1};
    for (int dir = 0; dir < 4; ++dir) {
        int nx = this->getX() + dx[dir]; int ny = this->getY() + dy[dir];
        if (nx >= 0 && nx < harti.size() && ny >= 0 && ny < harti.size()) {
            if (harti[nx][ny] && std::dynamic_pointer_cast<Prada>(harti[nx][ny])) { tx = nx; ty = ny; gasitPradaLocala = true; break; }
        }
    }
    if (gasitPradaLocala) { this->setPozitie(tx, ty); this->modificaEnergie(10); } else executaMiscareAleatorieAI(this, harti);
    this->imbatraneste();
}

void Urs::actioneaza(const MatriceHarta& harti) {
    int tx = this->getX(), ty = this->getY(); bool gasitPradaLocala = false;
    int dx[] = {-1, 1, 0, 0}; int dy[] = {0, 0, -1, 1};
    for (int dir = 0; dir < 4; ++dir) {
        int nx = this->getX() + dx[dir]; int ny = this->getY() + dy[dir];
        if (nx >= 0 && nx < static_cast<int>(harti.size()) && ny >= 0 && ny < static_cast<int>(harti.size())) {
            if (harti[nx][ny] && std::dynamic_pointer_cast<Prada>(harti[nx][ny])) { tx = nx; ty = ny; gasitPradaLocala = true; break; }
        }
    }
    if (gasitPradaLocala) { this->setPozitie(tx, ty); this->modificaEnergie(25); } else executaMiscareAleatorieAI(this, harti);
    this->imbatraneste();
}

void Uliu::actioneaza(const MatriceHarta& harti) {
    int tx = this->getX(), ty = this->getY(); bool gasitPradaLocala = false;
    int dx[] = {-1, 1, 0, 0}; int dy[] = {0, 0, -1, 1};
    for (int dir = 0; dir < 4; ++dir) {
        int nx = this->getX() + dx[dir]; int ny = this->getY() + dy[dir];
        if (nx >= 0 && nx < static_cast<int>(harti.size()) && ny >= 0 && ny < static_cast<int>(harti.size())) {
            if (harti[nx][ny] && std::dynamic_pointer_cast<Prada>(harti[nx][ny])) { tx = nx; ty = ny; gasitPradaLocala = true; break; }
        }
    }
    if (gasitPradaLocala) { this->setPozitie(tx, ty); this->modificaEnergie(12); } else executaMiscareAleatorieAI(this, harti);
    this->imbatraneste();
}

void Iepure::actioneaza(const MatriceHarta& harti) { actualizeazaOboseala(); if (esteObosita) return; executaMiscareAleatorieAI(this, harti); this->imbatraneste(); }
void Caprioara::actioneaza(const MatriceHarta& harti) { actualizeazaOboseala(); if (esteObosita) return; executaMiscareAleatorieAI(this, harti); this->imbatraneste(); }
void Pasare::actioneaza(const MatriceHarta& harti) { actualizeazaOboseala(); if (esteObosita) return; executaMiscareAleatorieAI(this, harti); this->imbatraneste(); }
void Veverita::actioneaza(const MatriceHarta& harti) { actualizeazaOboseala(); if (esteObosita) return; executaMiscareAleatorieAI(this, harti); this->imbatraneste(); }