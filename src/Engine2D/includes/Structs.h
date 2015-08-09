#ifndef STRUCTS_H
#define STRUCTS_H

namespace Engine{
	#define COLOR_VERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE)
	#define TEXTURE_VERTEX (D3DFVF_XYZ|D3DFVF_TEX1|D3DFVF_TEXCOORDSIZE2(0))

	struct D3DVERTEX{
			float x, y, z;
			DWORD color;
	};


	struct D3DTVERTEX{
			float x, y, z;
			float u, v;
	};


	enum MATRIX_MODE{
		World = D3DTS_WORLDMATRIX(0),
		View = D3DTS_VIEW,
		Projection = D3DTS_PROJECTION,
	};


struct spriteUVInfo{
	float U1;
	float V1; 
	float U2; 
	float V2; 
	float U3; 
	float V3; 
	float U4; 
	float V4;
};

}

#endif