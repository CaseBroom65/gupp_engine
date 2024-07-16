#include "BaseApp.h"
#include "Window.h"

// M�todo para inicializar la aplicaci�n base
HRESULT BaseApp::init()
{
    return E_NOTIMPL; // Indica que la implementaci�n no est� disponible
}

// M�todo para actualizar la l�gica de la aplicaci�n
void BaseApp::update()
{
}

// M�todo para renderizar la escena
void BaseApp::render()
{
}

// M�todo para destruir o liberar recursos de la aplicaci�n
void BaseApp::destroy()
{
}

// M�todo para ejecutar la aplicaci�n
int BaseApp::run(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance); // Previene advertencias sobre par�metros no utilizados
    UNREFERENCED_PARAMETER(lpCmdLine); // Previene advertencias sobre par�metros no utilizados

    // Inicializa la ventana y verifica si tuvo �xito
    if (FAILED(m_window.init(hInstance, nCmdShow, nullptr)))
        return 0; // Regresa 0 si la inicializaci�n fall�

    // Llama al m�todo init y verifica si tuvo �xito
    if (FAILED(init()))
    {
        destroy(); // Libera recursos si la inicializaci�n fall�
        return 0;
    }

    // Bucle principal de mensajes
    MSG msg = { 0 }; // Inicializa la estructura de mensajes
    while (WM_QUIT != msg.message) // Contin�a hasta que se recibe un mensaje de salida
    {
        // Procesa mensajes de la cola
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg); // Traduce los mensajes de teclado
            DispatchMessage(&msg); // Env�a mensajes a la ventana
        }
        else
        {
            update(); // Llama al m�todo de actualizaci�n
            render(); // Llama al m�todo de renderizado
        }
    }

    destroy(); // Libera recursos al salir

    return (int)msg.wParam; // Devuelve el c�digo de salida de la aplicaci�n
}

// M�todo para manejar mensajes de la ventana
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

    case WM_DESTROY: // Mensaje de destrucci�n
        PostQuitMessage(0); // Envia un mensaje para salir
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam); // Manejo por defecto de otros mensajes
    }

    return 0; // Retorna 0 si se manej� el mensaje
}
