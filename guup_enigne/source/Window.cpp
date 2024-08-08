#include "Window.h" // Incluye el encabezado de la clase Window

HRESULT window::init(HINSTANCE hInstance, int nCmdShow, WNDPROC wndproc){ // M�todo para inicializar la ventana
    m_hInst = hInstance; // Almacena el manejador de la instancia

    // Register class
    WNDCLASSEX wcex; // Estructura para la clase de ventana
    wcex.cbSize = sizeof(WNDCLASSEX); // Establece el tama�o de la estructura
    wcex.style = CS_HREDRAW | CS_VREDRAW; // Establece los estilos de la ventana
    wcex.lpfnWndProc = wndproc; // Establece el procedimiento de la ventana
    wcex.cbClsExtra = 0; // No se utiliza memoria adicional para la clase
    wcex.cbWndExtra = 0; // No se utiliza memoria adicional para la ventana
    wcex.hInstance = m_hInst; // Almacena el manejador de la instancia
    wcex.hIcon = LoadIcon(m_hInst, (LPCTSTR)IDI_TUTORIAL1); // Carga el icono de la ventana
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW); // Carga el cursor por defecto
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // Establece el color de fondo
    wcex.lpszMenuName = nullptr; // No se utiliza men�
    wcex.lpszClassName = "TutorialWindowClass"; // Nombre de la clase de la ventana
    wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_TUTORIAL1); // Carga un icono peque�o

    if (!RegisterClassEx(&wcex)) // Registra la clase de ventana
        return E_FAIL; // Retorna error si falla

    // Create window
    RECT rc = { 0, 0, 1500, 840 }; // Define el rect�ngulo de la ventana
    m_rect = rc; // Almacena el rect�ngulo
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE); // Ajusta el tama�o de la ventana
    m_hWnd = CreateWindow("TutorialWindowClass", m_windowname.c_str(), WS_OVERLAPPEDWINDOW, // Crea la ventana
        CW_USEDEFAULT, CW_USEDEFAULT, m_rect.right - m_rect.left, m_rect.bottom - m_rect.top, nullptr, nullptr, m_hInst,
        nullptr);

    if (!m_hWnd) // Verifica si la ventana se cre� correctamente
        return E_FAIL; // Retorna error si falla

    ShowWindow(m_hWnd, nCmdShow); // Muestra la ventana

    GetClientRect(m_hWnd, &m_rect); // Obtiene las dimensiones del cliente
    m_width = m_rect.right - m_rect.left; // Calcula el ancho
    m_height = m_rect.bottom - m_rect.top; // Calcula la altura
    return S_OK; // Retorna �xito
}

void window::update(){ // M�todo vac�o para futuras actualizaciones
}

void window::render(){ // M�todo vac�o para renderizar
}

void window::destroy(){ // M�todo vac�o para destruir la ventana y limpiar recursos
}
