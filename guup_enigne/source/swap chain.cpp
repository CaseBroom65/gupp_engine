#include "swap chain.h" // Incluye el encabezado de la clase SwapChain
#include "Device.h" // Incluye el encabezado para manejar dispositivos gráficos
#include "DeviceContext.h" // Incluye el encabezado para manejar el contexto del dispositivo
#include "Window.h" // Incluye el encabezado de la clase Window
#include "Texture.h" // Incluye el encabezado de la clase Texture

void SwapChain::init(Device& device, DeviceContext& deviceContext, Texture& backBuffer, window window) // Método para inicializar la cadena de intercambio
{
    // Verifica si el recurso de la ventana existe
    if (window.m_hWnd == nullptr)
    {
        ERROR("Swapchain", "init", "CHECK FOR window window")
            exit(1);
    }

    unsigned int createDeviceFlags = 0; // Inicializa las banderas de creación del dispositivo
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG; // Activa el modo de depuración si está en modo debug
#endif

    // Tipos de controladores que se intentarán usar
    D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE, // Controlador de hardware
        D3D_DRIVER_TYPE_WARP, // Controlador WARP (software)
        D3D_DRIVER_TYPE_REFERENCE, // Controlador de referencia
    };
    UINT numDriverTypes = ARRAYSIZE(driverTypes); // Número de tipos de controladores

    // Niveles de características que se intentarán usar
    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0, // Nivel de característica 11.0
        D3D_FEATURE_LEVEL_10_1, // Nivel de característica 10.1
        D3D_FEATURE_LEVEL_10_0, // Nivel de característica 10.0
    };
    unsigned int numFeatureLevels = ARRAYSIZE(featureLevels); // Número de niveles de características

    DXGI_SWAP_CHAIN_DESC sd; // Estructura para describir la cadena de intercambio
    ZeroMemory(&sd, sizeof(sd)); // Limpia la memoria de la estructura
    sd.BufferCount = 1; // Establece el número de buffers
    sd.BufferDesc.Width = window.m_width; // Establece el ancho del buffer
    sd.BufferDesc.Height = window.m_height; // Establece la altura del buffer
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // Establece el formato del buffer
    sd.BufferDesc.RefreshRate.Numerator = 60; // Establece la tasa de refresco
    sd.BufferDesc.RefreshRate.Denominator = 1; // Establece el denominador de la tasa de refresco
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // Establece el uso del buffer
    sd.OutputWindow = window.m_hWnd; // Establece la ventana de salida
    sd.SampleDesc.Count = 1; // Establece el conteo de muestras
    sd.SampleDesc.Quality = 0; // Establece la calidad de las muestras
    sd.Windowed = TRUE; // Establece si la ventana está en modo ventana
    HRESULT hr = S_OK; // Inicializa el resultado HRESULT

    // Intenta crear el dispositivo y la cadena de intercambio
    for (unsigned int driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
    {
        m_driverType = driverTypes[driverTypeIndex]; // Selecciona el tipo de controlador actual
        hr = D3D11CreateDeviceAndSwapChain(NULL, m_driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
            D3D11_SDK_VERSION, &sd, &m_swapChain, &device.m_device, &m_featureLevel, &deviceContext.m_deviceContext); // Crea el dispositivo y la cadena de intercambio

        if (SUCCEEDED(hr)) // Verifica si la creación fue exitosa
        {
            break; // Sale del bucle si fue exitosa
        }

        if (FAILED(hr)) // Verifica si hubo un error en la creación
        {
            ERROR("Swapchain", "init", "CHECK FOR D3D11CreateDeviceAndSwapChain()")
                exit(1); // Salida si falla
        }
    }

    // Crea una vista de destino de renderizado
    hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer.m_texture); // Obtiene el buffer de la cadena de intercambio
    if (FAILED(hr)) // Verifica si hubo un error al obtener el buffer
    {
        ERROR("Swapchain", "init", "CHECK FOR m_swapChain->GetBuffer()")
            exit(1); // Salida si falla
    }
}

void SwapChain::update() // Método vacío para futuras actualizaciones
{
}

void SwapChain::render() // Método vacío para renderizar
{
}

void SwapChain::destroy() // Método para liberar recursos
{
    SAFE_RELEASE(m_swapChain); // Libera la cadena de intercambio
}

void SwapChain::present() // Método para presentar el contenido de la cadena de intercambio
{
    m_swapChain->Present(0, 0); // Presenta el buffer de intercambio
}
