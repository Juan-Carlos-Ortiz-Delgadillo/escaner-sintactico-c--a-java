#pragma once
#include <string>
#include <fstream>

namespace lexico {

    // Quita comillas iniciales/finales de la ruta
    // Ej: "C:\Users\juan\archivo.java" -> C:\Users\juan\archivo.java
    std::string normalizarRuta(const std::string& ruta);

    // Intenta abrir un archivo en modo binario.
    // Devuelve true si se pudo abrir.
    bool abrirBinario(const std::string& ruta, std::ifstream& out);

} // namespace lexico
