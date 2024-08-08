#pragma once
#include "PreRequisitos.h"
#include "InputLayout.h"

class Device;
class DeviceContext;

class ShaderProgram
{
public:
    // Constructor por defecto
    ShaderProgram() = default;
    // Destructor por defecto
    ~ShaderProgram() = default;

    // Método para inicializar el programa de shaders
    // Recibe un dispositivo, un nombre de archivo y un vector de descripciones de elementos de entrada
    void 
      init(Device device, 
           std::string fileName, 
           std::vector<D3D11_INPUT_ELEMENT_DESC> Layout);

    // Método para actualizar el programa de shaders
    void 
      update();

    // Método para renderizar usando el contexto del dispositivo
    void 
      render(DeviceContext& deviceContext);

    // Método para destruir o liberar recursos del programa de shaders
    void 
      destroy();

    // Método para compilar un shader desde un archivo
    // Recibe el nombre de archivo, el punto de entrada, el modelo de shader y un puntero de salida a un blob
    HRESULT 
      CompileShaderFromFile(char* szFileName, LPCSTR szEntryPoint,
                            LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

    // Método para crear el diseño de entrada
    // Recibe un dispositivo y un vector de descripciones de elementos de entrada
    void 
      CreateInputLayout(Device device, std::vector<D3D11_INPUT_ELEMENT_DESC> Layout);

    // Método para crear un shader
    // Recibe un dispositivo y un tipo de shader
    void 
      CreateShader(Device device, ShaderType type);

public:
    // Puntero al shader de vértices de Direct3D 11
    ID3D11VertexShader* m_VertexShader = nullptr;
    // Puntero al shader de píxeles de Direct3D 11
    ID3D11PixelShader* m_PixelShader = nullptr;
    // Diseño de entrada
    InputLayout m_inputLayout;

private:
    // Nombre del archivo del shader
    std::string m_shaderFileName;
    // Datos del shader de vértices
    ID3DBlob* m_vertexShaderData = nullptr;
    // Datos del shader de píxeles
    ID3DBlob* m_pixelShaderData = nullptr;
};
