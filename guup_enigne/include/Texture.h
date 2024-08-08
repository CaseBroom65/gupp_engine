#pragma once
#include "PreRequisitos.h"

class Device;
class DeviceContext;

class Texture
{
public:
    // Constructor por defecto
    Texture() = default;
    // Destructor por defecto
    ~Texture() = default;

    // Método para inicializar la textura desde un archivo
    // Recibe un dispositivo, el nombre de la textura y el tipo de extensión
    HRESULT 
      init(Device device, std::string TextureName, 
           ExtensionType extensionType);

    // Método para inicializar la textura con dimensiones específicas
    // Recibe un dispositivo, el ancho, la altura, el formato DXGI y las banderas de enlace
    void 
      init(Device device, unsigned int width,
           unsigned int height, DXGI_FORMAT Format, 
           unsigned int Bindflags);

    // Método para actualizar la textura
    void 
      update();

    // Método para renderizar usando el contexto del dispositivo
    // Recibe un contexto de dispositivo, la ranura de inicio y el número de vistas
    void
      render(DeviceContext& deviceContext, unsigned int StartSlot, 
             unsigned int NumViews);

    // Método para destruir o liberar recursos de la textura
    void 
      destroy();

public:
    // Variable encargada de manejar un recurso de textura como datos
    ID3D11Texture2D* m_texture = nullptr;
    // Variable encargada de manejar un recurso de textura como datos de imagen
    ID3D11ShaderResourceView* m_textureFromImg = nullptr;
};
