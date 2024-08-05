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
#include "ModelLoader.h"
//#include "fbxsdk.h"
#include "UserInterface.h"
#include "Actor.h"
//#include <Transform.h>


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
std::vector<Buffer>						g_vertexBuffers;
std::vector<Buffer>						g_indexBuffers;
Buffer									g_CBBufferNeverChanges;
Buffer									g_CBBufferChangeOnResize;
Buffer									g_CBBufferChangesEveryFrame;                 
//MeshComponent                       MC;
//Mesh									g_mesh;
std::vector<Texture>					modelTextures;
SamplerState							g_sampler;
ModelLoader								g_model;
Texture									g_default;
std::vector<Texture>gridTexs;
UserInterface                            g_UserInterface;

//XMMATRIX                            g_World;
XMMATRIX                            g_View;
XMMATRIX                            g_Projection;
XMFLOAT4                            g_vMeshColor(0.7f, 0.7f, 0.7f, 1.0f);
CBNeverChanges                      cbNeverChanges;
CBChangeOnResize                    cbChangesOnResize;
CBChangesEveryFrame                 cb;

//EngineUtilities::TSharedPointer<Actor> grid;
EngineUtilities::TSharedPointer<Actor> AVela;
//std::vector<Texture> gridTexs;

//EngineUtilities
//---------------
// -----------------------------------------------------------------------
//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------

HRESULT InitDevice();
void CleanupDevice();
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void Render();

void Update(double DeltaTime);

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

	//load model
	g_model.LoadModel("Models/Vela2.fbx");
	/* {
		g_mesh.vertex.push_back(vertex);
	}*/

	//// NOTA: El static_cast<unsigned int›
	//se está utilizando aquí para convertir el resultado del método size() 
	//    de un std::vector a un tipo unsigned int.
	//    El método size() devuelve un valor del tipo std::size_t, 
	//    que es un tipo específico de tamaño no negativo.En algunas 
	//    plataformas, std : size_t puede ser de un tamaño diferente a unsigned int. /

	//// Create vertex buffer
 //// Create vertex buffer
	//for (auto& mesh : g_model.meshes)
	//{
	//    Buffer vertexBuffer;
	//    vertexBuffer.init(g_device, mesh, D3D11_BIND_VERTEX_BUFFER);
	//    g_vertexBuffers.push_back(vertexBuffer);
	//   
	//   // // Create index buffer
	//    Buffer indexBuffer;
	//    indexBuffer.init(g_device, mesh, D3D11_BIND_INDEX_BUFFER);
	//    g_indexBuffers.push_back(indexBuffer);
	//}

	// g_mesh.index = g_model.GetIndices();
	// g_mesh.numIndex = static_cast<unsigned int>(g_mesh.index.size());
	// // g_indexBuffer.init(g_device, g_mesh, D3D11_BIND_INDEX_BUFFER);


	// Inicialización de Constant Buffers
	g_CBBufferNeverChanges.init(g_device, sizeof(CBNeverChanges));

	g_CBBufferChangeOnResize.init(g_device, sizeof(CBChangeOnResize));

	/*g_CBBufferChangesEveryFrame.init(g_device, sizeof(CBChangesEveryFrame));*/

	////Create SamplerState
	//g_sampler.init(g_device);

	//// Initialize the world matrices
	//g_World = XMMatrixIdentity();

	// Load the Texture
	Texture Vela_Char_BaseColor;
	Vela_Char_BaseColor.init(g_device, "Textures/Vela/Vela_Char_BaseColor.png", ExtensionType::PNG);

	Texture Vela_Corneas_BaseColor;
	Vela_Corneas_BaseColor.init(g_device, "Textures/Vela/Vela_Corneas_BaseColor.png", ExtensionType::PNG);

	Texture Vela_Gun_BaseColor;
	Vela_Gun_BaseColor.init(g_device, "Textures/Vela/Vela_Gun_BaseColor.png", ExtensionType::PNG);

	Texture Vela_Legs_BaseColor;
	Vela_Legs_BaseColor.init(g_device, "Textures/Vela/Vela_Legs_BaseColor.png", ExtensionType::PNG);

	Texture Vela_Mechanical_BaseColor;
	Vela_Mechanical_BaseColor.init(g_device, "Textures/Vela/Vela_Mechanical_BaseColor.png", ExtensionType::PNG);

	Texture Vela_Plate_BaseColor;
	Vela_Plate_BaseColor.init(g_device, "Textures/Vela/Vela_Plate_BaseColor.png", ExtensionType::PNG);

	Texture Vela_Visor_BaseColor;
	Vela_Visor_BaseColor.init(g_device, "Textures/Vela/Vela_Visor_BaseColor.png", ExtensionType::PNG);

	modelTextures.push_back(Vela_Corneas_BaseColor);		//1
	modelTextures.push_back(Vela_Gun_BaseColor);			//2
	modelTextures.push_back(Vela_Visor_BaseColor);			//3
	modelTextures.push_back(Vela_Legs_BaseColor);			//4
	modelTextures.push_back(Vela_Mechanical_BaseColor);		//5
	modelTextures.push_back(Vela_Char_BaseColor);			//6
	modelTextures.push_back(Vela_Plate_BaseColor);			//7
	g_default.init(g_device, "Textures/Default.png", ExtensionType::PNG);

	// Initialize the view matrix
	XMVECTOR Eye = XMVectorSet(0.0f, 3.0f, -6.0f, 0.0f);
	XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	g_View = XMMatrixLookAtLH(Eye, At, Up);

	cbNeverChanges.mView = XMMatrixTranspose(g_View);


	// Initialize the projection matrix
	g_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, g_window.m_width / (FLOAT)g_window.m_height, 0.01f, 100.0f);

	//CBChangeOnResize cbChangesOnResize;
	cbChangesOnResize.mProjection = XMMatrixTranspose(g_Projection);
	// Set Vela Actor
	AVela = EngineUtilities::MakeShared<Actor>(g_device);

	if (!AVela.isNull()) {
		MESSAGE("Actor", "Actor", "Actor accessed successfully.")

			AVela->getComponent<Transform>()->setPosition(EngineUtilities::Vector3(-0.9f, -2.0f, 2.0f));
		AVela->getComponent<Transform>()->setRotation(EngineUtilities::Vector3(XM_PI / -2.0f, 0.0f, XM_PI / 2.0f));
		AVela->getComponent<Transform>()->setScale(EngineUtilities::Vector3(.03f, .03f, .03f));
		AVela->SetMesh(g_device, g_model.meshes);
		AVela->SetTextures(modelTextures);
	}
	else {
		MESSAGE("Actor", "Actor", "Actor resource not found.")
	}

	/* grid = EngineUtilities::MakeShared<Actor>(g_device);
	 if (!grid.isNull()) {
		 MESSAGE("Actor", "Actor", "Actor accessed successfully.")
			 std::vector<MeshComponent> gridMesh;
		 gridMesh.push_back(MC);
		 grid->setMesh(g_device, gridMesh);
		 gridTexs.push_back(g_default);
		 grid->setTextures(gridTexs);
		 grid->getComponent<Transform>()->setPosition(EngineUtilities::Vector3(0.0f, -2.0f, 0.0f));
		 grid->getComponent<Transform>()->setScale(EngineUtilities::Vector3(.03f, .03f, .03f));
	 }
	 else {
		 MESSAGE("Actor", "Actor", "Actor resource not found.")
	 }*/
	/*g_CBBufferChangeOnResize.update(g_deviceContext, 0, nullptr, &cbChangesOnResize, 0, 0);*/
	g_UserInterface.init(g_window.m_hWnd, g_device.m_device, g_deviceContext.m_deviceContext);
	return S_OK;
}


