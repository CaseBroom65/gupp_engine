#pragma once
#include "PreRequisitos.h"

class Device;
class Texture;
class DeviceContext;
class DepthStencilView;

class RenderTargetView
{
public:
    // Constructor por defecto
    RenderTargetView() = default;
    // Destructor por defecto
    ~RenderTargetView() = default;

    // Método para inicializar la vista de destino de renderizado
    // Recibe un dispositivo, un búfer de fondo y un formato DXGI
    void init(Device device, Texture backBuffer, DXGI_FORMAT Format);

    // Método para actualizar la vista de destino de renderizado
    void update();

    // Método para renderizar usando el contexto del dispositivo
    // Recibe un contexto de dispositivo, una vista de stencil de profundidad, el número de vistas y un color de limpieza
    void render(DeviceContext& deviceContext, DepthStencilView& depthStencilView,
        unsigned int numViews, float ClearColor[4]);

    // Método para destruir o liberar recursos de la vista de destino de renderizado
    void destroy();

public:
    // Puntero a la vista de destino de renderizado de Direct3D 11
    ID3D11RenderTargetView* m_renderTargetView = nullptr;
};
