#pragma once
#include <Windows.h>
#include "myEngine_API.h"
#include "RenderTypes.h"
#include "EMath.h"
#include <d3d9.h>
#include <vector>

namespace engine{

class VertexBuffer;
class IndexBuffer;
class Camera;


class MYENGINE_API Renderer{
	public:
		Camera * c;
		IDirect3D9* d3d;
		IDirect3DDevice9* d3d_dev;

		Renderer();
		~Renderer();
		bool Init(HWND _HwnD);
		void BeginFrame();
		void EndFrame();
		void SetMatrix(MatrixType, const Matrix&);

		void Draw(ColorVertex*, Primitive, size_t);
		void Draw(TextureVertex*, Primitive, size_t);
		void Draw(Primitive prim);

		void SetBackgroundColor(short, short, short);
		void SwitchLightning();

		const Texture LoadTexture(const std::string& name, int KeyCode = 0);
		void SetCurrentTexture(const Texture&);
		void LoadIdentity();
		void SetTransformMatrix(D3DXMATRIX*);

		VertexBuffer* CreateVertexBuffer(size_t vSize, unsigned int FVF);
		void SetCurrentVertexBuffer(VertexBuffer* c_vb3D);
		IndexBuffer* CreateIndexBuffer();
		void SetCurrentIndexBuffer(IndexBuffer* c_ib);


	//	void SetCurrentTexture(const &texture t);
	//	IDirect3DTexture9 * LoadTexture(std::string& s);
	private:
		
		short r, g, b;
		VertexBuffer* p_vb;
		IndexBuffer* p_ib;
		//VertexBuffer * p_vTexture;

		std::vector<Texture> m_vTexture;
		
};
}