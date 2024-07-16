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

    // Declaraci�n del m�todo init que probablemente inicializa la aplicaci�n y retorna un resultado de tipo HRESULT (com�n en API de Windows para indicar �xito o error).
    HRESULT init();

    // Declaraci�n del m�todo update que probablemente se usa para actualizar el estado de la aplicaci�n.
    void update();

    // Declaraci�n del m�todo render que probablemente se usa para renderizar o dibujar en la ventana.
    void render();

    // Declaraci�n del m�todo destroy que probablemente se usa para limpiar y liberar recursos.
    void destroy();

    // Declaraci�n del m�todo run que recibe los par�metros de la funci�n WinMain y probablemente contiene el bucle principal de la aplicaci�n.
    // Los par�metros son:
    // - HINSTANCE hInstance: Manejador de instancia de la aplicaci�n.
    // - HINSTANCE hPrevInstance: Manejador de instancia previa (obsoleto y siempre NULL en aplicaciones modernas).
    // - LPWSTR lpCmdLine: L�nea de comandos.
    // - int nCmdShow: Par�metro que especifica c�mo debe mostrarse la ventana.
    int run(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow);

    // Declaraci�n del m�todo WndProc que es el procedimiento de ventana.
    LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
    // Instancia de la clase Window.
    window m_window;
};
