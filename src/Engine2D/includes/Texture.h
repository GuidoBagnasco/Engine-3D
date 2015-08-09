#ifndef TEXTURE_H
#define TEXTURE_H
#include <iostream>
#include <string>
#include "Defines.h"

namespace Engine{

class ENGINE_API Texture{
private:
	std::string m_name;
	int m_width;
	int m_height;
	int m_keycode;
	IDirect3DTexture9* m_texture;
	std::string m_fileName;

public:
	Texture();
	void SetName(std::string name);
	std::string GetName();

	void SetDimension(int width, int height);
	int GetWidth();
	int GetHeight();
	void GetDimension(int &width, int& height);

	void SetKeycode(int keycode);
	int GetKeycode();

	void SetFileName(std::string fileName);
	std::string GetFileName();

	bool SetTexture(IDirect3DTexture9* pk_Texture);
	IDirect3DTexture9* GetTexture();
};
}


#endif