#include "lexico/abecedario.hpp"

namespace lexico {

Abecedario::Abecedario() { inicializar(); }

bool Abecedario::contiene(unsigned char c) const {
    return permitido_[c];
}

void Abecedario::inicializar() {
    permitido_.fill(false);

    // Letras minúsculas
    for (unsigned char c = 'a'; c <= 'z'; ++c)
        permitido_[c] = true;

    // Letras mayúsculas
    for (unsigned char c = 'A'; c <= 'Z'; ++c)
        permitido_[c] = true;

    // Dígitos
    for (unsigned char c = '0'; c <= '9'; ++c)
        permitido_[c] = true;

    // Símbolos visibles
    const unsigned char simbolos[] = {
        ' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')',
        '*', '+', ',', '-', '.', '/', ':', ';', '<', '=',
        '>', '?', '@', '[', ']', '^', '_', '`', '{', '|',
        '}', '~'
    };
    for (auto s : simbolos) permitido_[s] = true;

    // Caracteres de control permitidos (escapes en Java)
    permitido_['\n'] = true; // salto de línea
    permitido_['\r'] = true; // retorno de carro
    permitido_['\t'] = true; // tabulación
    permitido_['\b'] = true; // backspace
    permitido_['\f'] = true; // form feed
}

} // namespace lexico






