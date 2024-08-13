# gupp_engine
es para la clase de arquitectura de motores graficos.

# Descripción total
Guup_engine es un motor gráfico en desarrollo que utiliza Direct3D 11, una API de gráficos 3D de alto rendimiento proporcionada por Microsoft. Está diseñado para ofrecer una base sólida para la creación de aplicaciones gráficas y videojuegos, facilitando la gestión y manipulación de recursos gráficos como texturas, shaders y buffers.

# Características
Gestión de Dispositivos y Contextos:

- **Device**: Responsable de la creación y gestión de recursos en la GPU.

- **DeviceContext**: Maneja el estado del pipeline y ejecuta las operaciones de renderizado.

- **SwapChain**: Administra la cadena de intercambio necesaria para la presentación de imágenes en pantalla, facilitando la creación de la vista de renderizado.

- **Texture**: Gestor de texturas en 2D, incluyendo la carga de imágenes desde archivos y la creación de recursos de textura en la memoria de la GPU.

- **DepthStencilView**: Gestión de vistas de profundidad y stencil, esenciales para el renderizado correcto de escenas 3D.

- **Viewport**: Define la región rectangular de la ventana de renderizado donde se dibuja la escena.

- **SimpleVertex**: Define los datos básicos de los vértices, incluyendo posición y coordenadas de textura.

- **CBNeverChanges, CBChangeOnResize, CBChangesEveryFrame**: Buffers constantes utilizados para pasar datos a los shaders, optimizados para diferentes frecuencias de cambio (nunca, en redimensionado, cada frame).

# Requisitos
- Sistema Operativo: Windows 7 o superior.
- SDK: DirectX SDK (Direct3D 11).
- Compilador: Visual Studio 2019 o superior.