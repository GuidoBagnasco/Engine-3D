#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Shape.h"


namespace Engine{
class ENGINE_API Triangle : public Shape{
private:
	int uiVertexCount;
	D3DVERTEX vertices[3];
public:
	Triangle();
	Triangle(D3DVERTEX v1, D3DVERTEX v2, D3DVERTEX v3, float w = 1, float h = 1);
	~Triangle();
	void Draw(Renderer* renderer);
	void SetColor(DWORD color);
};
}

#endif