#ifndef OOP_SPECIIPRADATORI_HPP
#define OOP_SPECIIPRADATORI_HPP

#include "Pradator.hpp"
#include <ostream>
#include <string>
class Lup : public Pradator {
protected:
    void doAfiseaza(std::ostream& os) const override { os << (getSex() == 'M' ? "LM" : "LF"); }
public:
    Lup(int x, int y, char sex) : Pradator(x, y, 100, "Lup", sex, 30) {}
    std::shared_ptr<Entitate> clone() const override { return std::make_shared<Lup>(*this); }
    void actioneaza(const MatriceHarta& harti) override;
};

class Vulpe : public Pradator {
protected:
    void doAfiseaza(std::ostream& os) const override { os << (getSex() == 'M' ? "VM" : "VF"); }
public:
    Vulpe(int x, int y, char sex) : Pradator(x, y, 80, "Vulpe", sex, 15) {}
    std::shared_ptr<Entitate> clone() const override { return std::make_shared<Vulpe>(*this); }
    void actioneaza(const MatriceHarta& harti) override;
};

class Urs : public Pradator {
protected:
    void doAfiseaza(std::ostream& os) const override { os << (getSex() == 'M' ? "UM" : "UF"); }
public:
    Urs(int x, int y, char sex) : Pradator(x, y, 150, "Urs", sex, 45) {}
    std::shared_ptr<Entitate> clone() const override { return std::make_shared<Urs>(*this); }
    void actioneaza(const MatriceHarta& harti) override;
};

class Uliu : public Pradator {
protected:
    void doAfiseaza(std::ostream& os) const override { os << (getSex() == 'M' ? "ULM" : "ULF"); }
public:
    Uliu(int x, int y, char sex) : Pradator(x, y, 90, "Uliu", sex, 20) {}
    std::shared_ptr<Entitate> clone() const override { return std::make_shared<Uliu>(*this); }
    void actioneaza(const MatriceHarta& harti) override;
};


#endif