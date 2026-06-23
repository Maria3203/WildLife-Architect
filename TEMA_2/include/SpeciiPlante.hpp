#ifndef OOP_SPECIIPLANTE_HPP
#define OOP_SPECIIPLANTE_HPP

#include "Planta.hpp"
#include <ostream>
#include <string>

class Feriga : public Planta {
public: // <-- Mutat totul in public
    Feriga(int x, int y) : Planta(x, y, 10, "Feriga", 15, false) {}

    // Redenumit si corectat
    void afiseaza(std::ostream& os) const override { os << "Fe"; }

    // Corectat clonarea
    std::shared_ptr<Entitate> clone() const override {
        return std::shared_ptr<Entitate>(new Feriga(*this));
    }
};

class FructBun : public Planta {
protected:
    void afiseaza(std::ostream& os) const override { os << "FB"; }
public:
    FructBun(int x, int y) : Planta(x, y, 15, "Fruct Bun", 30, false) {}
    std::shared_ptr<Entitate> clone() const override { return std::make_shared<FructBun>(*this); }
};

class FructOtravitor : public Planta {
protected:
    void afiseaza(std::ostream& os) const override { os << "FO"; }
public:
    FructOtravitor(int x, int y) : Planta(x, y, 5, "Fruct Otravitor", -40, true) {}
    std::shared_ptr<Entitate> clone() const override { return std::make_shared<FructOtravitor>(*this); }
    bool esteOtravitoare() const override { return true; }
};


#endif