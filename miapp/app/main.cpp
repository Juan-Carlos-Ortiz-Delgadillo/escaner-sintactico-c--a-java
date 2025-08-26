#include <iostream>
#include <fstream>
#include <string>

#include "lexico/abecedario.hpp"
#include "lexico/lectorArchivo.hpp"
#include "lexico/validador.hpp"

int main() {
    using namespace lexico;

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cout << "Ruta del archivo .java (puedes arrastrar y soltar, luego Enter):\n> ";

    std::string ruta;
    std::getline(std::cin, ruta);
    ruta = normalizarRuta(ruta);

    // Verifica extensión (opcional)
    if (ruta.size() < 5 || ruta.substr(ruta.size() - 5) != ".java") {
        std::cout << "Advertencia: la ruta no termina en .java\n";
    }

    std::ifstream in;
    if (!abrirBinario(ruta, in)) {
        std::cerr << "Error: no se pudo abrir el archivo: " << ruta << "\n";
        return 1;
    }

    Abecedario abc;
    Hallazgo h = validar(in, abc);

    if (h.invalido) {
        std::cout << h.mensaje
                  << " en linea " << h.linea
                  << ", columna " << h.columna << "\n";
    } else {
        std::cout << h.mensaje << "\n";
    }

    return 0;
}