//--------------------------------------------------------------------------------------
// Clean up the objects we've created
//--------------------------------------------------------------------------------------
void CleanupDevice()
{
	if (g_deviceContext.m_deviceContext) g_deviceContext.m_deviceContext->ClearState();

	AVela->destroy();
	//grid->destroy();

	//g_default.destroy();
	g_CBBufferNeverChanges.destroy();
	g_CBBufferChangeOnResize.destroy();
	

	g_shaderProgram.destroy();
	g_DepthStencil.destroy();
	g_depthStencilView.destroy();
	g_RenderTargetView.destroy();
	g_swapchain.destroy();
	g_deviceContext.destroy();
	// Release UI
	g_UserInterface.destroy();

	g_device.destroy();
}
//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
		return true;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

//Update everyframe
void Update(double DeltaTime)
{

	g_UserInterface.update();
	bool show_demo_window = true;
	
	ImGui::ShowDemoWindow(&show_demo_window);
	///*ImGui::Begin("Test");

	 /*ImGui::End();*/
   // Update constant Buffers
	g_CBBufferNeverChanges.update(g_deviceContext, 0, nullptr, &cbNeverChanges, 0, 0);
	g_CBBufferChangeOnResize.update(g_deviceContext, 0, nullptr, &cbChangesOnResize, 0, 0);

	// Actualizar info logica del mesh
	AVela->getComponent<Transform>()->ui_noWindow("Transform");
	AVela->update(0, g_deviceContext);
	//grid->update(0, g_deviceContext);
	//EngineUtilities::Vector3 translation(0.0f, 0.0f, DeltaTime);
	//AVela->getComponent<Transform>()->translate(translation);
	//AVela->getComponent<Transform>()->setRotation(Vector3f(XM_PI / -2.0f, DeltaTime, XM_PI / 2.0f));
}

//--------------------------------------------------------------------------------------
// Render a frame
//--------------------------------------------------------------------------------------
void Render()
{
	// Clear the back buffer
	
	float ClearColor[4] = { 0.85f, 0.85f, 0.85f, 1.0f }; // red, green, blue, alpha
	g_RenderTargetView.render(g_deviceContext,g_depthStencilView,1,ClearColor);
	// Set Viewport
	g_viewport.render(g_deviceContext);
	//
	// Clear the depth buffer to 1.0 (max depth)
	//
	//g_deviceContext.m_deviceContext->ClearDepthStencilView(g_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	//render cube
	g_depthStencilView.render(g_deviceContext);

	//render cube
	g_shaderProgram.render(g_deviceContext);

	// Render the models
	AVela->render(g_deviceContext);
	//grid->render(g_deviceContext);

	//for (size_t i = 0; i < 7; i++) {
	//	//g_vertexBuffers[i].render(g_deviceContext, 0, 1);
		//g_indexBuffers[i].render(g_deviceContext, DXGI_FORMAT_R32_UINT);
		//if (i <= modelTextures.size() - 1)
		//{
		//	modelTextures[i].render(g_deviceContext, 0, 1);
		//}
		//else {
		//	g_default.render(g_deviceContext, 0, 1);
		//}
		//g_default.render(g_deviceContext, 0, 1);
		//g_sampler.render(g_deviceContext, 0, 1);
	//
	//
	//	//g_deviceContext.m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//	//g_deviceContext.m_deviceContext->DrawIndexed(g_model.meshes[i].m_numIndex, 0, 0);
	//}
		// Actualizar constant buffers
	g_CBBufferNeverChanges.render(g_deviceContext, 0, 1);
	g_CBBufferChangeOnResize.render(g_deviceContext, 1, 1);

	g_UserInterface.render();
	// Present our back buffer to our front buffer
	//
	//g_pSwapChain->Present(0, 0);
	g_swapchain.present();
}
