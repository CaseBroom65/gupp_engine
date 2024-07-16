#include "ShaderProgram.h"
#include "Device.h"
#include "DeviceContext.h"

void ShaderProgram::init(Device device, std::string fileName, std::vector<D3D11_INPUT_ELEMENT_DESC> Layout)
{
    // Verifica si el dispositivo es válido
    if (device.m_device == nullptr)
    {
        ERROR("ShaderProgram", "init", "CHECK FOR Device Device");
        exit(1);
    }
    else if (Layout.size() <= 1)
    {
        ERROR("ShaderProgram", "init", "CHECK FOR vector<D3D11_INPUT_ELEMENT_DESC> Layout.size()");
        exit(1);
    }

    // Almacena el nombre del archivo del shader
    m_shaderFileName = fileName;

    // Crea el vertex shader
    CreateShader(device, ShaderType::VERTEX_SHADER);

    // Crea el InputLayout
    CreateInputLayout(device, Layout);

    // Crea el pixel shader
    CreateShader(device, ShaderType::PIXEL_SHADER);
}

void ShaderProgram::update()
{
    // Método vacío para futuras actualizaciones
}

void ShaderProgram::render(DeviceContext& deviceContext)
{
    // Establecer el InputLayout
    m_inputLayout.render(deviceContext);

    // Establecer los shaders
    deviceContext.VSSetShader(m_VertexShader, nullptr, 0);
    deviceContext.PSSetShader(m_PixelShader, nullptr, 0);
}

void ShaderProgram::destroy()
{
    // Liberar los shaders y el InputLayout
    SAFE_RELEASE(m_VertexShader);
    m_inputLayout.destroy();
    SAFE_RELEASE(m_PixelShader);
}

HRESULT ShaderProgram::CompileShaderFromFile(char* szFileName, LPCSTR szEntryPoint,
    LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
    dwShaderFlags |= D3DCOMPILE_DEBUG; // Habilitar información de depuración
#endif

    ID3DBlob* pErrorBlob;
    // Compilar el shader desde el archivo
    hr = D3DX11CompileFromFile(szFileName, NULL, NULL, szEntryPoint, szShaderModel,
        dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL);
    if (FAILED(hr))
    {
        if (pErrorBlob != NULL)
            OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
        if (pErrorBlob) pErrorBlob->Release();
        return hr;
    }
    if (pErrorBlob) pErrorBlob->Release();

    return S_OK;
}

void ShaderProgram::CreateInputLayout(Device device, std::vector<D3D11_INPUT_ELEMENT_DESC> Layout)
{
    m_inputLayout.init(device, Layout, m_vertexShaderData);
    m_vertexShaderData->Release(); // Liberar los datos del shader después de usarlos
}

void ShaderProgram::CreateShader(Device device, ShaderType type)
{
    HRESULT hr = S_OK;
    ID3DBlob* shaderData = nullptr;
    const char* shaderEntryPoint = (type == PIXEL_SHADER) ? "PS" : "VS";
    const char* shaderModel = (type == PIXEL_SHADER) ? "ps_4_0" : "vs_4_0";

    // Compilar el shader
    hr = CompileShaderFromFile(m_shaderFileName.data(), shaderEntryPoint, shaderModel, &shaderData);

    if (FAILED(hr))
    {
        MessageBox(nullptr, "The FX cannot be compiled. Please run this executable from the directory that contains the FX file.", "Error", MB_OK);
        ERROR("ShaderProgram", "CreateShader", "CHECK FOR CompileShaderFromFile()");
        exit(1);
    }

    // Crear el shader
    if (type == PIXEL_SHADER)
    {
        hr = device.CreatePixelShader(shaderData->GetBufferPointer(), shaderData->GetBufferSize(), nullptr, &m_PixelShader);
    }
    else
    {
        hr = device.CreateVertexShader(shaderData->GetBufferPointer(), shaderData->GetBufferSize(), nullptr, &m_VertexShader);
    }

    if (FAILED(hr))
    {
        shaderData->Release();
        ERROR("ShaderProgram", "CreateShader", "CHECK FOR device.CreateShader()");
        exit(1);
    }

    // Almacenar los datos del shader compilado
    if (type == PIXEL_SHADER)
    {
        m_pixelShaderData = shaderData;
    }
    else
    {
        m_vertexShaderData = shaderData;
    }
}
