#ifndef OOP_ENTITATEFACTORY_HPP
#define OOP_ENTITATEFACTORY_HPP

#include <memory>
#include <string>
#include "SpeciiPradatori.hpp"
#include "SpeciiPrazi.hpp"

class EntitateFactory {
public:
    static std::shared_ptr<Animal> creeazaAnimal(const std::string& specie, int x, int y, char sex) {
        if (specie == "Lup") return std::make_shared<Lup>(x, y, sex);
        if (specie == "Vulpe") return std::make_shared<Vulpe>(x, y, sex);
        if (specie == "Urs") return std::make_shared<Urs>(x, y, sex);
        if (specie == "Uliu") return std::make_shared<Uliu>(x, y, sex);
        if (specie == "Iepure") return std::make_shared<Iepure>(x, y, sex);
        if (specie == "Caprioara") return std::make_shared<Caprioara>(x, y, sex);
        if (specie == "Pasare") return std::make_shared<Pasare>(x, y, sex);
        if (specie == "Veverita") return std::make_shared<Veverita>(x, y, sex);
        return nullptr;
    }
};

#endif