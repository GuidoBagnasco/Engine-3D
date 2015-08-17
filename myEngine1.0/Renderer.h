#pragma once
#include <Windows.h>
#include "myEngine_API.h"
#include "RenderTypes.h"
#include "EMath.h"
#include <d3d9.h>
#include <vector>

namespace engine{

class VertexBuffer;
	
class MYENGINE_API Renderer{
	public:
		Renderer();
		~Renderer();
		bool Init(HWND _HwnD);
		void BeginFrame();
		void EndFrame();
		void setMatrix(MatrixType, const Matrix&);

		void Draw(ColorVertex*, engine::Primitive, size_t);
		void Draw(TextureVertex*, engine::Primitive, size_t);

		void SetBackgroundColor(short, short, short);
		void SwitchLightning();

		const Texture loadTexture(const std::string& name, int KeyCode = 0);
		void setCurrentTexture(const Texture&);
		void loadIdentity();
		void setTransformMatrix(D3DXMATRIX*);


	//	void SetCurrentTexture(const &texture t);
	//	IDirect3DTexture9 * LoadTexture(std::string& s);
	private:
		short r, g, b;
		IDirect3D9  * d3d;
		IDirect3DDevice9  * d3d_dev; 

		VertexBuffer * p_vb;
		VertexBuffer * p_vTexture;

		std::vector<Texture> m_vTexture;
		
};
}