#pragma once
#include "PreRequisitos.h"
#include "Window.h"
class BaseApp
{
public:
	BaseApp() = default;
	~BaseApp() = default;

	HRESULT init();

	void update();

	void render();

	void destroy();

	int run(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow);

	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
	window m_window;
};