#ifndef EXCEPTII_HPP
#define EXCEPTII_HPP

#include <exception>
#include <string>


class EcosistemException : public std::exception {
protected:
    std::string mesaj;
public:
    explicit EcosistemException(const std::string& msg);
    const char* what() const noexcept override;
};

class ExceptieSetariJoc : public EcosistemException {
public:
    explicit ExceptieSetariJoc(const std::string& msg);
};


class ExceptieLogicaJoc : public EcosistemException {
public:
    explicit ExceptieLogicaJoc(const std::string& msg);
};


#endif // EXCEPTII_HPP