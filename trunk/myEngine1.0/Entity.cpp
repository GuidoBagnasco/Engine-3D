#define NOMINMAX
#include <algorithm>
#include "Entity.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <d3dx9.h>
using namespace engine;

Entity::Entity() :
_PosX(0.0f),
_PosY(0.0f),
_PosZ(0.0f),
_Rot(0.0f),
_ScaleX(1.0f),
_ScaleY(1.0f),
_ScaleZ(1.0f),
m_fPrevPosX(0.0f),
m_fPrevPosY(0.0f),
m_fPrevPosZ(0.0f),
m_sColGroup(""),
m_sName(""),
_TrMatrix(new D3DXMATRIX()),
p_vb(NULL),
p_ib(NULL)
{
	UpdateLocalTransformation();
}

Entity::~Entity(){
	delete _TrMatrix;
	_TrMatrix = NULL;

	if (p_vb){
		delete p_vb;
		p_vb = NULL;
	}

	if (p_ib){
		delete p_ib;
		p_ib = NULL;
	}
}

void Entity::SetPos(float fPosX, float fPosY, float fPosZ){
	m_fPrevPosX = _PosX;
	m_fPrevPosY = _PosY;
	m_fPrevPosZ = _PosZ;
	
	_PosX = fPosX;
	_PosY = fPosY;
	_PosZ = fPosZ;

	UpdateLocalTransformation();
}

float Entity::PosX() const{
	return _PosX;
}

float Entity::PosY() const{
	return _PosY;
}

float Entity::PosZ() const{
	return _PosZ;
}

float Entity::ScaleX() const {
	return _ScaleX;
}

float Entity::ScaleY() const{
	return _ScaleY;
}

float Entity::ScaleZ() const{
	return _ScaleZ;
}

float Entity::Rotation() const{
	return _Rot;
}

void Entity::SetRotation(float fRotation){
	_Rot = fRotation;
	UpdateLocalTransformation();
}

void Entity::SetScale(float fScaleX, float fScaleY, float fScaleZ){
	_ScaleX = fScaleX;
	_ScaleY = fScaleY;
	_ScaleZ = fScaleZ;
	UpdateLocalTransformation();
}

void Entity::ReturnToPreviousPos(){

	_PosX = m_fPrevPosX;
	_PosY = m_fPrevPosY;
	_PosZ = m_fPrevPosZ;

	UpdateLocalTransformation();
}
#include <iostream>
void Entity::UpdateLocalTransformation(){
	D3DXMATRIX translateMatrix;
	D3DXMatrixTranslation(&translateMatrix, _PosX, _PosY, _PosZ);

	D3DXMATRIX rotationMatrix;
	D3DXMatrixRotationZ(&rotationMatrix, _Rot);

	D3DXMATRIX scaleMatrix;
	D3DXMatrixScaling(&scaleMatrix, _ScaleX, _ScaleY, _ScaleZ);

	D3DXMatrixIdentity(_TrMatrix);
	D3DXMatrixMultiply(_TrMatrix, &translateMatrix, _TrMatrix);
	D3DXMatrixMultiply(_TrMatrix, &rotationMatrix, _TrMatrix);
	D3DXMatrixMultiply(_TrMatrix, &scaleMatrix, _TrMatrix);
	std::cout << _ScaleX << " " << _ScaleY << " " << _ScaleZ << std::endl;
}

Entity::CollisionResult Entity::CheckCollision(Entity& rkEntity2D) const{
	float fOverlapZ = std::max(0.0f,
		std::min(PosZ() + fabs(ScaleZ()) / 2.0f, rkEntity2D.PosZ() + fabs(rkEntity2D.ScaleZ()) / 2.0f) -
		std::max(PosZ() - fabs(ScaleZ()) / 2.0f, rkEntity2D.PosZ() - fabs(rkEntity2D.ScaleZ()) / 2.0f)
		);
	float fOverlapX = std::max(0.0f,
		std::min(PosX() + fabs(ScaleX()) / 2.0f, rkEntity2D.PosX() + fabs(rkEntity2D.ScaleX()) / 2.0f) -
		std::max(PosX() - fabs(ScaleX()) / 2.0f, rkEntity2D.PosX() - fabs(rkEntity2D.ScaleX()) / 2.0f)
		);
	float fOverlapY = std::max(0.0f,
		std::min(PosY() + fabs(ScaleY()) / 2.0f, rkEntity2D.PosY() + fabs(rkEntity2D.ScaleY()) / 2.0f) -
		std::max(PosY() - fabs(ScaleY()) / 2.0f, rkEntity2D.PosY() - fabs(rkEntity2D.ScaleY()) / 2.0f)
		);

	if (fOverlapX != 0.0f && fOverlapY != 0.0f && fOverlapZ != 0.0f){
		if (fOverlapX > fOverlapZ){
			return CollisionZ;
		}
		else if (fOverlapX > fOverlapY){
			return CollisionVertical;
		}
		else{
			return CollisionHorizontal;
		}
	}
	
	return NoCollision;
}

void Entity::DrawAABB(Renderer& rkRenderer) const{
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