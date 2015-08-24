#include "Mesh.h"
#include "Renderer.h"
#include "pg2_vertexbuffer.h"
#include "pg2_indexbuffer.h"
#include "RenderTypes.h"
using namespace engine;




Mesh::Mesh(Renderer& rkRenderer) : Entity(){
	m_pkRenderer = &rkRenderer;
	p_vb = rkRenderer.CreateVertexBuffer(sizeof(ColorVertex), ColorVertexType);
	p_ib = rkRenderer.CreateIndexBuffer();
}




Mesh::Mesh(Renderer& rkRenderer, std::vector<ColorVertex> vertices) : Entity(), _Vertex(new ColorVertex[sizeof(vertices)]){
	m_pkRenderer = &rkRenderer;
	p_vb = rkRenderer.CreateVertexBuffer(sizeof(ColorVertex), ColorVertexType);
	p_ib = rkRenderer.CreateIndexBuffer();
}



Mesh::~Mesh(){
	if(p_vb){
		delete p_vb;
		p_vb = NULL;
	}

	if(p_ib){
		delete p_ib;
		p_ib = NULL;
	}
}


void Mesh::SetData(ColorVertex* Tex_Vertex, size_t vertexCount, engine::Primitive Prim, unsigned short* pInt, size_t indexCount){
	m_primType = Prim;
	p_vb->setVertexData((void *)Tex_Vertex, vertexCount);
	p_ib->setIndexData(pInt, indexCount);
}


void Mesh::Draw() const{
	p_vb->bind();
	p_ib->bind();

	m_pkRenderer->SetCurrentTexture(engine::NoTexture);
	m_pkRenderer->SetMatrix(World, _TrMatrix);
	m_pkRenderer->Draw(m_primType);
}