#ifndef OOP_SPECIIPRADATORI_HPP
#define OOP_SPECIIPRADATORI_HPP
#include "Pradator.hpp"
#include <ostream>
#include <string>

class Lup : public Pradator {
public:
    Lup(int x, int y, char sex) : Pradator(x, y, 100, "Lup", sex, 30) {}

    void afiseaza(std::ostream& os) const override {
        os << (this->getSex() == 'M' ? "LM" : "LF");
    }

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

#endif