#pragma once
#include "PreRequisitos.h"


class window
{
public:
    // Constructor por defecto
    window() = default;
    // Destructor por defecto
    ~window() = default;

    // M�todo para inicializar la ventana
    // Recibe un handle a la instancia, un c�digo de comando y un procedimiento de ventana
    HRESULT init(HINSTANCE hInstance, int nCmdShow, WNDPROC wndproc);

    // M�todo para actualizar la ventana
    void update();

    // M�todo para renderizar la ventana
    void render();

    // M�todo para destruir o liberar recursos de la ventana
    void destroy();

public:
    // Handle de la ventana
    HWND m_hWnd = nullptr;
    // Ancho de la ventana
    unsigned int m_width;
    // Altura de la ventana
    unsigned int m_height;

private:
    // Handle a la instancia de la aplicaci�n
    HINSTANCE m_hInst = nullptr;
    // Estructura que define el rect�ngulo de la ventana
    RECT m_rect;
    // Nombre de la ventana
    std::string m_windowname = "guup Engine";
};
