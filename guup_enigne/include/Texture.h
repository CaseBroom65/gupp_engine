#pragma once
#include "PreRequisitos.h"

class Device;
class DeviceContext;

class Texture
{
public:
	Texture() = default;
	~Texture() = default;

	HRESULT init(Device device, std::string TextureName);

	void init(Device device, unsigned int width, unsigned int height, DXGI_FORMAT Format, unsigned int Bindflags);
	
	void update();

	void render(DeviceContext& deviceContext, unsigned int StartSlot,unsigned int NumViews);


	void destroy();

public:
	//this variable is in change of handle a texture resource as data
	ID3D11Texture2D* m_texture = nullptr;
	//this variable is in change of handle  texture recource as image data
	ID3D11ShaderResourceView* m_textureFromImg;
};
