#include "lexico/guiwin.hpp"
#ifdef _WIN32
#include <windows.h>
#include <commdlg.h>
#endif

namespace lexico {

std::string abrirDialogoSeleccionJava() {
#ifdef _WIN32
    char szFile[MAX_PATH] = {0};
    OPENFILENAMEA ofn{}; ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = nullptr;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "Archivos Java\0*.java\0Todos\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    if (GetOpenFileNameA(&ofn)) return std::string(szFile);
#endif
    return {};
}

} // namespace lexico
