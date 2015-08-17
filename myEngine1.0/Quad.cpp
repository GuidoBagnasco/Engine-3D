#include "Quad.h"
#include "Renderer.h"
#include <d3dx9.h>
using namespace engine;

Quad::Quad() :
Entity(),
_Vertex(new ColorVertex[4]){

	_Vertex[0].x = -0.5f; _Vertex[0].y = 0.5f; _Vertex[0].z = 0.0f;
	_Vertex[1].x = 0.5f; _Vertex[1].y = 0.5f; _Vertex[1].z = 0.0f;
	_Vertex[2].x = -0.5f; _Vertex[2].y = -0.5f; _Vertex[2].z = 0.0f;
	_Vertex[3].x = 0.5f; _Vertex[3].y = -0.5f; _Vertex[3].z = 0.0f;


	// Setting the default Color (255,0,0)
	_Vertex[0].color = engine_COLOR_ARGB(128,255, 0, 0);
	_Vertex[1].color = engine_COLOR_ARGB(128,255, 0, 0);
	_Vertex[2].color = engine_COLOR_ARGB(128,255, 0, 0);
	_Vertex[3].color = engine_COLOR_ARGB(128,255, 0, 0);
}

Quad::~Quad()
{
	delete[] _Vertex;
	_Vertex = NULL;
}

void Quad::draw(Renderer& r) const{
	r.setCurrentTexture(NoTexture);
	r.setMatrix(World, _TrMatrix);
	r.Draw(_Vertex, engine::TriangleStrip, 4);
}

void Quad::setColor(DWORD c){
	for(int i = 0; i < 4; i++)
		_Vertex[i].color = c;
}

void Quad::setColor(DWORD c, int v){
	if(v >= 0 && v < 4)
		_Vertex[v].color = c;
}