#include "InputLayout.h"
#include "Device.h"
#include "DeviceContext.h"

void InputLayout::init(Device device, 
                       std::vector<D3D11_INPUT_ELEMENT_DESC> Layout, 
                       ID3DBlob* VertexshaderData){
    // Verifica que el layout tenga elementos
    if (Layout.empty()){
        ERROR("InputLayout", "init", "CHECK FOR std::vector<D3D11_INPUT_ELEMENT_DESC> Layout");
        exit(1);
    }
    // Verifica que los datos del shader no sean nulos
    else if (VertexshaderData == nullptr){
        ERROR("InputLayout", "init", "CHECK FOR ID3DBlob* VertexshaderData");
        exit(1);
    }

    HRESULT hr = S_OK;

    // Crea el input layout utilizando el dispositivo
    hr = device.CreateInputLayout(Layout.data(), Layout.size(),
        VertexshaderData->GetBufferPointer(),
        VertexshaderData->GetBufferSize(), &m_inputLayout);

    // Verifica si la creación falló
    if (FAILED(hr)){
        ERROR("InputLayout", "init", "CHECK FOR CreateInputLayout()");
        exit(1);
    }
}

void InputLayout::update(){
    // Método de actualización vacío
}

void InputLayout::render(DeviceContext& deviceContext){
    // Establece el input layout en el contexto del dispositivo
    deviceContext.IASetInputLayout(m_inputLayout);
}

void InputLayout::destroy(){
    // Libera el input layout
    SAFE_RELEASE(m_inputLayout);
}
