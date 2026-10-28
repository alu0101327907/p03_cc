#include <cmath>
#include <exception>
#include <iostream>
#include <limits>
#include <string>

#include "pr/AnalizadorArgumentos.hpp"
#include "pr/ContadorLlamadas.hpp"
#include "pr/PotenciaPR.hpp"

namespace {

constexpr long double UMBRAL_AVISO_LLAMADAS = 5.0e7L;

/// Comprueba si base^exponente es representable con el tipo Natural.
bool desbordaPotencia(pr::Natural base, pr::Natural exponente) {
    const pr::Natural maximo = std::numeric_limits<pr::Natural>::max();
    if (base == 0) {
        return false;  // 0^y = 0 (o 1 si y = 0): nunca desborda
    }
    pr::Natural acumulado = 1;
    for (pr::Natural i = 0; i < exponente; ++i) {
        if (acumulado > maximo / base) {
            return true;
        }
        acumulado *= base;
    }
    return false;
}

/// Avisa por stderr cuando el numero de llamadas estimado es muy elevado.
void avisarSiCosteElevado(pr::Natural base, pr::Natural exponente) {
    long double estimacion = 0.0L;
    if (base >= 2) {
        estimacion = std::pow(static_cast<long double>(base),
                              static_cast<long double>(exponente)) *
                     (static_cast<long double>(exponente) + 2.0L);
    } else {
        estimacion = 2.0L * static_cast<long double>(exponente);
    }

    if (estimacion > UMBRAL_AVISO_LLAMADAS) {
        std::cerr << "Aviso: el numero de llamadas estimado es muy elevado. "
                     "La ejecucion puede tardar (pulse Ctrl+C para cancelar).\n";
    }
}

}  // namespace

int main(int argc, char* argv[]) {
    const std::string nombrePrograma =
        (argc > 0 && argv[0] != nullptr) ? std::string(argv[0]) : std::string("potencia_pr");

    try {
        const pr::AnalizadorArgumentos analizador;
        const pr::OpcionesPrograma opciones = analizador.analizar(argc, argv);

        if (opciones.mostrarAyuda) {
            std::cout << pr::AnalizadorArgumentos::uso(nombrePrograma);
            return 0;
        }

        if (!opciones.base.has_value() || !opciones.exponente.has_value()) {
            std::cerr << "Error: es obligatorio indicar la base (-x) y el exponente (-y).\n\n"
                      << pr::AnalizadorArgumentos::uso(nombrePrograma);
            return 1;
        }

        const pr::Natural base = *opciones.base;
        const pr::Natural exponente = *opciones.exponente;

        if (desbordaPotencia(base, exponente)) {
            std::cerr << "Error: " << base << "^" << exponente
                      << " no es representable con enteros de 64 bits (unsigned long long).\n";
            return 2;
        }

        avisarSiCosteElevado(base, exponente);

        pr::ContadorLlamadas contador;
        const pr::PotenciaPR potencia(contador);
        const pr::Natural resultado = potencia.evaluar(base, exponente);

        std::cout << "potencia(" << base << ", " << exponente << ") = " << resultado << '\n';
        std::cout << "Numero de llamadas a funciones: " << contador.total() << '\n';
        return 0;
    } catch (const std::exception& excepcion) {
        std::cerr << "Error: " << excepcion.what() << "\n\n"
                  << "Use -h o --help para ver la ayuda del programa.\n";
        return 1;
    }
}