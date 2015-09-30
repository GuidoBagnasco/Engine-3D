#define NOMINMAX
#include "Mesh.h"
#include "Node.h"
#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include <algorithm>
using namespace engine;


Mesh::Mesh(Renderer& r, bool isTextured) :/* Entity(),*/ m_rRenderer(r), m_pVertexBuffer(NULL), m_pIndexBuffer(NULL), m_pTexture(NoTexture){

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
	m_pVertexBuffer->SetVertexData((void *)Tex_Vertex, vertexCount);
	m_pIndexBuffer->SetIndexData(pInt, indexCount);
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


/*
void Mesh::DrawAABB(Renderer& rkRenderer) const{
	static ColorVertex s_akAABBVertices[5];
	static bool s_bIsInitialized = false;
	if (!s_bIsInitialized){
		s_bIsInitialized = true;

		s_akAABBVertices[0].x = -0.5;	s_akAABBVertices[0].y = -0.5;	s_akAABBVertices[0].z = 0.0; s_akAABBVertices[0].color = engine_COLOR_RGB(255, 50, 50);
		s_akAABBVertices[1].x = -0.5;	s_akAABBVertices[1].y = 0.5;	s_akAABBVertices[1].z = 0.0; s_akAABBVertices[1].color = engine_COLOR_RGB(255, 70, 70);
		s_akAABBVertices[2].x = 0.5;	s_akAABBVertices[2].y = 0.5;	s_akAABBVertices[2].z = 0.0; s_akAABBVertices[2].color = engine_COLOR_RGB(255, 30, 30);
		s_akAABBVertices[3].x = 0.5;	s_akAABBVertices[3].y = -0.5;	s_akAABBVertices[3].z = 0.0; s_akAABBVertices[3].color = engine_COLOR_RGB(255, 15, 15);
		s_akAABBVertices[4].x = -0.5;	s_akAABBVertices[4].y = -0.5;	s_akAABBVertices[4].z = 0.0; s_akAABBVertices[4].color = engine_COLOR_RGB(255, 95, 90);
	}

	rkRenderer.SetCurrentTexture(NoTexture);
	rkRenderer.SetMatrix(World, _TrMatrix);
	rkRenderer.Draw(s_akAABBVertices, engine::LineStrip, 5);
}
*/