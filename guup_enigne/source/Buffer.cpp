#include "Buffer.h"
#include "Device.h"
#include "DeviceContext.h"
#include "MeshComponent.h"

// Método privado para crear un búfer
void Buffer::createBuffer(Device& device,
                          D3D11_BUFFER_DESC& desc,
                          D3D11_SUBRESOURCE_DATA* initData) {
                          // Intenta crear el búfer utilizando el dispositivo
                          HRESULT hr = device.CreateBuffer(&desc, initData, &m_buffer);
                          if (FAILED(hr)) {
                              ERROR("Buffer", "createBuffer", "CHECK FOR method createBuffer()");
                          }
                      }

void Buffer::init(Device device, MeshComponent mesh, unsigned int bindFlag) {
    // Verifica si el dispositivo es válido
    if (device.m_device == nullptr) {
        ERROR("Buffer", "init", "CHECK FOR Device device");
    }

    // Valida los datos de la malla según el flag de enlace
    if ((bindFlag == D3D11_BIND_VERTEX_BUFFER && mesh.m_vertex.empty()) ||
        (bindFlag == D3D11_BIND_INDEX_BUFFER && mesh.m_index.empty())) {
        ERROR("Buffer", "init", "CHECK FOR Mesh mesh");
    }

    D3D11_BUFFER_DESC desc = {};
    D3D11_SUBRESOURCE_DATA InitData = {};

    // Configuración del búfer
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.CPUAccessFlags = 0;
    m_bindFlag = bindFlag;

    // Inicializa el búfer de vértices
    if (bindFlag == D3D11_BIND_VERTEX_BUFFER) {
        m_stride = sizeof(SimpleVertex);
        desc.ByteWidth = m_stride * static_cast<unsigned int>(mesh.m_vertex.size());
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        InitData.pSysMem = mesh.m_vertex.data();
    }
    // Inicializa el búfer de índices
    else if (bindFlag == D3D11_BIND_INDEX_BUFFER) {
        m_stride = sizeof(unsigned int);
        desc.ByteWidth = m_stride * static_cast<unsigned int>(mesh.m_index.size());
        desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
        InitData.pSysMem = mesh.m_index.data();
    }

    // Crea el búfer
    createBuffer(device, desc, &InitData);
}

void Buffer::init(Device device, unsigned int ByteWidth) {
    // Verifica parámetros de entrada
    if (device.m_device == nullptr || ByteWidth == 0) {
        ERROR("Buffer", "init", "CHECK FOR parameters");
    }

    m_stride = ByteWidth;

    D3D11_BUFFER_DESC desc = {};
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.ByteWidth = ByteWidth;
    desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    m_bindFlag = desc.BindFlags;

    // Crea el búfer de constantes
    createBuffer(device, desc, nullptr);
}

void Buffer::update(DeviceContext& deviceContext,
                    unsigned int DstSubresource,
                    const D3D11_BOX* pDstBox,
                    const void* pSrcData,
                    unsigned int SrcRowPitch,
                    unsigned int SrcDepthPitch) {

    // Actualiza el búfer con los nuevos datos
    deviceContext.UpdateSubresource(m_buffer,
        DstSubresource,
        pDstBox,
        pSrcData,
        SrcRowPitch,
        SrcDepthPitch);
}

void Buffer::render(DeviceContext& deviceContext,
                    unsigned int StartSlot,
                    unsigned int NumBuffers) {
                    // Renderiza según el tipo de búfer
                    switch (m_bindFlag) {
                    case D3D11_BIND_VERTEX_BUFFER:
                        deviceContext.IASetVertexBuffers(StartSlot,
                            NumBuffers,
                            &m_buffer,
                            &m_stride,
                            &m_offset);
                        break;
                    case D3D11_BIND_CONSTANT_BUFFER:
                        deviceContext.m_deviceContext->VSSetConstantBuffers(StartSlot,
                            NumBuffers,
                            &m_buffer);
                        break;
                    default:
                        ERROR("Buffer", "render", "CHECK FOR Unsupported BindFlag");
                        break;
                    }
                }

void Buffer::render(DeviceContext& deviceContext, DXGI_FORMAT format) {
    // Renderiza el búfer de índices
    if (m_bindFlag == D3D11_BIND_INDEX_BUFFER) {
        deviceContext.IASetIndexBuffer(m_buffer, format, m_offset);
    }
    else {
        ERROR("Buffer", "render", "CHECK FOR Unsupported BindFlag");
    }
}

void Buffer::renderModel(DeviceContext& deviceContext,
                         unsigned int StartSlot,
                         unsigned int NumBuffers) {
                          // Configura los búferes de constantes para el shader de vértices y píxeles
                          deviceContext.m_deviceContext->VSSetConstantBuffers(StartSlot,
                              NumBuffers,
                              &m_buffer);

                          deviceContext.m_deviceContext->PSSetConstantBuffers(StartSlot,
                              NumBuffers,
                              &m_buffer);
                      }

void Buffer::destroy() {
    // Libera el búfer
    SAFE_RELEASE(m_buffer);
}
