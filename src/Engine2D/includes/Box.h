#ifndef BOX_H
#define BOX_H
#include "Shape.h"

namespace Engine{
	class ENGINE_API Box : public Shape{
	private:
		int uiVertexCount;
		D3DVERTEX vertices[4];
	public:
		Box();
		Box(D3DVERTEX v1, D3DVERTEX v2, D3DVERTEX v3, D3DVERTEX v4, float w = 1, float h = 1);
		~Box();
		void Draw(Renderer* renderer);
		void SetColor(DWORD color);
	};
}

#endif