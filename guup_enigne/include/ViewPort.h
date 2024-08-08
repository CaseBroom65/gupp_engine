#pragma once
#include "PreRequisitos.h"
class window;
class DeviceContext;

class Viewport
{
public:
    // Constructor por defecto
    Viewport() = default;
    // Destructor por defecto
    ~Viewport() = default;

    // Método para inicializar el viewport
    // Recibe una ventana como parámetro
    void
      init(window window);

    // Método para actualizar el viewport
    void 
      update();

    // Método para renderizar usando el contexto del dispositivo
    void 
      render(DeviceContext& deviceContext);

    // Método para destruir o liberar recursos del viewport
    void 
      destroy();

public:
    // Estructura que define el viewport en Direct3D
    D3D11_VIEWPORT m_viewport;
};
