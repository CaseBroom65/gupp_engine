#pragma once
#include "PreRequisitos.h"

// Definición de la clase Device
class Device
{
public:
    // Constructor por defecto
    Device() = default;
    // Destructor por defecto
    ~Device() = default;

    // Método para inicializar el dispositivo
    void init();

    // Método para actualizar el dispositivo
    void update();

    // Método para renderizar usando el dispositivo
    void render();

    // Método para destruir o liberar recursos del dispositivo
    void destroy();

    // Método para crear una vista de renderizado de destino (Render Target View)
    HRESULT CreateRenderTargetView(ID3D11Resource* pResource,
        const D3D11_RENDER_TARGET_VIEW_DESC* pDesc,
        ID3D11RenderTargetView** ppRTView);

    // Método para crear una textura 2D
    HRESULT CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc,
        const D3D11_SUBRESOURCE_DATA* pInitialData,
        ID3D11Texture2D** ppTexture2D);

    // Método para crear una vista de profundidad y stencil (Depth Stencil View)
    HRESULT CreateDepthStencilView(ID3D11Resource* pResource,
        const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc,
        ID3D11DepthStencilView** ppDepthStencilView);

    // Método para crear un shader de vértices (Vertex Shader)
    HRESULT CreateVertexShader(const void* pShaderBytecode,
        unsigned int BytecodeLength,
        ID3D11ClassLinkage* pClassLinkage,
        ID3D11VertexShader** ppVertexShader);

    // Método para crear un diseño de entrada (Input Layout)
    HRESULT CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* pInputElementDescs,
        unsigned int NumElements,
        const void* pShaderBytecodeWithInputSignature,
        unsigned int BytecodeLength,
        ID3D11InputLayout** ppInputLayout);

    // Método para crear un shader de píxeles (Pixel Shader)
    HRESULT CreatePixelShader(const void* pShaderBytecode,
        unsigned int BytecodeLength,
        ID3D11ClassLinkage* pClassLinkage,
        ID3D11PixelShader** ppPixelShader);

    // Método para crear un búfer
    HRESULT CreateBuffer(const D3D11_BUFFER_DESC* pDesc,
        const D3D11_SUBRESOURCE_DATA* pInitialData,
        ID3D11Buffer** ppBuffer);

    // Método para crear un estado de sampler (Sampler State)
    HRESULT CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc, ID3D11SamplerState** ppSamplerState);

public:
    // Puntero al dispositivo de Direct3D 11
    ID3D11Device* m_device = nullptr;
};

