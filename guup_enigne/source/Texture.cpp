#define STB_IMAGE_IMPLEMENTATION // Define la implementación de la biblioteca STB para cargar imágenes
#include "stb_image.h" // Incluye la biblioteca STB para cargar imágenes
#include "Texture.h" // Incluye el encabezado de la clase Texture
#include "Device.h" // Incluye el encabezado para manejar dispositivos gráficos
#include "DeviceContext.h" // Incluye el encabezado para manejar el contexto del dispositivo

HRESULT Texture::init(Device device, std::string TextureName, ExtensionType extensionType)
{
    if (device.m_device == nullptr) // Verifica si el dispositivo es nulo
    {
        ERROR("Texture", "init", "CHECK FOR Device device on texture loading method")
    }
    HRESULT hr = S_OK; // Inicializa hr a S_OK
    switch (extensionType) // Comienza un bloque switch para manejar tipos de extensiones
    {
    case DDS: // Caso para DDS
        hr = D3DX11CreateShaderResourceViewFromFile(device.m_device, TextureName.c_str(), nullptr, nullptr, &m_textureFromImg, nullptr); // Crea la vista de recurso de shader desde un archivo
        if (FAILED(hr))
        {
            ERROR("Texture", "init", "Error in data from params[CHECK FOR String textureName -> Verify correct name in File]")
                exit(1);
        }
        break;
    case PNG:
        int width, height, channels; // Declara variables para dimensiones y canales
        unsigned char* data = stbi_load(TextureName.c_str(), &width, &height, &channels, 4); // Carga la imagen en formato RGBA
        if (!data)
        {
            ERROR("Texture", "stibi_load", "Error al cargar la imagen:" << stbi_failure_reason())
                return E_FAIL; // Verifica si la carga fue exitosa
        }
        D3D11_TEXTURE2D_DESC textureDesc = {}; // Crea una descripción de la textura
        textureDesc.Width = width; // Establece el ancho
        textureDesc.Height = height; // Establece la altura
        textureDesc.MipLevels = 1; // Establece los niveles de mipmap
        textureDesc.ArraySize = 1; // Establece el tamaño de la matriz
        textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // Establece el formato
        textureDesc.SampleDesc.Count = 1; // Establece el conteo de muestras
        textureDesc.Usage = D3D11_USAGE_DEFAULT; // Establece el uso
        textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE; // Establece las banderas de enlace
        D3D11_SUBRESOURCE_DATA initData = {}; // Datos de sobrecarga
        initData.pSysMem = data; // Puntero a los datos de la imagen
        initData.SysMemPitch = width * 4; // 4 bytes por pixel

        ID3D11Texture2D* texture = nullptr; // Declara un puntero para la textura
        hr = device.CreateTexture2D(&textureDesc, &initData, &texture); // Crea la textura
        if (FAILED(hr))
        {
            stbi_image_free(data); // Libera los datos de la imagen
            return hr; // Retorna el error
        }
        D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {}; // Descripción del recurso de la textura
        srvDesc.Format = textureDesc.Format; // Establece el formato
        srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D; // Establece la dimensión
        srvDesc.Texture2D.MipLevels = 1; // Establece los niveles de mipmap
        hr = device.m_device->CreateShaderResourceView(texture, &srvDesc, &m_textureFromImg); // Crea la vista de recurso de shader
        texture->Release(); // Libera la textura
        stbi_image_free(data); // Libera los datos de la imagen
        break;
    }
}

void Texture::init(Device device, unsigned int width, unsigned int height, DXGI_FORMAT Format, unsigned int Bindflags)
{
    if (device.m_device == nullptr) // Verifica si el dispositivo es nulo
    {
        ERROR("Texture", "init", "CHECK FOR Device device on texture loading method")
            exit(1);
    }
    else if (width <= 0 || height <= 0) // Verifica las dimensiones
    {
        ERROR("Texture", "init", "CHECK FOR unsigned int width OR unsigned int height")
            exit(1);
    }
    HRESULT hr = S_OK; // Inicializa hr a S_OK

    D3D11_TEXTURE2D_DESC desc; // Crea una descripción de textura
    memset(&desc, 0, sizeof(desc)); // Limpia la memoria de la descripción
    desc.Width = width; // Establece el ancho
    desc.Height = height; // Establece la altura
    desc.MipLevels = 1; // Establece los niveles de mipmap
    desc.ArraySize = 1; // Establece el tamaño de la matriz
    desc.Format = Format; // Establece el formato
    desc.SampleDesc.Count = 1; // Establece el conteo de muestras
    desc.SampleDesc.Quality = 0; // Establece la calidad de muestras
    desc.Usage = D3D11_USAGE_DEFAULT; // Establece el uso
    desc.BindFlags = Bindflags; // Establece las banderas de enlace

    hr = device.CreateTexture2D(&desc, nullptr, &m_texture); // Crea la textura
    if (m_texture == nullptr) // Verifica si la textura es nula
    {
        ERROR("Texture", "init", "Error in data from params [CHECK FOR m_texture]")
            exit(1);
    }
    else if (FAILED(hr)) // Verifica si la creación falló
    {
        ERROR("Texture", "init", "Error in data from resources [CHECK FOR CreateTexture2D]")
            exit(1);
    }
}

void Texture::update()
{
    // Método vacío para futuras actualizaciones
}

void Texture::render(DeviceContext& deviceContext, unsigned int StartSlot, unsigned int NumViews)
{
    if (m_textureFromImg != nullptr) // Verifica si hay una textura cargada
    {
        ID3D11ShaderResourceView* nullSRV[] = { nullptr }; // Crea un array nulo para limpiar recursos
        deviceContext.PSSetShaderResources(StartSlot, NumViews, nullSRV); // Limpia los recursos anteriores
        deviceContext.PSSetShaderResources(StartSlot, NumViews, &m_textureFromImg); // Establece la nueva textura en el contexto
    }
}

void Texture::destroy()
{
    if (m_texture != nullptr) // Verifica si la textura es válida
    {
        SAFE_RELEASE(m_texture); // Libera la textura
    }
    else if (m_textureFromImg != nullptr) // Verifica si la textura de imagen es válida
    {
        SAFE_RELEASE(m_textureFromImg); // Libera la textura de imagen
    }
}
