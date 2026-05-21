#include "../include/Pradator.hpp"
#include "../include/Prada.hpp"

Pradator::Pradator(int x, int y, int energie, std::string numeSpecie, char sex, int daune)
    : Animal(x, y, energie, numeSpecie, sex), dauneAtac(daune) {}

bool Pradator::esteAmenintare(const std::shared_ptr<Entitate>& alta) const {
    if (!alta) return false;

    auto altPradator = std::dynamic_pointer_cast<Pradator>(alta);

    if (altPradator) {
        return altPradator->calculeazaPutere() > this->calculeazaPutere();
    }

    return false;
}

bool Pradator::gasestePradaInJur(const MatriceHarta& harti, int& tintaX, int& tintaY) const {
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    int n = harti.size();

    for (int i = 0; i < 8; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
            auto ent = harti[nx][ny];
            if (ent && std::dynamic_pointer_cast<Prada>(ent)) {
                tintaX = nx;
                tintaY = ny;
                return true;
            }
        }
    }
    return false;
}