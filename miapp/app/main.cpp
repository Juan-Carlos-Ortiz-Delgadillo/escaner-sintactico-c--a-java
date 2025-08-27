#include <iostream>
#include <fstream>
#include <string>

#include "lexico/abecedario.hpp"
#include "lexico/lectorArchivo.hpp"
#include "lexico/validador.hpp"
#include "lexico/guiwin.hpp"       // ← GUI para elegir .java (Windows)
#include "lexico/tokenizer.hpp"    // ← Tokenizador

int main() {
    using namespace lexico;

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // 1) Intentar GUI (Windows). Si no seleccionas nada, pedimos por consola.
    std::string ruta = abrirDialogoSeleccionJava();
    if (ruta.empty()) {
        std::cout << "Ruta del archivo .java (puedes arrastrar y soltar, luego Enter):\n> ";
        std::getline(std::cin, ruta);
        ruta = normalizarRuta(ruta);
    }

    if (ruta.empty()) {
        std::cout << "No se proporciono ruta.\n";
        return 0;
    }

    // Verificación simple de extensión (opcional)
    if (ruta.size() < 5 || ruta.substr(ruta.size() - 5) != ".java") {
        std::cout << "Advertencia: la ruta no termina en .java\n";
    }

    // 2) Abrir archivo
    std::ifstream in;
    if (!abrirBinario(ruta, in)) {
        std::cerr << "Error: no se pudo abrir el archivo: " << ruta << "\n";
        return 1;
    }

    // 3) Validar primer caracter inválido
    Abecedario abc;
    Hallazgo h = validar(in, abc);
    if (h.invalido) {
        std::cout << h.mensaje
                  << " en linea " << h.linea
                  << ", columna " << h.columna << "\n";
        return 0; // cortar aquí, como pediste
    } else {
        std::cout << h.mensaje << "\n";
    }

    // 4) Tokenizar si la validacion fue OK
    in.clear();
    in.seekg(0);

    Tokenizer tz(in);
    std::cout << "=== TOKENS: " << ruta << " ===\n";
    while (true) {
        Token t = tz.next();
        if (t.type == TokenType::END_OF_FILE) break;
        if (t.type == TokenType::WHITESPACE) continue; // saltar blancos si no quieres verlos
        std::cout << (int)t.type << "\t" << t.lexeme
                  << "\t(" << t.line << "," << t.column << ")\n";
    }

    return 0;
}
