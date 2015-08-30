#include "Mesh.h"
#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
using namespace engine;


Mesh::Mesh(Renderer& r, bool isTextured) : Entity(), m_rRenderer(r), m_pVertexBuffer(NULL), m_pIndexBuffer(NULL), m_pTexture(NoTexture) {
	if(!isTextured){
		m_pVertexBuffer = r.CreateVertexBuffer(sizeof(engine::ColorVertex), engine::ColorVertexType);
		m_pIndexBuffer = r.CreateIndexBuffer();
	}else{
		m_pVertexBuffer = r.CreateVertexBuffer(sizeof(engine::MeshVertex), engine::MeshVertexType);
		m_pIndexBuffer = r.CreateIndexBuffer();
	}
}


Mesh::~Mesh(){
	if (m_pVertexBuffer){
		delete m_pVertexBuffer;
		m_pVertexBuffer = NULL;
	}

	if (m_pIndexBuffer){
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
	m_pVertexBuffer->SetVertexData((void *)Tex_Vertex, vertexCount);
	m_pIndexBuffer->SetIndexData(pInt, indexCount);
}



void Mesh::Draw(){
	m_pVertexBuffer->Bind();
	m_pIndexBuffer->Bind();
	
	m_rRenderer.SetCurrentTexture(m_pTexture);
	m_rRenderer.SetMatrix(World, _TrMatrix);
	m_rRenderer.Draw(m_Primitive);
}
