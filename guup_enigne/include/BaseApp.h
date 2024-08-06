#pragma once
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

#include "UserInterface.h"
#include "Actor.h"



// Define una clase llamada BaseApp.
class BaseApp
{
public:
    // Constructor predeterminado para BaseApp.
    BaseApp() = default;
    // Destructor predeterminado para BaseApp.
    ~BaseApp() = default;

    // Declaración del método init que probablemente inicializa la aplicación y retorna un resultado de tipo HRESULT (común en API de Windows para indicar éxito o error).
    HRESULT init();

    // Declaración del método update que probablemente se usa para actualizar el estado de la aplicación.
    void update();

    // Declaración del método render que probablemente se usa para renderizar o dibujar en la ventana.
    void render();

    // Declaración del método destroy que probablemente se usa para limpiar y liberar recursos.
    void destroy();

    // Declaración del método run que recibe los parámetros de la función WinMain y probablemente contiene el bucle principal de la aplicación.
    // Los parámetros son:
    // - HINSTANCE hInstance: Manejador de instancia de la aplicación.
    // - HINSTANCE hPrevInstance: Manejador de instancia previa (obsoleto y siempre NULL en aplicaciones modernas).
    // - LPWSTR lpCmdLine: Línea de comandos.
    // - int nCmdShow: Parámetro que especifica cómo debe mostrarse la ventana.
    int run(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, WNDPROC wndproc);

    void CreateGrid(int width, int depth, float spacing);

private:
    // Instancia de la clase Window.
    window                                  m_window;
    Device									m_device;
    DeviceContext							m_deviceContext;
    SwapChain								m_swapchain;
    Texture									m_BackBuffer;
    Texture									m_DepthStencil;
    DepthStencilView						m_depthStencilView;
    RenderTargetView						m_RenderTargetView;
    Viewport								m_viewport;
    ShaderProgram							m_shaderProgram;
    std::vector<Buffer>						m_vertexBuffers;
    std::vector<Buffer>						m_indexBuffers;
    Buffer									m_CBBufferNeverChanges;
    Buffer									m_CBBufferChangeOnResize;
    Buffer									m_CBBufferChangesEveryFrame;

    //Mesh									m_mesh;
    std::vector<Texture>					modelTextures;
    SamplerState							m_sampler;
    ModelLoader								m_model;
    Texture									m_default;
    std::vector<Texture>					gridTexs;
    UserInterface                            m_UserInterface;

    //XMMATRIX                            m_World;
    XMMATRIX                            m_View;
    XMMATRIX                            m_Projection;
    XMFLOAT4                            m_vMeshColor;
    CBNeverChanges                      cbNeverChanges;
    CBChangeOnResize                    cbChangesOnResize;
    CBChangesEveryFrame                 cb;
    //Grid Data
    MeshComponent                       MC;
    EngineUtilities::TSharedPointer<Actor> AGrid;

    //Vela Actor
    EngineUtilities::TSharedPointer<Actor> AVela;
    //std::vector<Texture> gridTexs;

};
