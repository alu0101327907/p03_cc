#include "pr/Composicion.hpp"

#include <stdexcept>
#include <utility>

namespace pr {

Composicion::Composicion(ContadorLlamadas& contador,
                         const FuncionPR& exterior,
                         std::vector<const FuncionPR*> interiores)
    : FuncionPR(contador),
      exterior_(exterior),
      interiores_(std::move(interiores)),
      aridad_(0) {
    if (interiores_.size() != exterior_.aridad()) {
        throw std::invalid_argument(
            "Composicion: la funcion exterior '" + exterior_.nombre() + "' tiene aridad " +
            std::to_string(exterior_.aridad()) + " pero se han proporcionado " +
            std::to_string(interiores_.size()) + " funciones interiores");
    }

    if (!interiores_.empty()) {
        aridad_ = interiores_.front()->aridad();
        for (const FuncionPR* interior : interiores_) {
            if (interior == nullptr) {
                throw std::invalid_argument("Composicion: funcion interior nula");
            }
            if (interior->aridad() != aridad_) {
                throw std::invalid_argument(
                    "Composicion: todas las funciones interiores deben tener la misma aridad");
            }
        }
    }
}

std::string Composicion::nombre() const {
    std::string resultado = "Comp[" + exterior_.nombre() + " o (";
    for (std::size_t i = 0; i < interiores_.size(); ++i) {
        if (i > 0) {
            resultado += ", ";
        }
        resultado += interiores_[i]->nombre();
    }
    resultado += ")]";
    return resultado;
}

std::size_t Composicion::aridad() const { return aridad_; }

Natural Composicion::evaluarImpl(const std::vector<Natural>& argumentos) const {
    verificarAridad(argumentos);

    std::vector<Natural> intermedios;
    intermedios.reserve(interiores_.size());
    for (const FuncionPR* interior : interiores_) {
        intermedios.push_back(interior->evaluar(argumentos));
    }
    return exterior_.evaluar(intermedios);
}

}  // namespace pr