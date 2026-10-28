#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "pr/ContadorLlamadas.hpp"

namespace pr {

/**
 * Clase base abstracta de toda funcion primitiva recursiva.
 *
 * Toda funcion concreta implementa evaluarImpl() y declara su nombre y su
 * aridad. El metodo publico evaluar() es no virtual: se encarga de contar la
 * llamada y de delegar en la implementacion concreta, garantizando que
 * absolutamente todas las invocaciones quedan registradas.
 */
class FuncionPR {
public:
    explicit FuncionPR(ContadorLlamadas& contador) : contador_(contador) {}

    virtual ~FuncionPR() = default;

    // Las funciones se comparten por referencia entre composiciones y
    // recursiones, por lo que se prohibe la copia para evitar duplicados
    // inconsistentes del estado.
    FuncionPR(const FuncionPR&) = delete;
    FuncionPR& operator=(const FuncionPR&) = delete;

    /// Punto de entrada unico: cuenta la llamada y evalua la funcion.
    Natural evaluar(const std::vector<Natural>& argumentos) const {
        contador_.incrementar();
        return evaluarImpl(argumentos);
    }

    /// Nombre simbolico de la funcion (utilidad para depuracion).
    virtual std::string nombre() const = 0;

    /// Numero de argumentos que consume la funcion.
    virtual std::size_t aridad() const = 0;

protected:
    /// Implementacion concreta de la funcion (no cuenta la llamada).
    virtual Natural evaluarImpl(const std::vector<Natural>& argumentos) const = 0;

    /// Lanza std::invalid_argument si el numero de argumentos no coincide.
    void verificarAridad(const std::vector<Natural>& argumentos) const;

    ContadorLlamadas& contador_;
};

}  // namespace pr