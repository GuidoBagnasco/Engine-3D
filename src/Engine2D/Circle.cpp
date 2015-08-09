#include "Circle.h"
#include "Renderer.h"
using namespace Engine;

Circle::Circle() : Shape(){
	cx = 0;
	cy = 0;
	iR = 255;
	iG = 0;
	iB = 0;
	SetNumberFaces(24);
	SetScale(1, 1);
}


Circle::Circle(int iFaces, float x, float y, int r, int g, int b, float w, float h) : Shape(){
	cx = x;
	cy = y;
	iR = r;
	iG = g;
	iB = b;
	SetNumberFaces(iFaces);
	SetScale(w, h);
}


void Circle::SetNumberFaces(int iFaces){

	if(iFaces > 145)
		m_iFaces = 145;
	else if(m_iFaces > 60 && m_iFaces > 75)
		m_iFaces = 60;
	else if(m_iFaces > 60 && m_iFaces > 90)
		m_iFaces = 90;
	else
		m_iFaces = iFaces;

	D3DVERTEX* pkV; 
	vertices = new D3DVERTEX[m_iFaces + 2];
	uiVertexCount = m_iFaces + 2;

	//---------------Center---------------//
	pkV = &(vertices[0]);
	pkV->x = cx;
	pkV->y = cy;
	pkV->z = 1.0f;
	pkV->color = D3DCOLOR_XRGB(iR, iG, iB);
	//-----------------------------------//
	
	for(int i = 1; i <= m_iFaces + 1; i++){
		double dAngle = (360/m_iFaces) * i;
		double radian = M_PI / 180.0;
		double dAngleSin = sin(dAngle * radian);
		double dAngleCos = cos(dAngle * radian);

		pkV = &(vertices[i]);
		pkV->x = (float)dAngleSin * 0.5f;
		pkV->y = (float)dAngleCos * 0.5f;
		pkV->z = 1.0f;
		pkV->color = D3DCOLOR_XRGB(iR, iG, iB);
	}
}


void Circle::Draw(Renderer* renderer){
	Entity2D::Draw(renderer);
	renderer->Draw(vertices, D3DPRIMITIVETYPE::D3DPT_TRIANGLEFAN, uiVertexCount);
}


void Circle::SetColor(DWORD color){
	Shape::SetColor(color);

	for(int i = 0; i < m_iFaces; i++)
		vertices[i].color = color;
}


Circle::~Circle(){
	delete[] vertices;
}