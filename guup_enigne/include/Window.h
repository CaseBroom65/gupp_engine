#pragma once
#include "PreRequisitos.h"


class window
{
public:
	window() = default;
	~window()= default;

	HRESULT init(HINSTANCE hInstance, int nCmdShow, WNDPROC wndproc);

	void update();

	void render();

	void destroy();

public:
	HWND m_hWnd = nullptr;
	unsigned int m_width;
	unsigned int m_height;
private:
	HINSTANCE m_hInst = nullptr;
	RECT m_rect;
	std::string m_windowname = "guup Engine";
};
