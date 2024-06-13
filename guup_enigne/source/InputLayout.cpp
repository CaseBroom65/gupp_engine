#include "InputLayout.h"
#include "Device.h"
#include "DeviceContext.h"

void InputLayout::init(Device device, std::vector<D3D11_INPUT_ELEMENT_DESC> Layout, ID3DBlob* VertexshaderData)
{
	if (Layout.size() == 0)
	{
		ERROR("InputLayout", "init", "CHECK FOR std::vector<D3D11_INPUT_ELEMENT_DESC> Layout")
			exit(1);
	}
	else if (VertexshaderData == nullptr)
	{
		ERROR("InputLayout", "init", "CHECK FOR  ID3DBlob* VertexsahderData")
			exit(1);
	}

	HRESULT hr = S_OK;

	hr = device.CreateInputLayout(Layout.data(), Layout.size(),
							VertexshaderData->GetBufferPointer(), 
							VertexshaderData->GetBufferSize(), &m_inputLayout);

		if (FAILED(hr))
		{
			ERROR("InputLayout", "init", "CHECK FOR CreateInputLayout() ")
				exit(1);
		}

}

void InputLayout::update()
{
}

void InputLayout::render(DeviceContext& deviceContext)
{
	deviceContext.IASetInputLayout(m_inputLayout);
}

void InputLayout::destroy()
{
	SAFE_RELEASE(m_inputLayout);
}
