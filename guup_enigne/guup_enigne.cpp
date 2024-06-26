//--------------------------------------------------------------------------------------
// File: guup_enigne.cpp
//
// This application demonstrates texturing
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#include "PreRequisitos.h"
#include "Window.h"
#include "Device.h"
#include "DeviceContext.h"
#include "swap chain.h"
#include "Texture.h"
#include "depthstencilView.h"
#include "RenderTargetView.h"
#include "ViewPort.h"
#include "ShaderProgram.h"
#include "Buffer.h"
#include "SampleState.h"

//--------------------------------------------------------------------------------------
// Structures
//--------------------------------------------------------------------------------------



//--------------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------------

window                                  g_window;
Device									g_device;
DeviceContext							g_deviceContext;
SwapChain								g_swapchain;
Texture									g_BackBuffer;
Texture									g_DepthStencil;
DepthStencilView						g_depthStencilView;
RenderTargetView						g_RenderTargetView;
Viewport								g_viewport;
ShaderProgram							g_shaderProgram;
Buffer									g_vertexBuffer;
Buffer									g_indexBuffer;
Buffer									g_CBBufferNeverChanges;
Buffer									g_CBBufferChangeOnResize;
Buffer									g_CBBufferChangesEveryFrame;
Mesh									g_mesh;
Texture									g_modelTexture;
SamplerState							g_sampler;


XMMATRIX                            g_World;
XMMATRIX                            g_View;
XMMATRIX                            g_Projection;
XMFLOAT4                            g_vMeshColor(0.7f, 0.7f, 0.7f, 1.0f);
CBNeverChanges                      cbNeverChanges;
CBChangeOnResize                    cbChangesOnResize;
CBChangesEveryFrame                 cb;

//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------

HRESULT InitDevice();
void CleanupDevice();
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void Render();

void Update(float DeltaTime);

//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	if (FAILED(g_window.init(hInstance, nCmdShow, WndProc)))
		return 0;

	if (FAILED(InitDevice()))
	{
		CleanupDevice();
		return 0;
	}

	// Main message loop
	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// Update our time
			static float t = 0.0f;
			if (g_swapchain.m_driverType == D3D_DRIVER_TYPE_REFERENCE)
			{
				t += (float)XM_PI * 0.0125f;
			}
			else
			{
				static DWORD dwTimeStart = 0;
				DWORD dwTimeCur = GetTickCount();
				if (dwTimeStart == 0)
					dwTimeStart = dwTimeCur;
				t = (dwTimeCur - dwTimeStart) / 1000.0f;
			}

			Update(t);
			Render();
		}
	}

	CleanupDevice();

	return (int)msg.wParam;
}


//--------------------------------------------------------------------------------------
// Register class and create window
//--------------------------------------------------------------------------------------



