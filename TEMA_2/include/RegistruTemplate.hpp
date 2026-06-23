#ifndef OOP_REGISTRUTEMPLATE_HPP
#define OOP_REGISTRUTEMPLATE_HPP

#include <vector>
#include <memory>
#include <iostream>

template <typename T>
class RegistruSpecial {
private:
    std::vector<std::shared_ptr<T>> entitati;
public:
    void adauga(std::shared_ptr<T> ent) {
        if (ent) entitati.push_back(ent);
    }

    int numaraVii() const {
        int count = 0;
        for (const auto& e : entitati) {
            if (e && e->getEnergie() > 0) count++;
        }
        return count;
    }
};


template <typename T>
int calculeazaEnergieTotala(const std::vector<std::shared_ptr<T>>& lista) {
    int total = 0;
    for (const auto& obiect : lista) {
        if (obiect) {
            total += obiect->getEnergie();
        }
    }
    return total;
}

#endif