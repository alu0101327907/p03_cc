#pragma once

#include <vector>

#include "pr/FuncionPR.hpp"

namespace pr {

/**
 * Operador de composicion.
 *
 *   Comp[f; g1, ..., gk](x1, ..., xn) = f(g1(x1, ..., xn), ..., gk(x1, ..., xn))
 *
 * donde k es la aridad de f y n la aridad comun de las gi.
 */
class Composicion : public FuncionPR {
public:
    Composicion(ContadorLlamadas& contador,
                const FuncionPR& exterior,
                std::vector<const FuncionPR*> interiores);

    std::string nombre() const override;
    std::size_t aridad() const override;

protected:
    Natural evaluarImpl(const std::vector<Natural>& argumentos) const override;

private:
    const FuncionPR& exterior_;
    std::vector<const FuncionPR*> interiores_;
    std::size_t aridad_;
};

}  // namespace pr