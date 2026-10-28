#include "pr/AnalizadorArgumentos.hpp"

#include <cctype>
#include <stdexcept>
#include <string>

namespace pr {
namespace {

/// Convierte una cadena de digitos en un numero natural.
Natural convertirNatural(const std::string& texto, const std::string& opcion) {
    if (texto.empty()) {
        throw std::invalid_argument("La opcion " + opcion + " necesita un valor numerico");
    }
    for (const char caracter : texto) {
        if (std::isdigit(static_cast<unsigned char>(caracter)) == 0) {
            throw std::invalid_argument("El valor '" + texto + "' de la opcion " + opcion +
                                        " no es un numero natural");
        }
    }
    try {
        std::size_t procesados = 0;
        const unsigned long long valor = std::stoull(texto, &procesados);
        if (procesados != texto.size()) {
            throw std::invalid_argument("El valor '" + texto + "' de la opcion " + opcion +
                                        " no es un numero natural");
        }
        return static_cast<Natural>(valor);
    } catch (const std::out_of_range&) {
        throw std::invalid_argument("El valor '" + texto + "' de la opcion " + opcion +
                                    " es demasiado grande");
    }
}

}  // namespace

OpcionesPrograma AnalizadorArgumentos::analizar(int argc, char* argv[]) const {
    OpcionesPrograma opciones;

    for (int i = 1; i < argc; ++i) {
        const std::string argumento = argv[i];

        if (argumento == "-h" || argumento == "--help") {
            opciones.mostrarAyuda = true;
        } else if (argumento == "-x" || argumento == "-y") {
            if (i + 1 >= argc) {
                throw std::invalid_argument("La opcion " + argumento + " necesita un valor");
            }
            const Natural valor = convertirNatural(argv[++i], argumento);
            if (argumento == "-x") {
                if (opciones.base.has_value()) {
                    throw std::invalid_argument("La opcion -x se ha indicado mas de una vez");
                }
                opciones.base = valor;
            } else {
                if (opciones.exponente.has_value()) {
                    throw std::invalid_argument("La opcion -y se ha indicado mas de una vez");
                }
                opciones.exponente = valor;
            }
        } else {
            throw std::invalid_argument("Opcion no reconocida: '" + argumento + "'");
        }
    }

    return opciones;
}

std::string AnalizadorArgumentos::uso(const std::string& nombrePrograma) {
    return "Uso: " + nombrePrograma + " -x <n> -y <n>\n"
           "\n"
           "Calcula potencia(x, y) = x^y como funcion primitiva recursiva e informa\n"
           "del numero de llamadas a funciones realizadas.\n"
           "\n"
           "Opciones:\n"
           "  -x <n>       Base de la potencia (numero natural).\n"
           "  -y <n>       Exponente de la potencia (numero natural).\n"
           "  -h, --help   Muestra esta ayuda.\n"
           "\n"
           "Ejemplo:\n"
           "  " + nombrePrograma + " -x 2 -y 10\n";
}

}  // namespace pr