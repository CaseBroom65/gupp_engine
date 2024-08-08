#pragma once
#include "PreRequisitos.h"

class Device;
class DeviceContext;

	class InputLayout
{
public:
    // Constructor por defecto
    InputLayout() = default;
    // Destructor por defecto
    ~InputLayout() = default;

    // M�todo para inicializar el dise�o de entrada
    // Recibe un dispositivo, un vector de descripciones de elementos de entrada y datos del shader de v�rtices
    void
      init(Device device, std::vector<D3D11_INPUT_ELEMENT_DESC> Layout, ID3DBlob* VertexshaderData);

    // M�todo para actualizar el dise�o de entrada
    void 
      update();

    // M�todo para renderizar usando el contexto del dispositivo
    void 
      render(DeviceContext& deviceContext);

    // M�todo para destruir o liberar recursos del dise�o de entrada
    void 
      destroy();

public:
    // Puntero al dise�o de entrada de Direct3D 11
    ID3D11InputLayout* m_inputLayout = nullptr;
    };
