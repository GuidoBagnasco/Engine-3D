#ifndef DEFINE_H
#define DEFINE_H


#pragma warning(disable : 4251)
#pragma warning(disable : 4244)
#pragma warning(disable : 4018)


#ifndef ENGINE_EXPORTS
	#define ENGINE_API __declspec(dllexport)
#else
	#define ENGINE_API __declspec(dllimport)
#endif

#define NOMINMAX
#include <algorithm>

#include <Windows.h>
#include <d3dx9.h>
#include "Structs.h"
#include "Vertex.h"


//namespace Engine{
	#define WINDOW_HEIGHT 600
	#define WINDOW_WIDTH 800
	#define Engine_COLOR_ARGB(a,r,g,b)  ((DWORD)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))
	#define Engine_COLOR_RGB(r,g,b) Engine_COLOR_ARGB(0xff,r,g,b)
//}
#endif