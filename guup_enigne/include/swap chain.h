#pragma once
#include "PreRequisitos.h"

//Forward Declarations - declaraciones Directas
class Device;
class DeviceContext;
class window;
class Texture;

class SwapChain
{
public:
    // Constructor por defecto
    SwapChain() = default;
    // Destructor por defecto
    ~SwapChain() = default;

    // Método para inicializar la cadena de intercambio
    // Recibe un dispositivo, un contexto de dispositivo, un búfer de fondo y una ventana
    void 
      init(Device& device, DeviceContext& deviceContext,
           Texture& backBuffer, window window);

    // Método para actualizar la cadena de intercambio
    void 
      update();

    // Método para renderizar usando la cadena de intercambio
    void 
      render();

    // Método para destruir o liberar recursos de la cadena de intercambio
    void 
      destroy();

    // Método para presentar el contenido renderizado
    void 
      present();

public:
    // Puntero a la cadena de intercambio de DirectX
    IDXGISwapChain* m_swapChain = nullptr;
    // Tipo de controlador de Direct3D
    D3D_DRIVER_TYPE m_driverType = D3D_DRIVER_TYPE_NULL;

private:
    // Nivel de características de Direct3D
    D3D_FEATURE_LEVEL m_featureLevel = D3D_FEATURE_LEVEL_11_0;
};