//--------------------------------------------------------------------------------------
// Helper for compiling shaders with D3DX11
//--------------------------------------------------------------------------------------
HRESULT CompileShaderFromFile(char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* pErrorBlob;
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


//--------------------------------------------------------------------------------------
// Create Direct3D device and swap chain
//--------------------------------------------------------------------------------------
HRESULT InitDevice()
{
	HRESULT hr = S_OK;

	/*
		UINT createDeviceFlags = 0;
	#ifdef _DEBUG
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
	#endif

		D3D_DRIVER_TYPE driverTypes[] =
		{
			D3D_DRIVER_TYPE_HARDWARE,
			D3D_DRIVER_TYPE_WARP,
			D3D_DRIVER_TYPE_REFERENCE,
		};
		UINT numDriverTypes = ARRAYSIZE(driverTypes);

		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
		};
		UINT numFeatureLevels = ARRAYSIZE(featureLevels);

		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.BufferCount = 1;
		sd.BufferDesc.Width = g_window.m_width;
		sd.BufferDesc.Height = g_window.m_height;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = g_window.m_hWnd;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.Windowed = TRUE;

		for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
		{
			g_driverType = driverTypes[driverTypeIndex];
			hr = D3D11CreateDeviceAndSwapChain(NULL, g_driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
				D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_device.m_device, &g_featureLevel, &g_deviceContext.m_deviceContext);
			if (SUCCEEDED(hr))
				break;
		}
		if (FAILED(hr))
			return hr;*/

			// Create a render target view
			//hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			// //if (FAILED(hr))
				//return hr;
			
	//create Swapchain
	g_swapchain.init(g_device, g_deviceContext, g_BackBuffer, g_window);

	//create render target view
	g_RenderTargetView.init(g_device, g_BackBuffer, DXGI_FORMAT_R8G8B8A8_UNORM);


	// Create depth stencil texture
	g_DepthStencil.init(g_device, g_window.m_width
		, g_window.m_height,
		DXGI_FORMAT_D24_UNORM_S8_UINT, D3D11_BIND_DEPTH_STENCIL);
	

	// Create the depth stencil view
	g_depthStencilView.init(g_device, g_DepthStencil, DXGI_FORMAT_D24_UNORM_S8_UINT);

	g_viewport.init(g_window);

	// Compile the vertex shader
	//ID3DBlob* pVSBlob = NULL;
	//hr = CompileShaderFromFile("guup_enigne.fx", "VS", "vs_4_0", &pVSBlob);
	//if (FAILED(hr))
	//{
	//	MessageBox(NULL,
	//		"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error", MB_OK);
	//	return hr;
	//}

	// Create the vertex shader
	//hr = g_device.m_device->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &g_pVertexShader);
	/*hr = g_device.CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &g_pVertexShader);
	if (FAILED(hr))
	{
		pVSBlob->Release();
		return hr;
	}*/

	//define the inputLayout

	std::vector<D3D11_INPUT_ELEMENT_DESC>Layout;

	D3D11_INPUT_ELEMENT_DESC position;
	position.SemanticName = "POSITION";
	position.SemanticIndex = 0;
	position.Format = DXGI_FORMAT_R32G32B32_FLOAT;
	position.InputSlot = 0;
	position.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT /*12*/;
	position.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	position.InstanceDataStepRate = 0;
	Layout.push_back(position);

	D3D11_INPUT_ELEMENT_DESC texcoord;;
	texcoord.SemanticName = "TEXCOORD";
	texcoord.SemanticIndex = 0;
	texcoord.Format = DXGI_FORMAT_R32G32_FLOAT;
	texcoord.InputSlot = 0;
	texcoord.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT /*12*/;
	texcoord.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	texcoord.InstanceDataStepRate = 0;
	Layout.push_back(texcoord);

	g_shaderProgram.init(g_device, "guup_enigne.fx", Layout);




	// Create vertex buffer
	SimpleVertex vertices[] =
	{
		{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

		{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

		{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(0.0f, 1.0f) },

		{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },
	};

	g_mesh.name = "Cube";

	// Set vertex buffer
	for (const SimpleVertex& vertex : vertices)
	{
		g_mesh.vertex.push_back(vertex);
	}

	//// NOTA: El static_cast<unsigned int�
	//se est� utilizando aqu� para convertir el resultado del m�todo size() 
	//    de un std::vector a un tipo unsigned int.
	//    El m�todo size() devuelve un valor del tipo std::size_t, 
	//    que es un tipo espec�fico de tama�o no negativo.En algunas 
	//    plataformas, std : size_t puede ser de un tama�o diferente a unsigned int. /

	g_mesh.numVertex = static_cast<unsigned int>(g_mesh.vertex.size());


	// Create vertex buffer
	g_vertexBuffer.init(g_device, g_mesh, D3D11_BIND_VERTEX_BUFFER);

	// Create index buffer
	unsigned int indices[] =
	{
		3,1,0,
		2,1,3,

		6,4,5,
		7,4,6,

		11,9,8,
		10,9,11,

		14,12,13,
		15,12,14,

		19,17,16,
		18,17,19,

		22,20,21,
		23,20,22
	};

	for (unsigned int index : indices) {
		g_mesh.index.push_back(index);
	}
	g_mesh.numIndex = static_cast<unsigned int>(g_mesh.index.size());

	// Set index buffer
	g_indexBuffer.init(g_device, g_mesh, D3D11_BIND_INDEX_BUFFER);

	// Inicializaci�n de Constant Buffers
	g_CBBufferNeverChanges.init(g_device, sizeof(CBNeverChanges));

	g_CBBufferChangeOnResize.init(g_device, sizeof(CBChangeOnResize));

	g_CBBufferChangesEveryFrame.init(g_device, sizeof(CBChangesEveryFrame));



	// Load the Texture
	g_modelTexture.init(g_device, "seafloor.dds");
	//Create SamplerState
	g_sampler.init(g_device);

	// Initialize the world matrices
	g_World = XMMatrixIdentity();

	// Initialize the view matrix
	XMVECTOR Eye = XMVectorSet(0.0f, 3.0f, -6.0f, 0.0f);
	XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	g_View = XMMatrixLookAtLH(Eye, At, Up);

	cbNeverChanges.mView = XMMatrixTranspose(g_View);


	// Initialize the projection matrix
	g_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, g_window.m_width / (FLOAT)g_window.m_height, 0.01f, 100.0f);

	CBChangeOnResize cbChangesOnResize;
	cbChangesOnResize.mProjection = XMMatrixTranspose(g_Projection);
	g_CBBufferChangeOnResize.update(g_deviceContext, 0, nullptr, &cbChangesOnResize, 0, 0);

	return S_OK;
}


//--------------------------------------------------------------------------------------
// Clean up the objects we've created
//--------------------------------------------------------------------------------------
void CleanupDevice()
{
	if (g_deviceContext.m_deviceContext) g_deviceContext.m_deviceContext->ClearState();


	g_sampler.destroy();
	g_modelTexture.destroy();
	g_shaderProgram.destroy();
	g_DepthStencil.destroy();
	g_depthStencilView.destroy();
	g_RenderTargetView.destroy();
	g_swapchain.destroy();
	g_deviceContext.destroy();
	g_device.destroy();
	g_CBBufferNeverChanges.destroy();
	g_CBBufferChangeOnResize.destroy();
	g_CBBufferChangesEveryFrame.destroy();
	g_vertexBuffer.destroy();
	g_indexBuffer.destroy();
}
//Update everyframe
void Update(float DeltaTime)
{
	// Rotate cube around the origin
	g_World = XMMatrixRotationY(DeltaTime);
	// Modify the color
	g_vMeshColor.x = (sinf(DeltaTime * 1.0f) + 1.0f) * 0.5f;
	g_vMeshColor.y = (cosf(DeltaTime * 3.0f) + 1.0f) * 0.5f;
	g_vMeshColor.z = (sinf(DeltaTime * 5.0f) + 1.0f) * 0.5f;
	//Update Constant Buffers
	g_CBBufferNeverChanges.update(g_deviceContext, 0, nullptr, &cbNeverChanges, 0, 0);
	g_CBBufferChangeOnResize.update(g_deviceContext, 0, nullptr, &cbChangesOnResize, 0, 0);
	cb.mWorld = XMMatrixTranspose(g_World);
	cb.vMeshColor = g_vMeshColor;
	g_CBBufferChangesEveryFrame.update(g_deviceContext, 0, nullptr, &cb, 0, 0);
}

//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	PAINTSTRUCT ps;
//	HDC hdc;
//
//	switch (message)
//	{
//	case WM_PAINT:
//		hdc = BeginPaint(hWnd, &ps);
//		EndPaint(hWnd, &ps);
//		break;
//
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		break;
//
//	default:
//		return DefWindowProc(hWnd, message, wParam, lParam);
//	}
//
//	return 0;
//}


//--------------------------------------------------------------------------------------
// Render a frame
//--------------------------------------------------------------------------------------
void Render()
{
	// Clear the back buffer
	
	float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha
	g_RenderTargetView.render(g_deviceContext,g_depthStencilView,1,ClearColor);

	g_viewport.render(g_deviceContext);
	//
	// Clear the depth buffer to 1.0 (max depth)
	//
	//g_deviceContext.m_deviceContext->ClearDepthStencilView(g_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	g_depthStencilView.render(g_deviceContext);
	// Render the cube
	//
	g_shaderProgram.render(g_deviceContext);
	g_vertexBuffer.render(g_deviceContext, 0, 1);
	g_indexBuffer.render(g_deviceContext, DXGI_FORMAT_R32_UINT);
	g_CBBufferNeverChanges.render(g_deviceContext, 0, 1); // Slot 0
	g_CBBufferChangeOnResize.render(g_deviceContext, 1, 1); // Slot 1
	g_CBBufferChangesEveryFrame.renderModel(g_deviceContext, 2, 1); // Slot 2
	g_modelTexture.render(g_deviceContext, 0, 1);
	//g_deviceContext.m_deviceContext->PSSetShaderResources( 0, 1, &g_pTextureRV );
	g_sampler.render(g_deviceContext, 0, 1);
	//Set primitve topology
	g_deviceContext.m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	g_deviceContext.m_deviceContext->DrawIndexed(g_mesh.numIndex, 0, 0);

	//
	// Present our back buffer to our front buffer
	//
	//g_pSwapChain->Present(0, 0);
	g_swapchain.present();
}
