#pragma once

#include <cstddef>

namespace pr {

/// Tipo usado para representar los numeros naturales manejados por el programa.
using Natural = unsigned long long;

/**
 * Contador compartido del numero de llamadas a funciones primitivas recursivas.
 *
 * Se inyecta por referencia en todas las funciones, de forma que cualquier
 * invocacion (de una funcion basica o de una funcion construida) queda
 * registrada. De este modo el contador es un colaborador explicito y no un
 * estado global oculto.
 */
class ContadorLlamadas {
public:
    ContadorLlamadas() = default;

    /// Registra una nueva llamada a funcion.
    void incrementar() noexcept { ++llamadas_; }

    /// Numero total de llamadas registradas hasta el momento.
    Natural total() const noexcept { return llamadas_; }

    /// Pone el contador a cero.
    void reiniciar() noexcept { llamadas_ = 0; }

private:
    Natural llamadas_{0};
};

}  // namespace pr