#include "Triangle.h"
#include "Renderer.h"
using namespace Engine;

Triangle::Triangle() : Shape(){
	uiVertexCount = 3;

	vertices[0].x = -0.5;
	vertices[0].y = -0.5;
	vertices[0].z = 1;
	vertices[0].color = D3DCOLOR_XRGB(0, 200, 10);
	
	vertices[1].x = 0.5;
	vertices[1].y = -0.5;
	vertices[1].z = 1;
	vertices[1].color = D3DCOLOR_XRGB(0, 200, 10);

	vertices[2].x = 0.5;
	vertices[2].y = 0.5;
	vertices[2].z = 1;
	vertices[2].color = D3DCOLOR_XRGB(0, 200, 10);

	SetScale(1, 1);
}


Triangle::Triangle(D3DVERTEX v1, D3DVERTEX v2, D3DVERTEX v3, float w, float h) : Shape(){
	uiVertexCount = 3;

	vertices[0] = v1;
	
	vertices[1] = v2;

	vertices[2] = v3;

	SetScale(w, h);
}


void Triangle::Draw(Renderer* renderer){
	Entity2D::Draw(renderer);
	renderer->Draw(vertices, D3DPRIMITIVETYPE::D3DPT_TRIANGLESTRIP, uiVertexCount);
}


void Triangle::SetColor(DWORD color){
	Shape::SetColor(color);

	for(int i = 0; i < 3; i++)
		vertices[i].color = color;
}


Triangle::~Triangle(){
	delete[] &vertices;
}