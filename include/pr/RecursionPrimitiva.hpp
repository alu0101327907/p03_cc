#pragma once

#include <cstddef>

#include "pr/FuncionPR.hpp"

namespace pr {

/**
 * Operador de recursion primitiva.
 *
 *   h(x1, ..., xn, 0)     = f(x1, ..., xn)                    (caso base)
 *   h(x1, ..., xn, k + 1) = g(x1, ..., xn, k, h(x1, ..., xn, k))   (paso)
 *
 * con aridad(f) = n, aridad(g) = n + 2 y aridad(h) = n + 1.
 *
 * El esquema se materializa con un recorrido desde 0 hasta k aplicando g
 * sucesivamente; el resultado es exactamente el de la definicion recursiva,
 * pero se evita el desbordamiento de pila cuando k es grande.
 */
class RecursionPrimitiva : public FuncionPR {
public:
    RecursionPrimitiva(ContadorLlamadas& contador,
                       const FuncionPR& casoBase,
                       const FuncionPR& paso);

    std::string nombre() const override;
    std::size_t aridad() const override;

protected:
    Natural evaluarImpl(const std::vector<Natural>& argumentos) const override;

private:
    const FuncionPR& casoBase_;
    const FuncionPR& paso_;
    std::size_t aridad_;
};

}  // namespace pr