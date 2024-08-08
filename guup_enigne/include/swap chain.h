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

    // M�todo para inicializar la cadena de intercambio
    // Recibe un dispositivo, un contexto de dispositivo, un b�fer de fondo y una ventana
    void 
      init(Device& device, DeviceContext& deviceContext,
           Texture& backBuffer, window window);

    // M�todo para actualizar la cadena de intercambio
    void 
      update();

    // M�todo para renderizar usando la cadena de intercambio
    void 
      render();

    // M�todo para destruir o liberar recursos de la cadena de intercambio
    void 
      destroy();

    // M�todo para presentar el contenido renderizado
    void 
      present();

public:
    // Puntero a la cadena de intercambio de DirectX
    IDXGISwapChain* m_swapChain = nullptr;
    // Tipo de controlador de Direct3D
    D3D_DRIVER_TYPE m_driverType = D3D_DRIVER_TYPE_NULL;

private:
    // Nivel de caracter�sticas de Direct3D
    D3D_FEATURE_LEVEL m_featureLevel = D3D_FEATURE_LEVEL_11_0;
};


