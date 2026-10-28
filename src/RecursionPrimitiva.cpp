#include "pr/RecursionPrimitiva.hpp"

#include <stdexcept>
#include <string>

namespace pr {

RecursionPrimitiva::RecursionPrimitiva(ContadorLlamadas& contador,
                                       const FuncionPR& casoBase,
                                       const FuncionPR& paso)
    : FuncionPR(contador),
      casoBase_(casoBase),
      paso_(paso),
      aridad_(casoBase.aridad() + 1) {
    // h(x1..xn, k) requiere que el paso g tenga aridad n + 2.
    if (paso_.aridad() != aridad_ + 1) {
        throw std::invalid_argument(
            "RecursionPrimitiva: el paso '" + paso_.nombre() + "' debe tener aridad " +
            std::to_string(aridad_ + 1) + " y tiene " + std::to_string(paso_.aridad()));
    }
}

std::string RecursionPrimitiva::nombre() const {
    return "Rec[" + casoBase_.nombre() + "; " + paso_.nombre() + "]";
}

std::size_t RecursionPrimitiva::aridad() const { return aridad_; }

Natural RecursionPrimitiva::evaluarImpl(const std::vector<Natural>& argumentos) const {
    verificarAridad(argumentos);

    // Los n primeros argumentos son los parametros fijos; el ultimo es la
    // variable sobre la que se hace la recursion.
    const std::vector<Natural> parametros(argumentos.begin(), argumentos.end() - 1);
    const Natural variable = argumentos.back();

    // Caso base: h(x1, ..., xn, 0) = f(x1, ..., xn)
    Natural acumulador = casoBase_.evaluar(parametros);

    // Paso recursivo aplicado desde 0 hasta variable - 1:
    // h(x1, ..., xn, k + 1) = g(x1, ..., xn, k, h(x1, ..., xn, k))
    std::vector<Natural> entrada;
    entrada.reserve(parametros.size() + 2);
    for (Natural k = 0; k < variable; ++k) {
        entrada.clear();
        entrada.insert(entrada.end(), parametros.begin(), parametros.end());
        entrada.push_back(k);
        entrada.push_back(acumulador);
        acumulador = paso_.evaluar(entrada);
    }

    return acumulador;
}

}  // namespace pr