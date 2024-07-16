#include "BaseApp.h"
#include "Window.h"

// Método para inicializar la aplicación base
HRESULT BaseApp::init()
{
    return E_NOTIMPL; // Indica que la implementación no está disponible
}

// Método para actualizar la lógica de la aplicación
void BaseApp::update()
{
}

// Método para renderizar la escena
void BaseApp::render()
{
}

// Método para destruir o liberar recursos de la aplicación
void BaseApp::destroy()
{
}

// Método para ejecutar la aplicación
int BaseApp::run(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance); // Previene advertencias sobre parámetros no utilizados
    UNREFERENCED_PARAMETER(lpCmdLine); // Previene advertencias sobre parámetros no utilizados

    // Inicializa la ventana y verifica si tuvo éxito
    if (FAILED(m_window.init(hInstance, nCmdShow, nullptr)))
        return 0; // Regresa 0 si la inicialización falló

    // Llama al método init y verifica si tuvo éxito
    if (FAILED(init()))
    {
        destroy(); // Libera recursos si la inicialización falló
        return 0;
    }

    // Bucle principal de mensajes
    MSG msg = { 0 }; // Inicializa la estructura de mensajes
    while (WM_QUIT != msg.message) // Continúa hasta que se recibe un mensaje de salida
    {
        // Procesa mensajes de la cola
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg); // Traduce los mensajes de teclado
            DispatchMessage(&msg); // Envía mensajes a la ventana
        }
        else
        {
            update(); // Llama al método de actualización
            render(); // Llama al método de renderizado
        }
    }

    destroy(); // Libera recursos al salir

    return (int)msg.wParam; // Devuelve el código de salida de la aplicación
}

// Método para manejar mensajes de la ventana
LRESULT CALLBACK BaseApp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message)
    {
    case WM_PAINT: // Mensaje de pintura
        hdc = BeginPaint(hWnd, &ps); // Comienza la pintura
        EndPaint(hWnd, &ps); // Finaliza la pintura
        break;

    case WM_DESTROY: // Mensaje de destrucción
        PostQuitMessage(0); // Envia un mensaje para salir
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam); // Manejo por defecto de otros mensajes
    }

    return 0; // Retorna 0 si se manejó el mensaje
}
