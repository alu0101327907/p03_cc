#include "pr/FuncionesBasicas.hpp"

#include <limits>
#include <stdexcept>

namespace pr {

// ---------------------------------------------------------------------------
// Cero
// ---------------------------------------------------------------------------
Cero::Cero(ContadorLlamadas& contador) : FuncionPR(contador) {}

std::string Cero::nombre() const { return "Z"; }

std::size_t Cero::aridad() const { return 1; }

Natural Cero::evaluarImpl(const std::vector<Natural>& argumentos) const {
    verificarAridad(argumentos);
    return 0;
}

// ---------------------------------------------------------------------------
// Sucesor
// ---------------------------------------------------------------------------
Sucesor::Sucesor(ContadorLlamadas& contador) : FuncionPR(contador) {}

std::string Sucesor::nombre() const { return "S"; }

std::size_t Sucesor::aridad() const { return 1; }

Natural Sucesor::evaluarImpl(const std::vector<Natural>& argumentos) const {
    verificarAridad(argumentos);
    if (argumentos[0] == std::numeric_limits<Natural>::max()) {
        throw std::overflow_error("Desbordamiento al aplicar la funcion sucesor S");
    }
    return argumentos[0] + 1;
}

// ---------------------------------------------------------------------------
// Proyeccion
// ---------------------------------------------------------------------------
Proyeccion::Proyeccion(ContadorLlamadas& contador, std::size_t indice, std::size_t aridad)
    : FuncionPR(contador), indice_(indice), aridad_(aridad) {
    if (aridad == 0) {
        throw std::invalid_argument("Proyeccion: la aridad debe ser mayor que cero");
    }
    if (indice == 0 || indice > aridad) {
        throw std::invalid_argument("Proyeccion: el indice debe estar entre 1 y la aridad");
    }
}

std::string Proyeccion::nombre() const {
    return "P_" + std::to_string(indice_) + "^" + std::to_string(aridad_);
}

std::size_t Proyeccion::aridad() const { return aridad_; }

Natural Proyeccion::evaluarImpl(const std::vector<Natural>& argumentos) const {
    verificarAridad(argumentos);
    return argumentos[indice_ - 1];
}

}  // namespace pr