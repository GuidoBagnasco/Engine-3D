//---------------------------------------------------------------------------
#ifndef PG2_VERTEXBUFFER_H
#define PG2_VERTEXBUFFER_H
//---------------------------------------------------------------------------
#include "myEngine_API.h"
#include "RenderTypes.h"
//---------------------------------------------------------------------------
#include <d3d9.h> 
#include <d3dx9.h>
#include <cassert>
//---------------------------------------------------------------------------
namespace engine{
//---------------------------------------------------------------------------
class MYENGINE_API VertexBuffer{
public:
	VertexBuffer(IDirect3DDevice9* pkDevice, size_t uiVertexSize, unsigned int uiFVF);
	~VertexBuffer();

	void Bind();		// TODO: Is this missing??
	void Draw();
	int Flush();
	void SetVertexData(const void* pakVertices, D3DPRIMITIVETYPE ePrimitive, size_t uiVertexCount);
	
private:
	unsigned int m_uiFVF;
	size_t m_uiVertexSize;
	size_t m_uiVertexCount;

	D3DPRIMITIVETYPE m_ePrimitiveType;
	LPDIRECT3DVERTEXBUFFER9 m_pkVertexBuffer;
	IDirect3DDevice9* m_pkDevice;
};
//---------------------------------------------------------------------------
} // end namespace
//---------------------------------------------------------------------------
#endif  // PG2_VERTEXBUFFER_H
//---------------------------------------------------------------------------
