#pragma once

#include <optional>
#include <string>

#include "pr/ContadorLlamadas.hpp"

namespace pr {

/// Opciones obtenidas de la linea de comandos.
struct OpcionesPrograma {
    std::optional<Natural> base;        // -x <n>
    std::optional<Natural> exponente;   // -y <n>
    bool mostrarAyuda{false};           // -h | --help
};

/// Analizador de la linea de comandos del programa principal.
class AnalizadorArgumentos {
public:
    /// Interpreta argv. Lanza std::invalid_argument si algo es incorrecto.
    OpcionesPrograma analizar(int argc, char* argv[]) const;

    /// Texto de ayuda del programa.
    static std::string uso(const std::string& nombrePrograma);
};

}  // namespace pr