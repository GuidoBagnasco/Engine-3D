
//---------------------------------------------------------------------------
#ifndef PG2_INDEXBUFFER_H
#define PG2_INDEXBUFFER_H
//---------------------------------------------------------------------------
#include "myEngine_API.h"
//---------------------------------------------------------------------------
#include <d3d9.h>
#include <d3dx9.h>
#include <cassert>
//---------------------------------------------------------------------------
namespace engine{
//---------------------------------------------------------------------------
class MYENGINE_API IndexBuffer{
public:
	IndexBuffer(IDirect3DDevice9* pkDevice);
	~IndexBuffer();

	void Bind();
	void SetIndexData(const unsigned short* pausIndices, size_t uiIndexCount);
	
private:
	size_t m_uiIndexCount;

	D3DPRIMITIVETYPE m_ePrimitiveType;
	LPDIRECT3DINDEXBUFFER9 m_IndexBuffer;
	IDirect3DDevice9* m_pkDevice;
};
//---------------------------------------------------------------------------
} // end namespace
//---------------------------------------------------------------------------
#endif  // PG2_INDEXBUFFER_H
//---------------------------------------------------------------------------
