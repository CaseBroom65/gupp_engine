#pragma once
#include "PreRequisitos.h"

// Definici�n de la clase Device
class Device
{
public:
    // Constructor por defecto
    Device() = default;
    // Destructor por defecto
    ~Device() = default;

    // M�todo para inicializar el dispositivo
    void init();

    // M�todo para actualizar el dispositivo
    void update();

    // M�todo para renderizar usando el dispositivo
    void render();

    // M�todo para destruir o liberar recursos del dispositivo
    void destroy();

    // M�todo para crear una vista de renderizado de destino (Render Target View)
    HRESULT CreateRenderTargetView(ID3D11Resource* pResource,
        const D3D11_RENDER_TARGET_VIEW_DESC* pDesc,
        ID3D11RenderTargetView** ppRTView);

    // M�todo para crear una textura 2D
    HRESULT CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc,
        const D3D11_SUBRESOURCE_DATA* pInitialData,
        ID3D11Texture2D** ppTexture2D);

    // M�todo para crear una vista de profundidad y stencil (Depth Stencil View)
    HRESULT CreateDepthStencilView(ID3D11Resource* pResource,
        const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc,
        ID3D11DepthStencilView** ppDepthStencilView);

    // M�todo para crear un shader de v�rtices (Vertex Shader)
    HRESULT CreateVertexShader(const void* pShaderBytecode,
        unsigned int BytecodeLength,
        ID3D11ClassLinkage* pClassLinkage,
        ID3D11VertexShader** ppVertexShader);

    // M�todo para crear un dise�o de entrada (Input Layout)
    HRESULT CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* pInputElementDescs,
        unsigned int NumElements,
        const void* pShaderBytecodeWithInputSignature,
        unsigned int BytecodeLength,
        ID3D11InputLayout** ppInputLayout);

    // M�todo para crear un shader de p�xeles (Pixel Shader)
    HRESULT CreatePixelShader(const void* pShaderBytecode,
        unsigned int BytecodeLength,
        ID3D11ClassLinkage* pClassLinkage,
        ID3D11PixelShader** ppPixelShader);

    // M�todo para crear un b�fer
    HRESULT CreateBuffer(const D3D11_BUFFER_DESC* pDesc,
        const D3D11_SUBRESOURCE_DATA* pInitialData,
        ID3D11Buffer** ppBuffer);

    // M�todo para crear un estado de sampler (Sampler State)
    HRESULT CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc, ID3D11SamplerState** ppSamplerState);

public:
    // Puntero al dispositivo de Direct3D 11
    ID3D11Device* m_device = nullptr;
};

