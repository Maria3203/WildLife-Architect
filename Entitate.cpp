#include "Entitate.h"

class Pozitie {
public:
    int x, y;
    Pozitie(int _x, int _y) : x(_x), y(_y) {}
};

Entitate::Entitate(std::string n, char s, TipEntitate t, int x, int y, Statistici st)
    : nume(n), simbol(s), tip(t), stats(st) {
    pos = new Pozitie(x, y);
}

Entitate::~Entitate() { delete pos; }

Entitate::Entitate(const Entitate& alta) : nume(alta.nume), simbol(alta.simbol), tip(alta.tip), stats(alta.stats), inventar(alta.inventar) {
    pos = new Pozitie(alta.pos->x, alta.pos->y);
}

Entitate& Entitate::operator=(const Entitate& alta) {
    if (this != &alta) {
        delete pos;
        nume = alta.nume; simbol = alta.simbol; tip = alta.tip;
        stats = alta.stats; inventar = alta.inventar;
        pos = new Pozitie(alta.pos->x, alta.pos->y);
    }
    return *this;
}

void Entitate::deplasareManual(int maxW, int maxH) {
    char tasta;
    std::cout << "\n[" << nume << "] (Viteza " << stats.getViteza() << ") WASD: ";
    std::cin >> tasta;

    int v = stats.getViteza();
    int nx = pos->x, ny = pos->y;

    if (tasta == 'w') ny -= v;
    if (tasta == 's') ny += v;
    if (tasta == 'a') nx -= v;
    if (tasta == 'd') nx += v;

    pos->x = std::max(0, std::min(maxW - 1, nx));
    pos->y = std::max(0, std::min(maxH - 1, ny));

    stats.modificaEnergie(-5);
    stats.imbatraneste();
}

void Entitate::interactioneaza(Entitate& alta) {
    if (this->tip == TipEntitate::Pradator && alta.tip == TipEntitate::Prada) {
        this->stats.modificaEnergie(30);
        alta.stats.modificaEnergie(-200); // Victima moare
        this->inventar.push_back("Hrana_de_la_" + alta.nume);
    }
    else if (this->tip == TipEntitate::Pradator && alta.tip == TipEntitate::Pradator) {
        if (this->stats.getPutere() > alta.stats.getPutere()) {
            alta.stats.modificaEnergie(-40);
        } else {
            this->stats.modificaEnergie(-40);
        }
    }
}
void Entitate::deplasareAI(int maxW, int maxH) {
    if (tip == TipEntitate::Planta) return;

    int v = stats.getViteza();
    int dx = (rand() % 3 - 1) * v; // se misca -v, 0 sau v
    int dy = (rand() % 3 - 1) * v;

    int nx = pos->x + dx;
    int ny = pos->y + dy;

    pos->x = std::max(0, std::min(maxW - 1, nx));
    pos->y = std::max(0, std::min(maxH - 1, ny));

    stats.modificaEnergie(-1);
    stats.imbatraneste();
}
bool Entitate::incearcaFamilie(Entitate& partener) {
    if (this->tip == partener.tip &&
        this->stats.getGen() != partener.stats.getGen() &&
        this->stats.getGen() != Gen::Nedeterminat &&
        partener.stats.getGen() != Gen::Nedeterminat &&
        !this->stats.hasFamily() && !partener.stats.hasFamily()) {

        this->stats.setFamilie(true);
        partener.stats.setFamilie(true);
        return true;
        }
    return false;
}

int Entitate::getX() const { return pos->x; }
int Entitate::getY() const { return pos->y; }

std::ostream& operator<<(std::ostream& os, const Entitate& e) {
    os << "[" << e.simbol << "] " << e.nume << " | P:" << e.stats.getPutere()
       << " | Vst:" << e.stats.getVarsta() << " | Inv:" << e.inventar.size();
    return os;
}