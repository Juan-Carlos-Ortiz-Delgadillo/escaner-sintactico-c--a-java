#include "lexico/representacion.hpp"
#include <cctype>
#include <cstdio>

namespace lexico {

std::string representarChar(char c) {
    switch (c) {
        case '\n': return "\\n";       // salto de línea
        case '\r': return "\\r";       // retorno de carro
        case '\t': return "\\t";       // tabulación
        case '\b': return "\\b";       // backspace
        case '\f': return "\\f";       // form feed
        case ' ' : return "[espacio]"; // espacio visible
        case '\\': return "\\\\";      // barra invertida
        case '\"': return "\"";        // comillas dobles
        case '\'': return "\'";        // comillas simples
        default:
            // si es imprimible, se devuelve tal cual
            if (std::isprint(static_cast<unsigned char>(c))) {
                return std::string(1, c);
            } else {
                // si no es imprimible, se devuelve en hexadecimal
                char buf[8];
                std::snprintf(buf, sizeof(buf), "0x%02X", static_cast<unsigned char>(c));
                return std::string(buf);
            }
    }
}

} // namespace lexico
