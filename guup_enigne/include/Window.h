#pragma once
#include "PreRequisitos.h"


class window
{
public:
    // Constructor por defecto
    window() = default;
    // Destructor por defecto
    ~window() = default;

    // Método para inicializar la ventana
    // Recibe un handle a la instancia, un código de comando y un procedimiento de ventana
    HRESULT init(HINSTANCE hInstance, int nCmdShow, WNDPROC wndproc);

    // Método para actualizar la ventana
    void update();

    // Método para renderizar la ventana
    void render();

    // Método para destruir o liberar recursos de la ventana
    void destroy();

public:
    // Handle de la ventana
    HWND m_hWnd = nullptr;
    // Ancho de la ventana
    unsigned int m_width;
    // Altura de la ventana
    unsigned int m_height;

private:
    // Handle a la instancia de la aplicación
    HINSTANCE m_hInst = nullptr;
    // Estructura que define el rectángulo de la ventana
    RECT m_rect;
    // Nombre de la ventana
    std::string m_windowname = "guup Engine";
};
