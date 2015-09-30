#include "Node.h"
#include "Mesh.h"
#include "Renderer.h"

#include <iostream>
using namespace engine;


Node::Node() :
_PosX(0.0f),
_PosY(0.0f),
_PosZ(0.0f),
_RotX(0.0f),
_RotY(0.0f),
_RotZ(0.0f),
_ScaleX(1.0f),
_ScaleY(1.0f),
_ScaleZ(1.0f),
m_fPrevPosX(0.0f),
m_fPrevPosY(0.0f),
m_fPrevPosZ(0.0f),
pivot(D3DXVECTOR3(0.0f,0.0f,0.0f))
{
	D3DXMatrixIdentity(&world);
	D3DXMatrixIdentity(&defaultMatrix);
	D3DXMatrixIdentity(&local);
}

Node::~Node(){
	for (int i = 0; i < m_vChilds.size(); i++) {
		delete m_vChilds[i];
		m_vChilds[i] = NULL;
	}

	for (int i = 0; i < m_vMeshes.size(); i++) {
		delete m_vMeshes[i];
		m_vMeshes[i] = NULL;
	}
}


void Node::SetPos(float fPosX, float fPosY, float fPosZ){
	m_fPrevPosX = _PosX;
	m_fPrevPosY = _PosY;
	m_fPrevPosZ = _PosZ;

	_PosX = fPosX;
	_PosY = fPosY;
	_PosZ = fPosZ;
}


float Node::PosX() const{
	return _PosX;
}


float Node::PosY() const{
	return _PosY;
}


float Node::PosZ() const{
	return _PosZ;
}


float Node::ScaleX() const {
	return _ScaleX;
}


float Node::ScaleY() const{
	return _ScaleY;
}


float Node::ScaleZ() const{
	return _ScaleZ;
}


float Node::RotationX() const{
	return _RotX;
}

float Node::RotationY() const{
	return _RotY;
}

float Node::RotationZ() const{
	return _RotZ;
}



void Node::SetRotation(float fRotX, float fRotY, float fRotZ){
	//x - x1
	_RotX = fRotX;
	_RotY = fRotY;
	_RotZ = fRotZ;
	/*
	_RotX -= pivot.x;
	_RotY -= pivot.y;
	_RotZ -= pivot.z;
	*/
}


void Node::SetPivot(float x, float y, float z){
	pivot = D3DXVECTOR3(x, y, z);
}


void Node::SetScale(float fScaleX, float fScaleY, float fScaleZ){
	_ScaleX = fScaleX;
	_ScaleY = fScaleY;
	_ScaleZ = fScaleZ;
}

void Node::SetFirstTransformationFromAssimp(float a1, float a2, float a3, float a4,
	float b1, float b2, float b3, float b4,
	float c1, float c2, float c3, float c4,
	float d1, float d2, float d3, float d4){


	defaultMatrix._11 = a1;
	defaultMatrix._12 = a2;
	defaultMatrix._13 = a3;
	defaultMatrix._14 = a4;

	defaultMatrix._21 = b1;
	defaultMatrix._22 = b2;
	defaultMatrix._23 = b3;
	defaultMatrix._24 = b4;

	defaultMatrix._31 = c1;
	defaultMatrix._32 = c2;
	defaultMatrix._33 = c3;
	defaultMatrix._34 = c4;

	defaultMatrix._41 = d1;
	defaultMatrix._42 = d2;
	defaultMatrix._43 = d3;
	defaultMatrix._44 = d4;
}

void Node::SetDiscomposedTransformationFromAssimp(D3DXVECTOR3 sca, D3DXQUATERNION rot, D3DXVECTOR3 pos)
{


}


void Node::ReturnToPreviousPos(){
	_PosX = m_fPrevPosX;
	_PosY = m_fPrevPosY;
	_PosZ = m_fPrevPosZ;
}

void Node::Draw(Renderer& r){
	D3DXMatrixIdentity(&world);
	r.SetMatrix(World, &world);
	UpdateTransformation(world);
	NodeDraw(r);
}

void Node::UpdateTransformation(D3DXMATRIX parentWorld){
	D3DXMATRIX translation;
	D3DXMATRIX scalation;
	D3DXMATRIX rotx;
	D3DXMATRIX roty;
	D3DXMATRIX rotz;

	D3DXMatrixIdentity(&local);



	// translation
	D3DXMatrixTranslation(&translation, _PosX + pivot.x, _PosY + pivot.y, _PosZ + pivot.z);
	D3DXMatrixMultiply(&local, &translation, &local);


	//	rotation
	D3DXMatrixRotationX(&rotx, _RotX);
	D3DXMatrixRotationY(&roty, _RotY);
	D3DXMatrixRotationZ(&rotz, _RotZ);

	D3DXMatrixMultiply(&local, &rotx, &local);
	D3DXMatrixMultiply(&local, &roty, &local);
	D3DXMatrixMultiply(&local, &rotz, &local);


	
	
	// scalation
	D3DXMatrixScaling(&scalation, _ScaleX, _ScaleY, _ScaleZ);
	D3DXMatrixMultiply(&local, &scalation, &local);

	D3DXMatrixMultiply(&local, &local, &defaultMatrix);
	D3DXMatrixMultiply(&world, &local, &parentWorld);

	if (m_vChilds.size() > 0){
		for (int i = 0; i <m_vChilds.size(); i++){
			m_vChilds[i]->UpdateTransformation(world);
		}
	}
}

void Node::NodeDraw(Renderer& r){

	if (m_vChilds.size() > 0){
		for (int i = 0; i < m_vChilds.size(); i++){
			m_vChilds[i]->NodeDraw(r);
		}
	}

	if (m_vMeshes.size() > 0){
		for (int i = 0; i < m_vMeshes.size(); i++){
			r.SetMatrix(World, &world);
			m_vMeshes[i]->Draw();
		}
	}

}

void Node::AddChild(Node* child){
	m_vChilds.push_back(child);
}

void Node::AddMesh(Mesh* child){
	m_vMeshes.push_back(child);
}


Node* Node::GetChild(int index){
	if (m_vChilds.empty())
		return this;

	index = index > m_vChilds.size() ? m_vChilds.size() - 1 : index;
	index = index < 0 ? 0 : index;
	return m_vChilds[index];
}



int Node::GetChildsCount(){
	if (m_vChilds.empty())
		return -1;
	return m_vChilds.size();
}