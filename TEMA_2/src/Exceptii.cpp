#include "../include/Exceptii.hpp"

EcosistemException::EcosistemException(const std::string& msg) : mesaj(msg) {}

const char* EcosistemException::what() const noexcept {
    return mesaj.c_str();
}

ExceptieSetariJoc::ExceptieSetariJoc(const std::string& msg)
    : EcosistemException("Eroare Setari: " + msg) {}

ExceptieLogicaJoc::ExceptieLogicaJoc(const std::string& msg)
    : EcosistemException("Eroare Logica: " + msg) {}

