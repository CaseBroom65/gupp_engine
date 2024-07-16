#include "RenderTargetView.h"
#include "Device.h"
#include "DeviceContext.h"
#include "DepthStencilView.h"
#include "Texture.h"

void RenderTargetView::init(Device device, Texture backBuffer, DXGI_FORMAT Format)
{
    // Verifica si el dispositivo es v�lido
    if (device.m_device == nullptr)
    {
        ERROR("RenderTargetView", "init", "Check for Device device");
        exit(1);
    }
    // Verifica si el backBuffer es v�lido
    else if (backBuffer.m_texture == nullptr)
    {
        ERROR("RenderTargetView", "init", "Check for Texture backBuffer");
        exit(1);
    }

    HRESULT hr = S_OK;

    // Configuraci�n de la descripci�n de la vista de renderizado
    D3D11_RENDER_TARGET_VIEW_DESC desc = {};
    desc.Format = Format; // Formato del render target
    desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D; // Dimensi�n de la vista

    // Crear la vista de renderizado
    hr = device.CreateRenderTargetView(backBuffer.m_texture, &desc, &m_renderTargetView);

    if (FAILED(hr))
    {
        ERROR("RenderTargetView", "init", "Check for CreateRenderTargetView");
        exit(1);
    }
}

void RenderTargetView::update()
{
    // M�todo vac�o para actualizaciones, puede ser implementado m�s adelante
}

void RenderTargetView::render(DeviceContext& deviceContext, DepthStencilView& depthStencilView, unsigned int numViews, float ClearColor[4])
{
    // Limpiar la vista de renderizado con el color especificado
    deviceContext.m_deviceContext->ClearRenderTargetView(m_renderTargetView, ClearColor);
    // Establecer los render targets
    deviceContext.m_deviceContext->OMSetRenderTargets(numViews, &m_renderTargetView, depthStencilView.m_DepthStencilView);
}

void RenderTargetView::destroy()
{
    // Liberar la vista de renderizado
    SAFE_RELEASE(m_renderTargetView);
}
