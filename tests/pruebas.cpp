#include <iostream>
#include <stdexcept>
#include <vector>

#include "pr/ContadorLlamadas.hpp"
#include "pr/PotenciaPR.hpp"

namespace {

int fallos = 0;

void comprobarPotencia(pr::Natural base, pr::Natural exponente, pr::Natural esperado) {
    pr::ContadorLlamadas contador;
    const pr::PotenciaPR potencia(contador);
    const pr::Natural obtenido = potencia.evaluar(base, exponente);

    if (obtenido != esperado) {
        std::cerr << "FALLO: potencia(" << base << ", " << exponente << ") = " << obtenido
                  << ", se esperaba " << esperado << '\n';
        ++fallos;
    }
    if (contador.total() == 0) {
        std::cerr << "FALLO: no se ha contabilizado ninguna llamada en potencia(" << base << ", "
                  << exponente << ")\n";
        ++fallos;
    }
}

void comprobarNumeroDeLlamadas(pr::Natural base, pr::Natural exponente, pr::Natural esperado) {
    pr::ContadorLlamadas contador;
    const pr::PotenciaPR potencia(contador);
    static_cast<void>(potencia.evaluar(base, exponente));

    if (contador.total() != esperado) {
        std::cerr << "FALLO: potencia(" << base << ", " << exponente << ") realiza "
                  << contador.total() << " llamadas, se esperaban " << esperado << '\n';
        ++fallos;
    }
}

void comprobarAridadIncorrecta() {
    pr::ContadorLlamadas contador;
    const pr::PotenciaPR potencia(contador);
    try {
        static_cast<void>(potencia.funcion().evaluar(std::vector<pr::Natural>{2}));
        std::cerr << "FALLO: se esperaba una excepcion por aridad incorrecta\n";
        ++fallos;
    } catch (const std::invalid_argument&) {
        // Comportamiento correcto.
    }
}

}  // namespace

int main() {
    struct Caso {
        pr::Natural base;
        pr::Natural exponente;
        pr::Natural esperado;
    };

    const std::vector<Caso> casos = {
        {0, 0, 1},      {0, 5, 0},      {1, 0, 1},      {1, 100, 1},   {2, 0, 1},
        {2, 1, 2},      {2, 10, 1024},  {3, 4, 81},     {5, 3, 125},   {7, 5, 16807},
        {10, 6, 1000000}};

    for (const Caso& caso : casos) {
        comprobarPotencia(caso.base, caso.exponente, caso.esperado);
    }

    // El numero de llamadas es determinista: se fija como prueba de regresion.
    comprobarNumeroDeLlamadas(2, 0, 4);
    comprobarNumeroDeLlamadas(2, 1, 25);
    comprobarNumeroDeLlamadas(2, 10, 6292);

    comprobarAridadIncorrecta();

    if (fallos == 0) {
        std::cout << "Todas las pruebas se han superado.\n";
        return 0;
    }
    std::cerr << fallos << " prueba(s) fallida(s).\n";
    return 1;
}