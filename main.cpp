
#include <iostream>
#include <utility>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

class JurnalSimulare {
private:
    std::ofstream fisierLog;
    std::string numeFisier;

public:
    explicit JurnalSimulare(std::string nume = "log.txt")
        : numeFisier(std::move(nume)) {
        fisierLog.open(numeFisier, std::ios::app);
        if (fisierLog.is_open()) {
            fisierLog << "--- Sesiune noua de simulare inceputa ---\n";
        }
    }

    ~JurnalSimulare() {
        if (fisierLog.is_open()) {
            fisierLog << "--- Sesiune terminata ---\n\n";
            fisierLog.close();
        }
    }

    void log(const std::string& mesaj) {
        if (fisierLog.is_open()) {
            fisierLog << "[LOG]: " << mesaj << "\n";
        }
    }
};
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
    [[nodiscard]] std::string getNume() const { return nume; }

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



class Ecosistem {
private:
    int latime, inaltime;
    std::vector<Entitate> entitati;
    JurnalSimulare jurnal;

public:
    explicit Ecosistem(int l = 10, int i = 10) : latime(l), inaltime(i), jurnal("simulare_log.txt") {}

        ~Ecosistem() {
        std::cout << "Ecosistemul de " << latime << "x" << inaltime << " a fost inchis.\n";
    }
    void adaugaAnimal(const Entitate& e) {
        entitati.push_back(e);
        jurnal.log("A fost adaugata entitatea: " + e.getNume());
    }

    void incarcaDinFisier(const std::string& numeFisier) {
        jurnal.log("Inceperea incarcarii din fisier: " + numeFisier);
        std::ifstream f(numeFisier);
        if (!f.is_open()) {
            std::cout << "[Eroare] Nu am putut deschide " << numeFisier << ". Folosesc setari default.\n";
            return;
        }
        int nrEntitati;
        f >> latime >> inaltime >> nrEntitati;

        for (int i = 0; i < nrEntitati; ++i) {
            std::string nume;
            char simbol;
            int x, y, e;
            f >> nume >> simbol >> x >> y >> e;
            entitati.emplace_back(nume, simbol, x, y, e);
        }
        f.close();
        jurnal.log("Incarcare reusita. Latime: " + std::to_string(latime));
    }
    void actualizeaza() {
        for (auto& e : entitati) {
            int nx = e.getX() + (rand() % 3 - 1);
            int ny = e.getY() + (rand() % 3 - 1);
            if (nx >= 0 && nx < latime && ny >= 0 && ny < inaltime) {
                e.seDeplaseaza(nx, ny);
            }
        }
        jurnal.log("Tura procesata.");
    }

    void afiseaza() const {
        for (int i = 0; i < inaltime; ++i) {
            for (int j = 0; j < latime; ++j) {
                char s = '.';
                for (const auto& e : entitati) {
                    if (e.getX() == j && e.getY() == i) { s = e.getSimbol(); break; }
                }
                std::cout << s << " ";
            }
            std::cout << "\n";
        }
    }
};
int main() {
    srand(static_cast<unsigned>(time(nullptr)));
    std::cout << "===== Wildlife Architect v0.1 =====\n";

    Ecosistem padure;
    padure.incarcaDinFisier("tastatura.txt");

    std::cout << "Harta initiala (din fisier):\n";
    padure.afiseaza();

    std::cout << "\nSimulare in curs...\n";
    padure.actualizeaza();
    padure.afiseaza();

    return 0;
}