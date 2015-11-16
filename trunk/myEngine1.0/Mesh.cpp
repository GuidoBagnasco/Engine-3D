#define NOMINMAX
#include "Mesh.h"
#include "Node.h"
#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include <algorithm>
using namespace engine;


Mesh::Mesh(Renderer& r, bool isTextured) :/* Entity(),*/ m_rRenderer(r), m_pVertexBuffer(NULL), m_pIndexBuffer(NULL), m_pTexture(NoTexture), m_pBB(new D3DXVECTOR3[8]){

	if(!isTextured){
		m_pVertexBuffer = r.CreateVertexBuffer(sizeof(engine::ColorVertex), engine::ColorVertexType);
		m_pIndexBuffer = r.CreateIndexBuffer();
	}else{
		m_pVertexBuffer = r.CreateVertexBuffer(sizeof(engine::MeshVertex), engine::MeshVertexType);
		m_pIndexBuffer = r.CreateIndexBuffer();
	}
}


Mesh::~Mesh(){
	if(m_pVertexBuffer){
		delete m_pVertexBuffer;
		m_pVertexBuffer = NULL;
	}

	if(m_pIndexBuffer){
		delete m_pIndexBuffer;
		m_pIndexBuffer = NULL;
	}
}



void Mesh::SetData(ColorVertex* Tex_Vertex, size_t vertexCount, Primitive Prim, unsigned short* pInt, size_t indexCount){
	m_Primitive = Prim;
	m_pVertexBuffer->SetVertexData((void *)Tex_Vertex, vertexCount);
	m_pIndexBuffer->SetIndexData(pInt, indexCount);
}



void Mesh::SetData(MeshVertex* Tex_Vertex, size_t vertexCount, Primitive Prim, unsigned short* pInt, size_t indexCount){
	m_Primitive = Prim;

	m_TextureVertex = Tex_Vertex;
	m_VertexCount = vertexCount;

	m_pVertexBuffer->SetVertexData((void *)Tex_Vertex, vertexCount);
	m_pIndexBuffer->SetIndexData(pInt, indexCount);

	DrawBB();
}

void Mesh::SetTexture(Texture t){
	m_pTexture = t;
}

void Mesh::Draw(){
	m_pVertexBuffer->Bind();
	m_pIndexBuffer->Bind();
	
	m_rRenderer.SetCurrentTexture(m_pTexture);
	m_rRenderer.Draw(m_Primitive);
}



void Mesh::DrawBB() const{
	D3DXVECTOR3 v_BoundMin;
	D3DXVECTOR3 v_BoundMax;

	v_BoundMin = D3DXVECTOR3(m_TextureVertex[0].x, m_TextureVertex[0].y, m_TextureVertex[0].z);
	v_BoundMax = D3DXVECTOR3(m_TextureVertex[0].x, m_TextureVertex[0].y, m_TextureVertex[0].z);


	for (int i = 1; i < m_VertexCount; i++){
		// X
		if (m_TextureVertex[i].x > v_BoundMax.x)
			v_BoundMax.x = m_TextureVertex[i].x;
		else if (m_TextureVertex[i].x < v_BoundMin.x)
			v_BoundMin.x = m_TextureVertex[i].x;

		// Y
		if (m_TextureVertex[i].y > v_BoundMax.y)
			v_BoundMax.y = m_TextureVertex[i].y;
		else if (m_TextureVertex[i].y < v_BoundMin.y)
			v_BoundMin.y = m_TextureVertex[i].y;

		// Z
		if (m_TextureVertex[i].z > v_BoundMax.z)
			v_BoundMax.z = m_TextureVertex[i].z;
		else if (m_TextureVertex[i].z < v_BoundMin.z)
			v_BoundMin.z = m_TextureVertex[i].z;
	}

	m_pBB[0] = v_BoundMax;
	m_pBB[1] = D3DXVECTOR3(v_BoundMax.x, v_BoundMin.y, v_BoundMax.z);
	m_pBB[2] = D3DXVECTOR3(v_BoundMin.x, v_BoundMin.y, v_BoundMax.z);
	m_pBB[3] = D3DXVECTOR3(v_BoundMin.x, v_BoundMax.y, v_BoundMax.z);
	m_pBB[4] = D3DXVECTOR3(v_BoundMax.x, v_BoundMax.y, v_BoundMin.z);
	m_pBB[5] = D3DXVECTOR3(v_BoundMax.x, v_BoundMin.y, v_BoundMin.z);
	m_pBB[6] = v_BoundMin;
	m_pBB[7] = D3DXVECTOR3(v_BoundMin.x, v_BoundMax.y, v_BoundMin.z);
}

