#pragma once
#include "PreRequisitos.h"
class window;
class DeviceContext;

class Viewport
{
public:
    Viewport() = default;
    ~Viewport() = default;

    void init(window window);
    void update();
    void render(DeviceContext& deviceContext);
    void destroy();


public:
    D3D11_VIEWPORT m_viewport;

};