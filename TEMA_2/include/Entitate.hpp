#ifndef OOP_ENTITATE_HPP
#define OOP_ENTITATE_HPP

#include <memory>
#include <iostream>
#include <vector>
#include <string>

class Entitate;


using MatriceHarta = std::vector<std::vector<std::shared_ptr<Entitate>>>;


class Entitate {
protected:
    int x, y;
    int id;
    int energie;
    std::string numeSpecie;

public:
    Entitate(int x, int y, int energie, const std::string& numeSpecieParam);
    virtual ~Entitate() = default;

    virtual bool estePrada() const { return false; }
    virtual bool estePradator() const { return false; }
    virtual bool estePlanta() const { return false; }
    virtual bool esteFructOtravitor() const { return false; }

    virtual int getBonusEnergie() const { return 0; }


    virtual void actioneaza(const MatriceHarta& harti) = 0;
    virtual std::shared_ptr<Entitate> clone() const = 0;
    virtual void afiseaza(std::ostream& os) const = 0;

    int getX() const { return x; }
    int getY() const { return y; }
    int getId() const { return id; }
    void setPozitie(int nouX, int nouY) { x = nouX; y = nouY; }
    int getEnergie() const { return energie; }
    void modificaEnergie(int val) { energie += val; }
    const std::string& getNumeSpecie() const { return numeSpecie; }
};

#endif