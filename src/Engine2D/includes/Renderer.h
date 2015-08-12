#ifndef RENDERER_H
#define RENDERER_H

#include "Defines.h"
#include <string>
#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")


namespace Engine{
template <class PixelFormatClass, unsigned int FVF>
class VertexBuffer;
class Texture;
class Importer;

class ENGINE_API Renderer{
private:
	IDirect3D9 *p_D3D;
	IDirect3DDevice9* m_pkDevice;
	HWND m_hWnd;
	D3DXMATRIX m_mProjectionMatrix;
	VertexBuffer<D3DVERTEX, COLOR_VERTEX>* m_pkVertexBuffer;
	VertexBuffer<D3DTVERTEX, TEXTURE_VERTEX>* m_pkVertexBufferS;
	
	Importer* m_sImporter;

	// Matrices
	MATRIX_MODE m_eCurrentMatMode;
	D3DXMATRIX kProjectionMatrix;
	D3DXMATRIX kViewMatrix;
	D3DXVECTOR3 kViewPos;
	D3DXVECTOR3 kLookPos;
	D3DXVECTOR3 kViewUp;
public:
	Renderer(HWND hWnd);
	~Renderer(void);
	bool InitDX(HWND hWnd);
	void StartFrame();
	void EndFrame();

	// Shapes
	void Draw(D3DVERTEX* vertexCollection, D3DPRIMITIVETYPE ePrim, unsigned int uiVertexCount);
	
	// Sprites
	void DrawSP(D3DTVERTEX* vertexCollection, unsigned int uiVertexCount);
	Texture* LoadTexture(std::string fileName, int keycode);
	void SetTexture(Texture* texture);

	void SetMatrixMode(MATRIX_MODE mode);
	void SetViewPosition(float posX, float posY, float posZ);
	void UpdateView(D3DXVECTOR3* viewPos, D3DXVECTOR3* lookPos);
	void LoadIdentity();

	void CreateImporter();

	void CameraControl(D3DXVECTOR3* viewPos, D3DXVECTOR3* lookPos);
	void Translate(float fx, float fy);
	void Scale(float h, float w);

};
}

#endif