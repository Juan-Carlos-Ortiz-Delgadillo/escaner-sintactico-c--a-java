#include "lexico/lectorArchivo.hpp"

namespace lexico {

// 🔹 Quita comillas iniciales/finales (cuando arrastras un archivo en consola)
std::string normalizarRuta(const std::string& ruta) {
    if (ruta.empty()) return ruta;

    std::string r = ruta;

    if (!r.empty() && (r.front() == '\"' || r.front() == '\'')) {
        r.erase(r.begin());
    }
    if (!r.empty() && (r.back() == '\"' || r.back() == '\'')) {
        r.pop_back();
    }

    return r;
}

// 🔹 Intenta abrir un archivo en modo binario
bool abrirBinario(const std::string& ruta, std::ifstream& out) {
    out = std::ifstream(ruta, std::ios::binary);
    return static_cast<bool>(out);
}

} // namespace lexico
