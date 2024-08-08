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

    // M�todo para inicializar el programa de shaders
    // Recibe un dispositivo, un nombre de archivo y un vector de descripciones de elementos de entrada
    void 
      init(Device device, 
           std::string fileName, 
           std::vector<D3D11_INPUT_ELEMENT_DESC> Layout);

    // M�todo para actualizar el programa de shaders
    void 
      update();

    // M�todo para renderizar usando el contexto del dispositivo
    void 
      render(DeviceContext& deviceContext);

    // M�todo para destruir o liberar recursos del programa de shaders
    void 
      destroy();

    // M�todo para compilar un shader desde un archivo
    // Recibe el nombre de archivo, el punto de entrada, el modelo de shader y un puntero de salida a un blob
    HRESULT 
      CompileShaderFromFile(char* szFileName, LPCSTR szEntryPoint,
                            LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

    // M�todo para crear el dise�o de entrada
    // Recibe un dispositivo y un vector de descripciones de elementos de entrada
    void 
      CreateInputLayout(Device device, std::vector<D3D11_INPUT_ELEMENT_DESC> Layout);

    // M�todo para crear un shader
    // Recibe un dispositivo y un tipo de shader
    void 
      CreateShader(Device device, ShaderType type);

public:
    // Puntero al shader de v�rtices de Direct3D 11
    ID3D11VertexShader* m_VertexShader = nullptr;
    // Puntero al shader de p�xeles de Direct3D 11
    ID3D11PixelShader* m_PixelShader = nullptr;
    // Dise�o de entrada
    InputLayout m_inputLayout;

private:
    // Nombre del archivo del shader
    std::string m_shaderFileName;
    // Datos del shader de v�rtices
    ID3DBlob* m_vertexShaderData = nullptr;
    // Datos del shader de p�xeles
    ID3DBlob* m_pixelShaderData = nullptr;
};
