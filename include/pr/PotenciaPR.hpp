#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "pr/FuncionPR.hpp"

namespace pr {

/**
 * Constructor de la funcion potencia como funcion primitiva recursiva.
 *
 * Ensambla, usando unicamente las funciones basicas y los operadores de
 * composicion y recursion primitiva, la siguiente jerarquia:
 *
 *   suma     = Rec[ P_1^1 ; S o P_3^3 ]
 *   producto = Rec[ Z     ; suma o (P_3^3, P_1^3) ]
 *   potencia = Rec[ S o Z ; producto o (P_3^3, P_1^3) ]
 *
 * La clase es propietaria de todas las subfunciones que construye, de modo
 * que la composicion de referencias internas es siempre valida.
 */
class PotenciaPR {
public:
    explicit PotenciaPR(ContadorLlamadas& contador);

    PotenciaPR(const PotenciaPR&) = delete;
    PotenciaPR& operator=(const PotenciaPR&) = delete;

    /// Evalua potencia(base, exponente) = base^exponente.
    Natural evaluar(Natural base, Natural exponente) const;

    /// Acceso a la funcion primitiva recursiva subyacente.
    const FuncionPR& funcion() const { return *potencia_; }

private:
    /// Crea un componente, lo almacena y devuelve una referencia estable a el.
    template <typename T, typename... Args>
    const T& crear(Args&&... args) {
        auto componente = std::make_shared<T>(std::forward<Args>(args)...);
        componentes_.push_back(componente);
        return *componente;
    }

    ContadorLlamadas& contador_;
    std::vector<std::shared_ptr<FuncionPR>> componentes_;
    const FuncionPR* potencia_{nullptr};
};

}  // namespace pr