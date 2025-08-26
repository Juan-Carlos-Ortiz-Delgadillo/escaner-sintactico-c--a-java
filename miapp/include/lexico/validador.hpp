#pragma once
#include <istream>
#include <cstddef>
#include <string>

namespace lexico {

class Abecedario;

// Resultado de la verificación
struct Hallazgo {
    bool invalido = false;      // true si se encontró un carácter inválido
    char caracter = '\0';       // el byte encontrado
    std::size_t linea = 0;      // 1-based
    std::size_t columna = 0;    // 1-based
    std::string mensaje;        // texto legible ("Invalid character: ...")
};

// Recorre el stream y devuelve:
//  - Hallazgo{invalido=true,...} si encuentra el primer inválido (y corta)
//  - Hallazgo{invalido=false,...} si todo está OK
Hallazgo validar(std::istream& in, const Abecedario& abc);

} // namespace lexico
