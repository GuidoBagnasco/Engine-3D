#ifndef CIRCLE_H
#define CIRCLE_H
#include "Shape.h"
#define _USE_MATH_DEFINES
#include <math.h>


namespace Engine{
class ENGINE_API Circle : public Shape{
private:
	int uiVertexCount;
	int m_iFaces;
	D3DVERTEX* vertices;
	float cx;
	float cy;
	int iR, iG, iB;
public:
	Circle();
	Circle(int iFaces, float x, float y, int r, int g, int b, float w = 100, float h = 100);
	~Circle();
	void SetNumberFaces(int iFaces);
	int GetNumberFaces(){return m_iFaces;}
	void Draw(Renderer* renderer);
	void SetColor(DWORD color);
};
}

#endif