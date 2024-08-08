#include "Viewport.h" // Incluye el encabezado de la clase Viewport
#include "Window.h" // Incluye el encabezado de la clase Window
#include "DeviceContext.h" // Incluye el encabezado para manejar el contexto del dispositivo

void Viewport::init(window window){ // Método para inicializar el viewport
    if (window.m_hWnd == nullptr){ // Verifica si el manejador de ventana es nulo
        ERROR("Viewport", "init", "CHECK FOR Window window") // Reporta error si la ventana es nula
            exit(1); // Sale del programa
    }
    m_viewport.Width = (float)window.m_width; // Establece el ancho del viewport
    m_viewport.Height = (float)window.m_height; // Establece la altura del viewport
    m_viewport.MinDepth = 0.0f; // Establece la profundidad mínima
    m_viewport.MaxDepth = 1.0f; // Establece la profundidad máxima
    m_viewport.TopLeftX = 0; // Establece la coordenada X de la esquina superior izquierda
    m_viewport.TopLeftY = 0; // Establece la coordenada Y de la esquina superior izquierda
}

void Viewport::update(){ // Método vacío para futuras actualizaciones
}

void Viewport::render(DeviceContext& deviceContext){ // Método para renderizar el viewport
    deviceContext.RSSetViewports(1, &m_viewport); // Establece el viewport en el contexto del dispositivo
}

void Viewport::destroy(){ // Método vacío para limpiar recursos si es necesario
}
