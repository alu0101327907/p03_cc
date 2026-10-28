#include "pr/FuncionPR.hpp"

#include <stdexcept>

namespace pr {

void FuncionPR::verificarAridad(const std::vector<Natural>& argumentos) const {
    if (argumentos.size() != aridad()) {
        throw std::invalid_argument("La funcion '" + nombre() + "' espera " +
                                    std::to_string(aridad()) + " argumento(s) pero ha recibido " +
                                    std::to_string(argumentos.size()));
    }
}

}  // namespace pr