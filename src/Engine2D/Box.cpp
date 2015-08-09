#include "Box.h"
#include "Renderer.h"
using namespace Engine;

Box::Box() : Shape(){
	uiVertexCount = 4;

	vertices[0].x = -0.5;
	vertices[0].y =  0.5;
	vertices[0].z =  1.0f;
	vertices[0].color = D3DCOLOR_XRGB(70, 120, 90);
	
	vertices[1].x =  0.5;
	vertices[1].y =  0.5;
	vertices[1].z =  1.0f;
	vertices[1].color = D3DCOLOR_XRGB(70, 120, 90);

	vertices[2].x = -0.5;
	vertices[2].y = -0.5;
	vertices[2].z =  1.0f;
	vertices[2].color = D3DCOLOR_XRGB(70, 120, 90);

	vertices[3].x =  0.5;
	vertices[3].y = -0.5;
	vertices[3].z =  1.0f;
	vertices[3].color = D3DCOLOR_XRGB(70, 120, 90);

	SetScale(1, 1);
}


Box::Box(D3DVERTEX v1, D3DVERTEX v2, D3DVERTEX v3, D3DVERTEX v4, float w, float h) : Shape(){
	uiVertexCount = 4;

	vertices[0] = v1;
	
	vertices[1] = v2;

	vertices[2] = v3;

	vertices[3] = v4;

	SetScale(w, h);
}


void Box::Draw(Renderer* renderer){
	Entity2D::Draw(renderer);
	renderer->Draw(vertices, D3DPRIMITIVETYPE::D3DPT_TRIANGLESTRIP, uiVertexCount);
}



void Box::SetColor(DWORD color){
	Shape::SetColor(color);

	for(int i = 0; i < 4; i++)
		vertices[i].color = color;
}



Box::~Box(){
	delete[] &vertices;
}