#include "Window.h"
using namespace Engine;

Window::Window(HINSTANCE hInstance):
	m_hWnd(NULL),
	m_Instance(hInstance)
{

}



bool Window::CreateWindowE(unsigned int ui_Height, unsigned int ui_Width, HWND & hWnd){
	WNDCLASS kWC;

	memset(static_cast<void *> (&kWC), 0, sizeof(WNDCLASS));
	kWC.style = CS_HREDRAW | CS_VREDRAW;
	kWC.lpfnWndProc = (WNDPROC) WndProc;
	kWC.hInstance = m_Instance;
	kWC.hbrBackground = (HBRUSH) COLOR_BACKGROUND;
	kWC.lpszClassName = "Engine";

	if(!RegisterClass(&kWC))
		return false;

		// Creates the window
	m_hWnd = CreateWindow("Engine",
							"Engine",
							//WS_EX_TOPMOST | WS_POPUP,
							WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							ui_Width + 8,
							ui_Height + 30,
							NULL,
							NULL,
							m_Instance,
							NULL
	);

	if(!m_hWnd)
		return false;

	hWnd = m_hWnd;

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return true;
}



void Window::SetWindowTitle(LPCSTR lpString){
	SetWindowText(m_hWnd, lpString);
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	switch (message) {

		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_PAINT: // <— ADD THIS BLOCK
			ValidateRect(hWnd, NULL);
			break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}