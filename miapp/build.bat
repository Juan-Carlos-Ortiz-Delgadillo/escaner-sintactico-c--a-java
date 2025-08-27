@echo off
echo ============================================
echo Compilando proyecto "verificador" ...
echo ============================================

REM Compilar todos los .cpp y enlazar comdlg32 (dialogo Abrir archivo)
g++ -std=c++17 -Iinclude ^
  src\lexico\abecedario.cpp ^
  src\lexico\lectorArchivo.cpp ^
  src\lexico\representacion.cpp ^
  src\lexico\validador.cpp ^
  src\lexico\tokenizer.cpp ^
  src\lexico\dynamicrules.cpp ^
  src\lexico\guiwin.cpp ^
  app\main.cpp ^
  -lcomdlg32 ^
  -o verificador.exe

if %ERRORLEVEL% NEQ 0 (
  echo --------------------------------------------
  echo ❌ Error de compilacion
  pause
  exit /b %ERRORLEVEL%
)

echo --------------------------------------------
echo ✅ Compilacion exitosa. Ejecutando programa...
echo --------------------------------------------
verificador.exe
pause
