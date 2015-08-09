#ifndef VERTEX_H
#define VERTEX_H
#include "Defines.h"


namespace Engine{
	static D3DVERTEX SetVertex(float _x, float _y, float _z, int _r, int _g, int _b){
		D3DVERTEX vertex;
		vertex.x = _x;
		vertex.y = _y;
		vertex.z = _z;
		vertex.color = D3DCOLOR_XRGB(_r, _g, _b);

		return vertex;
	}
}

#endif