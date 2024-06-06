#include "Device.h"

void Device::init()
{
}

void Device::update()
{
}

void Device::render()
{
}

void Device::destroy()
{
	SAFE_RELEASE(m_device);
}
/// <summary>
/// Input Layout in DirectX 11 is a description of the vertex data that will be sent to the graphics pipeline.
///  It specifies the format and location of the data in the vertex buffers.
///  Constant Buffers in DirectX 11 are blocks of memory that hold data that remains constant for a set of rendering operations,
///  such as matrices, lighting parameters, or material properties. CreateRenderTargetView in DirectX 11 is a method that creates a render target view object,
///  which represents a resource that can be used as the target for rendering operations.
///  This allows the application to write rendering output to a specific resource.
/// </summary>
/// <param name="pResource"></param>
/// <param name="pDesc"></param>
/// <param name="ppRTView"></param>
/// <returns></returns>
HRESULT Device::CreateRenderTargetView(ID3D11Resource* pResource,
									   const D3D11_RENDER_TARGET_VIEW_DESC* pDesc,
										ID3D11RenderTargetView** ppRTView) //son parametros estos sierven para pasar información
{
	HRESULT hr = S_OK;
	//check if the resource and RTView exist
	if (pResource != nullptr || ppRTView != nullptr)
	{
		hr = m_device->CreateRenderTargetView(pResource, pDesc, ppRTView);
		MESSAGE("Device","CreateRenderTargetView","OK")
	}
	else
	{
		ERROR("device", "CreateRenderTargetView", "CHECK FOR ID3D11resource* pResource")
			exit(1);
	}
	return hr;
}

HRESULT Device::CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc,
	                            const D3D11_SUBRESOURCE_DATA* pInitialData, 
								ID3D11Texture2D** ppTexture2D)
{
	HRESULT hr = S_OK;
	//check if the descriptior of the trexture and the texture exist
	if (pDesc != nullptr || ppTexture2D != nullptr)
	{
		hr = m_device->CreateTexture2D(pDesc, pInitialData, ppTexture2D);
		MESSAGE("Device", "CreateTexture2D", "OK")
	}
	else
	{
		ERROR("device", "CreateTexture2D", "CHECK FOR CREATION MRTHOD]")
			exit(1);
	}
	return hr;
}

HRESULT Device::CreateDepthStencilView(ID3D11Resource* pResource,
										const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc, 
										ID3D11DepthStencilView** ppDepthStencilView)
{
	HRESULT hr = S_OK;
	if (pResource == nullptr)
	{
		ERROR("Device", "CreateDepthStencilview", "CHECK FOR ID3D11Resource* pResource")
			exit(1);
	}
	else if (ppDepthStencilView == nullptr)
	{
		ERROR("Device", "CreateDepthStencilview", "CHECK FOR ID3D11DepthStencilView** ppDepthStencilView")
			exit(1);
	}
	else
	{
		hr = m_device->CreateDepthStencilView(pResource, pDesc, ppDepthStencilView);
		MESSAGE("device", "CreateDepthStencilView", "OK")
			
	}
	return hr;
}

HRESULT Device::CreateVertexShader(const void* pShaderBytecode, 
											unsigned int BytecodeLength, 
											ID3D11ClassLinkage* pClassLinkage, 
											ID3D11VertexShader** ppVertexShader)
{
	HRESULT hr = S_OK;
	if (pShaderBytecode == nullptr)
	{
		ERROR("Device", "CreateVertexShader", "CHECK FOR const void * pShaderBytecode")
			exit(1);
	}
	else if (ppVertexShader == nullptr)
	{
		ERROR("Device", "CreateVertexSahder", "CHECK FOR ID3D11VertexShader** ppVertexShader")
			exit(1);
	}
	else
	{
		hr = m_device->CreateVertexShader(pShaderBytecode,
									      BytecodeLength,
										  pClassLinkage, 
										  ppVertexShader);
		MESSAGE("device", "CreateVertexShader", "OK")
	}
	return hr;
}

HRESULT Device::CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* pInputElementDescs, 
											unsigned int NumElements, 
											const void* pShaderBytecodeWithInputSignature,
											unsigned int BytecodeLength, 
											ID3D11InputLayout** ppInputLayout)
{
	HRESULT hr = S_OK;
	if (pInputElementDescs == nullptr)
	{
		ERROR("Device", "CreateInputLayout", "CHECK FOR D3D11_INPUT_ELEMENT_DESC* pInputElementDescs")
			exit(1);
	}
	else if (pShaderBytecodeWithInputSignature == nullptr)
	{
		ERROR("Device", "CreateInputLayout", "CHECK FOR const void* pShaderBytecodeWithInputSignature")
			exit(1);
	}
	else if (ppInputLayout == nullptr)
	{
		ERROR("Device", "CreateInputLayout", "CHECK FOR ID3D11InputLayout** ppInputLayout")
			exit(1);
	}
	else
	{
		hr = m_device->CreateInputLayout(pInputElementDescs,
			NumElements,
			pShaderBytecodeWithInputSignature,
			BytecodeLength,
			ppInputLayout);
		MESSAGE("device", "CreateInputLayout", "OK")
	}
	return hr;
}

HRESULT Device::CreatePixelShader(const void* pShaderBytecode, 
								  unsigned int BytecodeLength, 
								  ID3D11ClassLinkage* pClassLinkage, 
								  ID3D11PixelShader** ppPixelShader)
{
	HRESULT hr = S_OK;
	if (pShaderBytecode == nullptr)
	{
		ERROR("Device", "CreatePixelShader", "CHECK FOR const void* pShaderBytecode")
			exit(1);
	}
	else if (ppPixelShader == nullptr)
	{
		ERROR("Device", "CreatePixelShader", "CHECK FOR ID3D11PixelShader** ppPixelShader")
			exit(1);
	}
	else
	{
		hr = m_device->CreatePixelShader(pShaderBytecode,
			BytecodeLength,
			pClassLinkage,
			ppPixelShader);
		MESSAGE("device", "CreatePixelShader", "OK")
	}
	return hr;
}

HRESULT Device::CreateBuffer(const D3D11_BUFFER_DESC* pDesc, 
							const D3D11_SUBRESOURCE_DATA* pInitialData, 
							ID3D11Buffer** ppBuffer)
{
	HRESULT hr = S_OK;
	if (pDesc == nullptr)
	{
		ERROR("Device", "CreateBuffer", "CHECK FOR const D3D11_BUFFER_DESC* pDesc")
			exit(1);
	}
	else if (ppBuffer == nullptr)
	{
		ERROR("Device", "CreateBuffer", "CHECK FOR ID3D11Buffer** ppBuffer")
			exit(1);
	}
	else
	{
		hr = m_device->CreateBuffer(pDesc,pInitialData, ppBuffer);
		MESSAGE("device", "CreateBuffer", "OK")
	}
	return hr;
}

HRESULT Device::CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc, ID3D11SamplerState** ppSamplerState)
{
	HRESULT hr = S_OK;
	if (pSamplerDesc == nullptr)
	{
		ERROR("Device", "CreateSamplerState", "CHECK FOR const D3D11_SAMPLER_DESC* pSamplerDesc")
			exit(1);
	}
	else if (ppSamplerState == nullptr)
	{
		ERROR("Device", "CreateSamplerState", "CHECK FOR ID3D11SamplerState** ppSamplerState")
			exit(1);
	}
	else
	{
		hr = m_device->CreateSamplerState(pSamplerDesc, ppSamplerState);
		MESSAGE("Device", "CreateSamplerState", "OK")
	}
	return hr;
}
