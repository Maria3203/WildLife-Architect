#ifndef OOP_SPECIIPRAZI_HPP
#define OOP_SPECIIPRAZI_HPP

#include "Prada.hpp"
#include <ostream>
#include <string>

class Iepure : public Prada {
protected:
    void doAfiseaza(std::ostream& os) const override { os << "ie"; }
public:
    Iepure(int x, int y, char sex) : Prada(x, y, 50, "Iepure", sex, 25) {}
    std::shared_ptr<Entitate> clone() const override { return std::make_shared<Iepure>(*this); }
    void actioneaza(const MatriceHarta& harti) override;
};

class Caprioara : public Prada {
protected:
    void doAfiseaza(std::ostream& os) const override { os << "ca"; }
public:
    Caprioara(int x, int y, char sex) : Prada(x, y, 90, "Caprioara", sex, 50) {}
    std::shared_ptr<Entitate> clone() const override { return std::make_shared<Caprioara>(*this); }
    void actioneaza(const MatriceHarta& harti) override;
};

class Pasare : public Prada {
protected:
    void doAfiseaza(std::ostream& os) const override { os << "pa"; }
public:
    Pasare(int x, int y, char sex) : Prada(x, y, 40, "Pasare", sex, 20) {}
    std::shared_ptr<Entitate> clone() const override { return std::make_shared<Pasare>(*this); }
    void actioneaza(const MatriceHarta& harti) override;
};


class Veverita : public Prada {
protected:
    void doAfiseaza(std::ostream& os) const override { os << "ve"; }
public:
    Veverita(int x, int y, char sex) : Prada(x, y, 30, "Veverita", sex, 15) {}
    std::shared_ptr<Entitate> clone() const override { return std::make_shared<Veverita>(*this); }
    void actioneaza(const MatriceHarta& harti) override;
};


#endif