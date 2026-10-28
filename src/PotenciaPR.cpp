#include "pr/PotenciaPR.hpp"

#include <utility>
#include <vector>

#include "pr/Composicion.hpp"
#include "pr/FuncionesBasicas.hpp"
#include "pr/RecursionPrimitiva.hpp"

namespace pr {

PotenciaPR::PotenciaPR(ContadorLlamadas& contador) : contador_(contador) {
    // -----------------------------------------------------------------------
    // Funciones recursivas basicas
    // -----------------------------------------------------------------------
    const auto& cero = crear<Cero>(contador_);                          // Z(x) = 0
    const auto& sucesor = crear<Sucesor>(contador_);                    // S(x) = x + 1
    const auto& proy1_1 = crear<Proyeccion>(contador_, 1, 1);           // P_1^1
    const auto& proy1_3 = crear<Proyeccion>(contador_, 1, 3);           // P_1^3
    const auto& proy3_3 = crear<Proyeccion>(contador_, 3, 3);           // P_3^3

    // -----------------------------------------------------------------------
    // suma(x, y) = x + y
    //   suma(x, 0)     = P_1^1(x)
    //   suma(x, y + 1) = S( P_3^3(x, y, suma(x, y)) )
    // -----------------------------------------------------------------------
    const auto& sucesorDelAcumulador =
        crear<Composicion>(contador_, sucesor, std::vector<const FuncionPR*>{&proy3_3});
    const auto& suma = crear<RecursionPrimitiva>(contador_, proy1_1, sucesorDelAcumulador);

    // -----------------------------------------------------------------------
    // producto(x, y) = x * y
    //   producto(x, 0)     = Z(x)
    //   producto(x, y + 1) = suma( P_3^3(x, y, producto(x, y)),
    //                              P_1^3(x, y, producto(x, y)) )
    // -----------------------------------------------------------------------
    const auto& sumaAcumuladorBase = crear<Composicion>(
        contador_, suma, std::vector<const FuncionPR*>{&proy3_3, &proy1_3});
    const auto& producto = crear<RecursionPrimitiva>(contador_, cero, sumaAcumuladorBase);

    // -----------------------------------------------------------------------
    // potencia(x, y) = x^y
    //   potencia(x, 0)     = S(Z(x)) = 1
    //   potencia(x, y + 1) = producto( P_3^3(x, y, potencia(x, y)),
    //                                  P_1^3(x, y, potencia(x, y)) )
    // -----------------------------------------------------------------------
    const auto& uno =
        crear<Composicion>(contador_, sucesor, std::vector<const FuncionPR*>{&cero});
    const auto& productoAcumuladorBase = crear<Composicion>(
        contador_, producto, std::vector<const FuncionPR*>{&proy3_3, &proy1_3});
    potencia_ = &crear<RecursionPrimitiva>(contador_, uno, productoAcumuladorBase);
}

Natural PotenciaPR::evaluar(Natural base, Natural exponente) const {
    return potencia_->evaluar(std::vector<Natural>{base, exponente});
}

}  // namespace pr