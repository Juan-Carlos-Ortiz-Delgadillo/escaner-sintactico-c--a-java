#include "lexico/validador.hpp"
#include "lexico/abecedario.hpp"
#include "lexico/representacion.hpp"

namespace lexico {

Hallazgo validar(std::istream& in, const Abecedario& abc) {
    Hallazgo h;
    std::size_t linea = 1, columna = 1;

    char c;
    while (in.get(c)) {
        unsigned char uc = static_cast<unsigned char>(c);

        // ¿Está permitido este byte?
        if (!abc.contiene(uc)) {
            h.invalido = true;
            h.caracter = c;
            h.linea = linea;
            h.columna = columna;
            h.mensaje = "Invalid character: " + representarChar(c);
            return h; // cortar inmediatamente
        }

        // Avance de posición
        if (c == '\n') {             // LF
            ++linea;
            columna = 1;
        } else if (c == '\r') {      // CR en CRLF (Windows): no contamos columna
            // esperar a que llegue '\n'
        } else if (c == '\t') {      // si quieres contar TAB como varias columnas, cámbialo
            ++columna;               // p.ej. columna += 4;
        } else {
            ++columna;
        }
    }

    // Si llegamos aquí, no hubo inválidos
    h.invalido = false;
    h.linea = linea;
    h.columna = columna;
    h.mensaje = "OK: todos los caracteres pertenecen al abecedario.";
    return h;
}

} // namespace lexico
