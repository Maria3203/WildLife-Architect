
#include <iostream>
#include <utility>

enum TipEntitate {
    PRADATOR, PRADA, PLANTA
};

class Pozitie {
private:
    int x;
    int y;

public:
    explicit Pozitie(int valX = 0, int valY = 0) : x(valX), y(valY) {}
    [[nodiscard]] int getX() const { return x; }
    [[nodiscard]]int getY() const { return y; }

    friend std::ostream& operator<<(std::ostream& consola, const Pozitie& p) {
        consola << "[" << p.x << ":" << p.y << "]";
        return consola;
    }
};

class Statistici {
private:
    int energie;
    int foame;

public:
    explicit Statistici(int e = 100, int f = 0) {
        energie = e;
        foame = f;
    }

    void consumaEnergie(int cantitate) {
        energie -= cantitate;
        if (energie < 0) energie = 0;
    }

    friend std::ostream& operator<<(std::ostream& consola, const Statistici& s) {
        consola << "[E:" << s.energie << "% | F:" << s.foame << "]";
        return consola;
    }
};

class Entitate {
private:
    std::string nume;
    char simbol;
    Pozitie pos;
    Statistici stats;

public:
    [[nodiscard]] int getX() const { return pos.getX(); }
    [[nodiscard]] int getY() const { return pos.getY(); }
    [[nodiscard]] char getSimbol() const { return simbol; }

    Entitate(std::string n, char s, int x, int y, int e)
        : nume(std::move(n)), simbol(s), pos(x, y), stats(e) {}

    Entitate(const Entitate& alta)
       : nume(alta.nume + "_copie"),
         simbol(alta.simbol),
         pos(alta.pos),
         stats(alta.stats)
   {
        std::cout << "[Log] Constructor de copiere apelat pentru " << alta.nume << "\n";
   }


    Entitate& operator=(const Entitate& alta) {
        std::cout << "[Log] Operator= apelat pentru " << alta.nume << "\n";
        if (this != &alta) {
            this->nume = alta.nume;
            this->simbol = alta.simbol;
            this->pos = alta.pos;
            this->stats = alta.stats;
        }
        return *this;
    }

    ~Entitate() {
        std::cout << "[Log] Destructor apelat pentru " << nume << "\n";
    }

    void seDeplaseaza(int nouX, int nouY) {
        std::cout << "--- " << nume << " se misca spre (" << nouX << "," << nouY << ") ---\n";
        pos = Pozitie(nouX, nouY);
        stats.consumaEnergie(10);
    }


    friend std::ostream& operator<<(std::ostream& consola, const Entitate& e) {
        consola << "Entitate: " << e.nume << " [" << e.simbol << "]\n"
                << "  Locatie: " << e.pos << "\n"
                << "  Status:  " << e.stats << "\n";
        return consola;
    }
};

#include <vector>

class Ecosistem {
private:
    int latime, inaltime;
    std::vector<Entitate> entitati;

public:
    Ecosistem(int l, int i) : latime(l), inaltime(i) {}

    void adaugaAnimal(const Entitate& e) {
        entitati.push_back(e);
    }

    void afiseazaLumea() const {
        for (int i = 0; i < inaltime; ++i) {
            for (int j = 0; j < latime; ++j) {
                char simbol = '.';
                for (const auto& e : entitati) {
                    if (e.getX() == j && e.getY() == i) {
                        simbol = e.getSimbol();
                        break;
                    }
                }
                std::cout << simbol << " ";
            }
            std::cout << "\n";
        }
    }
};
int main() {
    std::cout << "===== Wildlife Architect v0.1 =====\n\n";

    Ecosistem padure(10, 10);
    Entitate lup("Lupul Alpha", 'L', 2, 3, 100);
    Entitate iepure("Bugs Bunny", 'I', 5, 5, 50);

    padure.adaugaAnimal(lup);
    padure.adaugaAnimal(iepure);

    std::cout << "Harta Ecosistemului:\n";
    padure.afiseazaLumea();

    std::cout << "\nDetalii lup inainte de miscare:\n" << lup;
    lup.seDeplaseaza(4, 5);

    return 0;
}