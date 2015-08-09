#include "Texture.h"
using namespace Engine;


Texture::Texture(){

}



void Texture::SetName(std::string name){
	m_name = name;
}



std::string Texture::GetName(){
	return m_name;
}



void Texture::SetDimension(int width, int height){
	m_width = width;
	m_height = height;
}



bool Texture::SetTexture(IDirect3DTexture9* pk_Texture){
	m_texture = pk_Texture;
	return m_texture != NULL;
}



IDirect3DTexture9* Texture::GetTexture(){
	return m_texture;
}



int Texture::GetWidth(){
	return m_width;
}



int Texture::GetHeight(){
	return m_height;
}



void Texture::GetDimension(int& width, int& height){
	width = m_width;
	height = m_height;
}


void Texture::SetKeycode(int keycode){
	m_keycode = keycode;
}


int Texture::GetKeycode(){
	return m_keycode;
}


void Texture::SetFileName(std::string fileName){
	m_fileName = fileName;
}


std::string Texture::GetFileName(){
	return m_fileName;
}