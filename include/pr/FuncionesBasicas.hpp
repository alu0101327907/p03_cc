#pragma once

#include <cstddef>

#include "pr/FuncionPR.hpp"

namespace pr {

/// Funcion basica cero: Z(x) = 0.
class Cero : public FuncionPR {
public:
    explicit Cero(ContadorLlamadas& contador);

    std::string nombre() const override;
    std::size_t aridad() const override;

protected:
    Natural evaluarImpl(const std::vector<Natural>& argumentos) const override;
};

/// Funcion basica sucesor: S(x) = x + 1.
class Sucesor : public FuncionPR {
public:
    explicit Sucesor(ContadorLlamadas& contador);

    std::string nombre() const override;
    std::size_t aridad() const override;

protected:
    Natural evaluarImpl(const std::vector<Natural>& argumentos) const override;
};

/// Funcion basica de proyeccion: P_i^n(x1, ..., xn) = xi.
class Proyeccion : public FuncionPR {
public:
    Proyeccion(ContadorLlamadas& contador, std::size_t indice, std::size_t aridad);

    std::string nombre() const override;
    std::size_t aridad() const override;

protected:
    Natural evaluarImpl(const std::vector<Natural>& argumentos) const override;

private:
    std::size_t indice_;
    std::size_t aridad_;
};

}  // namespace pr