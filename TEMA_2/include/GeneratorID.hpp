#ifndef OOP_GENERATORID_HPP
#define OOP_GENERATORID_HPP

class GeneratorID {
private:
    int idCurent;

    GeneratorID() : idCurent(0) {}

public:
    GeneratorID(const GeneratorID&) = delete;
    GeneratorID& operator=(const GeneratorID&) = delete;

    static GeneratorID& getInstance() {
        static GeneratorID instanta;
        return instanta;
    }

    int genereazaID() {
        return ++idCurent;
    }
};

#endif
