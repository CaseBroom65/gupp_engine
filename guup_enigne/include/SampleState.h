#pragma once
#include "PreRequisitos.h"

class Device;
class DeviceContext;

class SamplerState
{
public:
    // Constructor por defecto
    SamplerState() = default;
    // Destructor por defecto
    ~SamplerState() = default;

    // Método para inicializar el estado del sampler
    void init(Device device);

    // Método para actualizar el estado del sampler
    void update();

    // Método para renderizar usando el contexto del dispositivo
    // Recibe un contexto de dispositivo, la ranura de inicio y el número de samplers
    void render(DeviceContext& deviceContext, unsigned int StartSlot, unsigned int NumSamplers);

    // Método para destruir o liberar recursos del estado del sampler
    void destroy();

private:
    // Puntero al estado del sampler de Direct3D 11
    ID3D11SamplerState* m_sampler = nullptr;
};
