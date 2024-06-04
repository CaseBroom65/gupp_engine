#pragma once
#include "PreRequisitos.h"

//Forward Declarations - declaraciones Directas
class Device;
class DeviceContext;
class window;
class Texture;

class SwapChain
{
public:
	SwapChain() = default;
	~SwapChain()=default;


	void init(Device &device, DeviceContext &deviceContext, Texture &backBuffer, window window);

	void update();

	void render();

	void destroy();

	void present();

public:
	IDXGISwapChain* m_swapChain = nullptr;
	D3D_DRIVER_TYPE m_driverType = D3D_DRIVER_TYPE_NULL;
private:
	D3D_FEATURE_LEVEL m_featureLevel = D3D_FEATURE_LEVEL_11_0;
};

