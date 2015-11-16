#pragma once
#include "myEngine_API.h"
#include "RenderTypes.h"
#include "Entity.h"
#include <string>
#include <vector>


namespace engine{
	enum CollisionResult{
		CollisionVertical,
		CollisionHorizontal,
		NoCollision,
		CollisionZ
	};

	class Renderer;
	class IndexBuffer;
	class VertexBuffer;
	class Node;

	class MYENGINE_API Mesh : public Entity{

	public:
		Mesh(Renderer& r, bool isTextured = false);
		~Mesh();

		void SetData(ColorVertex* , size_t vertexCount, engine::Primitive, unsigned short*, size_t indexCount);
		void SetData(MeshVertex*  , size_t vertexCount, engine::Primitive, unsigned short*, size_t indexCount);
		void SetTexture(Texture);
		
		void Draw();
		void DrawBB() const;

		D3DXVECTOR3* m_pBB;

	private:
		IndexBuffer* m_pIndexBuffer;
		VertexBuffer* m_pVertexBuffer;
		Primitive m_Primitive;
		Renderer& m_rRenderer;
		Texture m_pTexture;

		MeshVertex* m_TextureVertex;
		unsigned int m_VertexCount = 0;

	};
}