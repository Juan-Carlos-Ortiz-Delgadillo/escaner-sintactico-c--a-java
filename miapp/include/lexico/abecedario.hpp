#pragma once

#include <array>

namespace lexico {

class Abecedario {
public:
    // Constructor: inicializa la tabla de caracteres permitidos
    Abecedario();

    // Método público: verifica si el caracter pertenece al abecedario
    bool contiene(unsigned char c) const;

private:
    // Tabla de 256 posiciones: true si el caracter está permitido
    std::array<bool, 256> permitido_;

    // Inicializa la tabla con todos los caracteres válidos
    void inicializar();
};

} // namespace lexico
