#pragma once
#include "PreRequisitos.h"

	class Device;
	class DeviceContext;
	class Texture;
	
class DepthStencilView
{
public:
    DepthStencilView() = default;
    ~DepthStencilView() = default;

    /**
     * Inicializa la vista de profundidad y stencil utilizando el dispositivo, la textura y el formato proporcionados.
     *
     * @param device: Una referencia al objeto de dispositivo gráfico.
     * @param depthStencil: Una referencia al objeto de textura de profundidad y stencil.
     * @param format: El valor de enumeración DXGI_FORMAT que especifica el formato de la textura de profundidad y stencil.
     */
    void init(Device & device, Texture & depthStencil, DXGI_FORMAT format);

    /**
     * Actualiza la vista de profundidad y stencil si es necesario. El comportamiento exacto depende del caso de uso específico.
     */
    void update();

    /**
     * Vincula la vista de profundidad y stencil a la etapa de fusión de salida del canal de renderizado.
     *
     * @param deviceContext: Una referencia al objeto de contexto del dispositivo.
     */
    void render(DeviceContext& deviceContext);

    /**
     * Libera los recursos asociados con la vista de profundidad y stencil.
     */
    void destroy();

public:
    ID3D11DepthStencilView* m_DepthStencilView = nullptr; // Puntero a la interfaz ID3D11DepthStencilView
};

