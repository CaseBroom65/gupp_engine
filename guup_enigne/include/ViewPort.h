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

    // M�todo para inicializar el viewport
    // Recibe una ventana como par�metro
    void
      init(window window);

    // M�todo para actualizar el viewport
    void 
      update();

    // M�todo para renderizar usando el contexto del dispositivo
    void 
      render(DeviceContext& deviceContext);

    // M�todo para destruir o liberar recursos del viewport
    void 
      destroy();

public:
    // Estructura que define el viewport en Direct3D
    D3D11_VIEWPORT m_viewport;
};
