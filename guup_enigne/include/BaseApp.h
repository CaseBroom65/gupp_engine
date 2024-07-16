#pragma once
#include "PreRequisitos.h"
#include "Window.h"
// Define una clase llamada BaseApp.
class BaseApp
{
public:
    // Constructor predeterminado para BaseApp.
    BaseApp() = default;
    // Destructor predeterminado para BaseApp.
    ~BaseApp() = default;

    // Declaración del método init que probablemente inicializa la aplicación y retorna un resultado de tipo HRESULT (común en API de Windows para indicar éxito o error).
    HRESULT init();

    // Declaración del método update que probablemente se usa para actualizar el estado de la aplicación.
    void update();

    // Declaración del método render que probablemente se usa para renderizar o dibujar en la ventana.
    void render();

    // Declaración del método destroy que probablemente se usa para limpiar y liberar recursos.
    void destroy();

    // Declaración del método run que recibe los parámetros de la función WinMain y probablemente contiene el bucle principal de la aplicación.
    // Los parámetros son:
    // - HINSTANCE hInstance: Manejador de instancia de la aplicación.
    // - HINSTANCE hPrevInstance: Manejador de instancia previa (obsoleto y siempre NULL en aplicaciones modernas).
    // - LPWSTR lpCmdLine: Línea de comandos.
    // - int nCmdShow: Parámetro que especifica cómo debe mostrarse la ventana.
    int run(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow);

    // Declaración del método WndProc que es el procedimiento de ventana.
    LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
    // Instancia de la clase Window.
    window m_window;
};
