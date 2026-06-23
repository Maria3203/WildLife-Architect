#ifndef OOP_SPECIIPRAZI_HPP
#define OOP_SPECIIPRAZI_HPP

#include "Prada.hpp"
#include <ostream>
#include <string>

class Iepure : public Prada {
public:
    Iepure(int x, int y, char sex) : Prada(x, y, 50, "Iepure", sex) {}

    void afiseaza(std::ostream& os) const override {
        os << "ie";
    }

    std::shared_ptr<Entitate> clone() const override {
        return std::shared_ptr<Entitate>(new Iepure(*this));
    }
    void actualizeazaOboseala() override;

    void actioneaza(const MatriceHarta& harti) override;
};

class Caprioara : public Prada {
public:

    Caprioara(int x, int y, char sex) : Prada(x, y, 90, "Caprioara", sex) {}

    void afiseaza(std::ostream& os) const override {
        os << "ca";
    }

    std::shared_ptr<Entitate> clone() const override {
        return std::shared_ptr<Entitate>(new Caprioara(*this));
    }
    void actualizeazaOboseala() override;

    void actioneaza(const MatriceHarta& harti) override;
};
class Pasare : public Prada {
public:
    // Prăzile au doar 5 parametri la constructor
    Pasare(int x, int y, char sex) : Prada(x, y, 40, "Pasare", sex) {}

    void afiseaza(std::ostream& os) const override {
        os << "pa";
    }

    std::shared_ptr<Entitate> clone() const override {
        return std::shared_ptr<Entitate>(new Pasare(*this));
    }

    void actualizeazaOboseala() override;
    void actioneaza(const MatriceHarta& harti) override;
};

class Veverita : public Prada {
public:
    Veverita(int x, int y, char sex) : Prada(x, y, 45, "Veverita", sex) {}

    void afiseaza(std::ostream& os) const override {
        os << "ve";
    }

    std::shared_ptr<Entitate> clone() const override {
        return std::shared_ptr<Entitate>(new Veverita(*this));
    }

    void actualizeazaOboseala() override;
    void actioneaza(const MatriceHarta& harti) override;

};
#endif
