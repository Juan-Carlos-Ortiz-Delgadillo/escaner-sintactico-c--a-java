#pragma once
#include <string>

namespace lexico {

    // Devuelve una representación legible del carácter recibido
    // Ejemplo: '\n' -> "\\n", ' ' -> "[espacio]", 'A' -> "A", 0xC3 -> "0xC3"
    std::string representarChar(char c);

} 
