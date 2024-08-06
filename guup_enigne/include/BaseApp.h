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

    // Declaraci�n del m�todo init que probablemente inicializa la aplicaci�n y retorna un resultado de tipo HRESULT (com�n en API de Windows para indicar �xito o error).
    HRESULT init();

    // Declaraci�n del m�todo update que probablemente se usa para actualizar el estado de la aplicaci�n.
    void update();

    // Declaraci�n del m�todo render que probablemente se usa para renderizar o dibujar en la ventana.
    void render();

    // Declaraci�n del m�todo destroy que probablemente se usa para limpiar y liberar recursos.
    void destroy();

    // Declaraci�n del m�todo run que recibe los par�metros de la funci�n WinMain y probablemente contiene el bucle principal de la aplicaci�n.
    // Los par�metros son:
    // - HINSTANCE hInstance: Manejador de instancia de la aplicaci�n.
    // - HINSTANCE hPrevInstance: Manejador de instancia previa (obsoleto y siempre NULL en aplicaciones modernas).
    // - LPWSTR lpCmdLine: L�nea de comandos.
    // - int nCmdShow: Par�metro que especifica c�mo debe mostrarse la ventana.
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
