#include "Entity.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <d3dx9.h>
using namespace engine;


Entity::Entity() :
m_sColGroup(""),
m_sName(""),
p_vb(NULL),
p_ib(NULL)
{

}


Entity::~Entity(){
	if (p_vb){
		delete p_vb;
		p_vb = NULL;
	}

	if (p_ib){
		delete p_ib;
		p_ib = NULL;
	}
}

