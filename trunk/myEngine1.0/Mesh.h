#pragma once
#include "myEngine_API.h"
#include "Entity.h"
#include "Renderer.h"
#include <d3d9.h>
#include <vector>

namespace engine{

	class Renderer;
	
	class MYENGINE_API Mesh : public Entity{
		public:
			Mesh(Renderer& rkRenderer);
			Mesh(Renderer& rkRenderer, std::vector<ColorVertex> vertices);
			~Mesh();
			void Draw() const;

			void SetData(ColorVertex* Tex_Vertex, size_t vertexCount, Primitive Prim, unsigned short* pInt, size_t indexCount);
			void SetData(MeshVertex* Tex_Vertex, size_t vertexCount, Primitive Prim, unsigned short* pInt, size_t indexCount);

		private:
			Renderer* m_pkRenderer;
			ColorVertex* _Vertex;
			Primitive m_primType;
		protected:
			virtual void Init(){	}

	};
}