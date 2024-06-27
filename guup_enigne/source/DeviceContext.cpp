#include "DeviceContext.h"

void DeviceContext::destroy()
{
	SAFE_RELEASE(m_deviceContext);
}

void DeviceContext::PSSetShaderResources(unsigned int StartSlot, unsigned int NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews)
{
	if (ppShaderResourceViews == nullptr)
	{
		ERROR("DeviceContext", "PSSetShaderResources", " CHECK FOR  ID3D11ShaderResourceView* const* ppShaderResourceViews")
			exit(1);
	}
	else
	{
		m_deviceContext->PSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
	}
}
void DeviceContext::RSSetViewports(unsigned int NumViewports, const D3D11_VIEWPORT* pViewports)
{

	if (pViewports == nullptr)
	{
		ERROR("DeviceContext", "RSSetViewports", "CHECK for const D3D11_VIEWPORT* pViewports")
			exit(1);
	}
	else
	{
		m_deviceContext->RSSetViewports(NumViewports, pViewports);
	}
}
/// <summary>
/// In the context of DirectX 11, the `IASetInputLayout(ID3D11InputLayout* pInputLayout)`
///  method sets the input layout object for the input-assembler stage of the graphics pipeline. 
/// The input layout defines how vertex data is interpreted by the graphics processing unit (GPU) 
/// when rendering 3D graphics. It specifies the format and semantic meaning of each element in the vertex data.
///  Setting the appropriate input layout is crucial for ensuring that the vertex data is interpreted correctly
///  by the GPU and rendered properly on the screen.
/// </summary>
/// <param name="pInputLayout"></param>
void DeviceContext::IASetInputLayout(ID3D11InputLayout* pInputLayout)
{

	if (pInputLayout == nullptr)
	{
		ERROR("DeviceContext", "IASetLayout", "CHECK FOR ID3D11InputLayout* pInputLayout")
			exit(1);
	}
	else
	{
		m_deviceContext->IASetInputLayout(pInputLayout);
	}
}

void DeviceContext::VSSetShader(ID3D11VertexShader* pVertexShader, ID3D11ClassInstance* const* ppClassInstances, unsigned int NumClassInstances)
{
	if (pVertexShader == nullptr)
	{
		ERROR("DeviceContext", "VSSetShader", "CHECK FOR ID3D11VertexShader* pVertexShader")
			exit(1);
	}
	else
	{
		m_deviceContext->VSSetShader(pVertexShader, ppClassInstances, NumClassInstances);
	}
}

void DeviceContext::PSSetShader(ID3D11PixelShader* pPixelShader, ID3D11ClassInstance* const* ppClassInstances, unsigned int NumClassInstances)
{
	if (pPixelShader == nullptr)
	{
		ERROR("DeviceContext", "PSSetShader", "CHECK FOR ID3D11PixelShader* pPixelShader")
			exit(1);
	}
	else
	{
		m_deviceContext->PSSetShader(pPixelShader, ppClassInstances, NumClassInstances);
	}
}
void DeviceContext::UpdateSubresource(ID3D11Resource* pDstResource, unsigned int DstSubresource, const D3D11_BOX* pDstBox, const void* pSrcData, unsigned int SrcRowPitch, unsigned int SrcDepthPitch)
{
	m_deviceContext->UpdateSubresource(pDstResource, DstSubresource,
		pDstBox, pSrcData, SrcRowPitch, SrcDepthPitch);
}

void DeviceContext::IASetVertexBuffers(unsigned int StartSlot, unsigned int NumBuffers,
	ID3D11Buffer* const* ppVertexBuffers, const unsigned int* pStrides, const unsigned int* pOffsets)
{
	m_deviceContext->IASetVertexBuffers(StartSlot, NumBuffers, ppVertexBuffers, pStrides, pOffsets);
}

void DeviceContext::IASetIndexBuffer(ID3D11Buffer* pIndexBuffer, DXGI_FORMAT Format, unsigned int Offset)
{
	m_deviceContext->IASetIndexBuffer(pIndexBuffer, Format, Offset);
}
void DeviceContext::PSSetSamplers(unsigned int StartSlot, unsigned int NumSamplers, ID3D11SamplerState* const* ppSamplers)
{
	if (ppSamplers == nullptr)
	{
		ERROR("DeviceContext", "PSSetSamplers", "Check for ID3D11SamplerState* const* ppSamplers");
	}
	else
	{
		m_deviceContext->PSSetSamplers(StartSlot, NumSamplers, ppSamplers);

	}

}
