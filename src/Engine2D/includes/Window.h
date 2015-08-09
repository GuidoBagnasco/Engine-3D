#ifndef WINDOW_H
#define WINDOW_H

#include "Defines.h"

namespace Engine{
	class ENGINE_API Window{
	public:
		Window(HINSTANCE hInstance);

		bool CreateWindowE(unsigned int ui_Height, unsigned int ui_Width, HWND & hWnd);
		void SetWindowTitle(LPCSTR lpString);

	private:
		HWND m_hWnd;
		HINSTANCE m_Instance;
	};	
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

#endif