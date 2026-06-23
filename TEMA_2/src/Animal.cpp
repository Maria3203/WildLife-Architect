#include "../include/Animal.hpp"
#include <algorithm>
#include <string>

Animal::Animal(int x, int y, int energie, const std::string &numeSpecie_param, char sex_param)
    : Entitate(x, y, energie, numeSpecie_param), // <--- SCHIMBAREA ESTE AICI: Trimitem 4 parametri bazei
      sex(sex_param),
      experienta(0),
      varsta(0) {
}
void Animal::executaMiscareAleatorieAI(const MatriceHarta& harti) {
    const int dx[] = {-1, 1, 0, 0};
    const int dy[] = {0, 0, -1, 1};
    int dir = std::rand() % 4;

    int nx = this->getX() + dx[dir];
    int ny = this->getY() + dy[dir];

    if (nx >= 0 && nx < static_cast<int>(harti.size()) && ny >= 0 && ny < static_cast<int>(harti.size())) {
        auto tinta = harti[nx][ny];
        if (!tinta) {
            this->setPozitie(nx, ny);
            this->modificaEnergie(-1);
        } else {
            // VERIFICARE POLIMORFICA FARA DYNAMIC CAST
            if (tinta->estePlanta() && harti[this->getX()][this->getY()]->estePrada()) {
                this->setPozitie(nx, ny);
                this->modificaEnergie(tinta->getBonusEnergie());
            }
        }
    }
}

bool Animal::estePrieten(int idCautat) const {
    return std::find(listaPrieteni.begin(), listaPrieteni.end(), idCautat) != listaPrieteni.end();
}


void Animal::adaugaPrieten(int idAdaugat) {
    if (!estePrieten(idAdaugat)) {
        listaPrieteni.push_back(idAdaugat);
    }
}
void Animal::imbatraneste() {
    this->varsta++;

}

void Animal::acumuleazaExperienta(int exp) {
    this->experienta += exp;
}

