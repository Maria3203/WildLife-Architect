#include "../include/Pradator.hpp"
#include "../include/SpeciiPradatori.hpp"
#include <cmath>
Pradator::Pradator(int x, int y, int energie, const std::string& numeSpecie, char sex, int daune)
    : Animal(x, y, energie, numeSpecie, sex), dauneAtac(daune) {
}
void Pradator::actioneazaPradatorStandard(const MatriceHarta& harti, int bonusEnergieAtac, int bonusExperienta) {
    int tx = this->getX();
    int ty = this->getY();
    bool gasitPradaLocala = false;

    const int dx[] = {-1, 1, 0, 0};
    const int dy[] = {0, 0, -1, 1};

    for (int dir = 0; dir < 4; ++dir) {
        int nx = this->getX() + dx[dir];
        int ny = this->getY() + dy[dir];

        if (nx >= 0 && nx < static_cast<int>(harti.size()) && ny >= 0 && ny < static_cast<int>(harti.size())) {
            if (harti[nx][ny] && harti[nx][ny]->estePrada()) {
                tx = nx;
                ty = ny;
                gasitPradaLocala = true;
                break;
            }
        }
    }

    if (gasitPradaLocala) {
        this->setPozitie(tx, ty);
        this->modificaEnergie(bonusEnergieAtac);
        if (bonusExperienta > 0) {
            this->acumuleazaExperienta(bonusExperienta);
        }
    } else {
        executaMiscareAleatorieAI( harti);
    }

    this->imbatraneste();
}
bool Pradator::esteAmenintare(const std::shared_ptr<Entitate>& alta) const {
    return true;
}
void Lup::actioneaza(const MatriceHarta& harti) {
    this->actioneazaPradatorStandard(harti, 15, 5);
}

// --- VULPE ---
void Vulpe::actioneaza(const MatriceHarta& harti) {
    this->actioneazaPradatorStandard(harti, 10, 0);
}

// --- URS ---
void Urs::actioneaza(const MatriceHarta& harti) {
    this->actioneazaPradatorStandard(harti, 25, 0);
}

// --- ULIU ---
void Uliu::actioneaza(const MatriceHarta& harti) {
    this->actioneazaPradatorStandard(harti, 20, 5);
}