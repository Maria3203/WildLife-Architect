#ifndef OOP_ENTITATE_HPP
#define OOP_ENTITATE_HPP

#pragma once
#include <string>
#include <memory>
#include <vector>

class Entitate;

using MatriceHarta = std::vector<std::vector<std::shared_ptr<Entitate>>>;

class Entitate {
private:
    static int contorID;

    int id_;
    std::string numeSpecie;
    char sex;

protected:
    int x, y;
    int energie;


    virtual void doAfiseaza(std::ostream& os) const = 0;

public:
    Entitate(int x, int y, int energie,const std::string& numeSpecie, char sex);
    virtual ~Entitate() = default;

    virtual std::shared_ptr<Entitate> clone() const = 0;

    virtual void actioneaza(const MatriceHarta& harti) = 0;


    void afiseaza(std::ostream& os) const;

    int getId() const { return id_; }
    int getX() const { return x; }
    int getY() const { return y; }
    int getEnergie() const { return energie; }
    char getSex() const { return sex; }
    const std::string& getNumeSpecie() const { return numeSpecie; }

    void modificaEnergie(int cantitate);
    void setPozitie(int nouX, int nouY);


    friend std::ostream& operator<<(std::ostream& os, const Entitate& entitate);
};


#endif