#include "Pradator.hpp"
#include <ostream>
#include <string>

class Lup : public Pradator {
public: // <-- Mutat afiseaza in public ca sa poata fi apelata de Ecosistem
    Lup(int x, int y, char sex) : Pradator(x, y, 100, "Lup", sex, 30) {}

    // Eroarea 1 rezolvata: redenumit in 'afiseaza'
    // Eroarea 2 rezolvata: folosit this->getSex() (asigura-te ca in Animal.hpp e const!)
    void afiseaza(std::ostream& os) const override {
        os << (this->getSex() == 'M' ? "LM" : "LF");
    }

    // Eroarea 3 rezolvata: fallback la new pentru clonare sigura
    std::shared_ptr<Entitate> clone() const override {
        return std::shared_ptr<Entitate>(new Lup(*this));
    }

    void actioneaza(const MatriceHarta& harti) override;
};

class Vulpe : public Pradator {
public:
    Vulpe(int x, int y, char sex) : Pradator(x, y, 80, "Vulpe", sex, 15) {}

    void afiseaza(std::ostream& os) const override {
        os << (this->getSex() == 'M' ? "VM" : "VF");
    }

    std::shared_ptr<Entitate> clone() const override {
        return std::shared_ptr<Entitate>(new Vulpe(*this));
    }

    void actioneaza(const MatriceHarta& harti) override;
};
class Urs : public Pradator {
public:
    // Parametrii bazei: x, y, energie, nume, sex, daune
    Urs(int x, int y, char sex) : Pradator(x, y, 150, "Urs", sex, 40) {}

    void afiseaza(std::ostream& os) const override {
        os << (this->getSex() == 'M' ? "UM" : "UF");
    }

    std::shared_ptr<Entitate> clone() const override {
        return std::shared_ptr<Entitate>(new Urs(*this));
    }

    void actioneaza(const MatriceHarta& harti) override;
};

class Uliu : public Pradator {
public:
    Uliu(int x, int y, char sex) : Pradator(x, y, 60, "Uliu", sex, 20) {}

    void afiseaza(std::ostream& os) const override {
        os << (this->getSex() == 'M' ? "uM" : "uF");
    }

    std::shared_ptr<Entitate> clone() const override {
        return std::shared_ptr<Entitate>(new Uliu(*this));
    }

    void actioneaza(const MatriceHarta& harti) override;
};