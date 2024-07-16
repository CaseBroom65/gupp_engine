#include "depthstencilView.h"
#include "Device.h"
#include "DeviceContext.h"
#include "Texture.h"

// Método para inicializar la vista de profundidad y stencil
void DepthStencilView::init(Device& device, Texture& depthStencil, DXGI_FORMAT format)
{
    // Verifica si el dispositivo es válido
    if (device.m_device == nullptr)
    {
        ERROR("DepthStencilView", "init", "CHECK FOR Device device");
        exit(1);
    }
    // Verifica si la textura de profundidad y stencil es válida
    else if (depthStencil.m_texture == nullptr)
    {
        ERROR("DepthStencilView", "init", "CHECK FOR ID3D11Resources* depthStencil");
        exit(1);
    }

    HRESULT hr = S_OK;
    D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
    memset(&descDSV, 0, sizeof(descDSV)); // Inicializa la descripción a cero

    // Configura la descripción de la vista de profundidad y stencil
    descDSV.Format = format; // Formato de la vista
    descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D; // Tipo de vista
    descDSV.Texture2D.MipSlice = 0; // Nivel de mipmap

    // Crea la vista de profundidad y stencil
    device.CreateDepthStencilView(depthStencil.m_texture, &descDSV, &m_DepthStencilView);

    // Verifica si la creación fue exitosa
    if (FAILED(hr))
    {
        ERROR("DepthStencilView", "init", "CHECK FOR CreateDepthStencilView");
        exit(1);
    }
}

// Método para renderizar y limpiar la vista de profundidad y stencil
void DepthStencilView::render(DeviceContext& deviceContext)
{
    deviceContext.m_deviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

// Método para destruir la vista de profundidad y stencil
void DepthStencilView::destroy()
{
    SAFE_RELEASE(m_DepthStencilView); // Libera el recurso
}
