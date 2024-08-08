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

    // Método para inicializar el diseño de entrada
    // Recibe un dispositivo, un vector de descripciones de elementos de entrada y datos del shader de vértices
    void
      init(Device device, std::vector<D3D11_INPUT_ELEMENT_DESC> Layout, ID3DBlob* VertexshaderData);

    // Método para actualizar el diseño de entrada
    void 
      update();

    // Método para renderizar usando el contexto del dispositivo
    void 
      render(DeviceContext& deviceContext);

    // Método para destruir o liberar recursos del diseño de entrada
    void 
      destroy();

public:
    // Puntero al diseño de entrada de Direct3D 11
    ID3D11InputLayout* m_inputLayout = nullptr;
    };
