#ifndef EXCEPTII_HPP
#define EXCEPTII_HPP

#include <exception>
#include <string>

// Clasa de bază proprie pentru excepții
class EcosistemException : public std::exception {
protected:
    std::string mesaj;
public:
    explicit EcosistemException(const std::string& msg);
    const char* what() const noexcept override;
};
// 1. Eroare pentru setări/inițializări invalide
class ExceptieSetariJoc : public EcosistemException {
public:
    explicit ExceptieSetariJoc(const std::string& msg);
};

// 2. Eroare pentru o secvență logică incorectă (ex: rulare fără jucător)
class ExceptieLogicaJoc : public EcosistemException {
public:
    explicit ExceptieLogicaJoc(const std::string& msg);
};


#endif // EXCEPTII_HPP