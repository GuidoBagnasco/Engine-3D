
//---------------------------------------------------------------------------
#include "VertexBuffer.h"
//---------------------------------------------------------------------------
#include "Renderer.h"
//---------------------------------------------------------------------------
#include <cassert>
//---------------------------------------------------------------------------
using namespace engine;
//---------------------------------------------------------------------------
// Engine to DirectX primitives enum mapping
D3DPRIMITIVETYPE g_ePrimitivesMapping[PrimitiveCount] = 
{
	D3DPT_TRIANGLELIST,		// TriangleList
	D3DPT_TRIANGLESTRIP,	// TriangleStrip
	D3DPT_POINTLIST,		// PointList
    D3DPT_LINELIST,			// LineList
    D3DPT_LINESTRIP,		// LineStrip
	D3DPT_TRIANGLEFAN		// TriangleFan
};
//---------------------------------------------------------------------------
VertexBuffer::VertexBuffer(IDirect3DDevice9* pkDevice, size_t uiVertexSize, unsigned int uiFVF):
m_uiFVF(uiFVF),
m_uiVertexSize(uiVertexSize),
m_uiVertexCount(0),
m_pkVertexBuffer(NULL),
m_pkDevice(pkDevice)
{
	// nothing to do
}

//---------------------------------------------------------------------------

VertexBuffer::~VertexBuffer(){
	if (m_pkVertexBuffer){
		m_pkVertexBuffer->Release();
		m_pkVertexBuffer = NULL;
	}
}

//---------------------------------------------------------------------------

void VertexBuffer::SetVertexData(const void* pakVertices, D3DPRIMITIVETYPE ePrimitive, size_t uiVertexCount){
	// release if previously created
	if(m_pkVertexBuffer){
		m_pkVertexBuffer->Release();
		m_pkVertexBuffer = NULL;
	}

	// create vertex buffer
	HRESULT hr = m_pkDevice->CreateVertexBuffer(
												uiVertexCount * m_uiVertexSize,
												D3DUSAGE_WRITEONLY,
												m_uiFVF,
												D3DPOOL_DEFAULT,
												&m_pkVertexBuffer,
												NULL
	);

	assert(hr == D3D_OK);

	// copy vertex data
	m_ePrimitiveType = g_ePrimitivesMapping[ePrimitive];

	void* pVertices = NULL;

	hr = m_pkVertexBuffer->Lock(0, 0, (void**)(&pVertices), 0);

	memcpy(pVertices, pakVertices, uiVertexCount * m_uiVertexSize);

	hr = m_pkVertexBuffer->Unlock();

	// update internal state
	m_uiVertexCount = uiVertexCount;
}

//---------------------------------------------------------------------------

void VertexBuffer::Bind(){
	HRESULT hr;

	hr = m_pkDevice->SetVertexShader(NULL);
	assert(hr == D3D_OK);

	hr = m_pkDevice->SetFVF(m_uiFVF);
	assert(hr == D3D_OK);

	hr = m_pkDevice->SetStreamSource(0, m_pkVertexBuffer, 0, m_uiVertexSize);
	assert(hr == D3D_OK);
}

//---------------------------------------------------------------------------

void VertexBuffer::Draw(){
	// bind the buffer
	Bind();

	// render
	//hr = m_pkDevice->DrawPrimitive(m_ePrimitiveType, 0, iPrimitiveCount);
	HRESULT hr = m_pkDevice->DrawIndexedPrimitive(m_ePrimitiveType, 0, 0, m_uiVertexCount, 0, Flush());
	//assert(hr == D3D_OK);
}

//---------------------------------------------------------------------------

int VertexBuffer::Flush(){
	// calculate primitive count
	int iPrimitiveCount = 0;

	if (m_ePrimitiveType == D3DPT_POINTLIST){
		iPrimitiveCount = m_uiVertexCount;
	}
	else if (m_ePrimitiveType == D3DPT_LINELIST){
		iPrimitiveCount = m_uiVertexCount / 2;
	}
	else if (m_ePrimitiveType == D3DPT_LINESTRIP){
		iPrimitiveCount = m_uiVertexCount - 1;
	}
	else if (m_ePrimitiveType == D3DPT_TRIANGLELIST){
		iPrimitiveCount = m_uiVertexCount / 3;
	}
	else if (m_ePrimitiveType == D3DPT_TRIANGLESTRIP){
		iPrimitiveCount = m_uiVertexCount - 2;
	}
	else if (m_ePrimitiveType == D3DPT_TRIANGLEFAN){
		iPrimitiveCount = m_uiVertexCount - 2;
	}

	return iPrimitiveCount;
}