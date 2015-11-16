#include "Node.h"
#include "Mesh.h"
#include "Renderer.h"

#include <iostream>
using namespace engine;


Node::Node()
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



void Node::SetTransformationFromAssimp(float a1, float a2, float a3, float a4,
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
	D3DXMatrixTranslation(&translation, m_position.x + pivot.x, m_position.y + pivot.y, m_position.z + pivot.z);
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

	SetBB();
}


void Node::NodeDraw(Renderer& r){
	if (r.m_frustum->CheckCube(m_bbCenter.x, m_bbCenter.y, m_bbCenter.z, D3DXVec3Length(&(m_bbCenter - m_BoundMax)))){
		//std::cout << GetName() <<"   " << D3DXVec3Length(&(m_bbCenter - m_BoundMax)) << std::endl;
		// Chech Center & bounds max
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
	else{
		//std::cout << D3DXVec3Length(&(m_bbCenter - m_BoundMax)) << std::endl;
		// Never enters here!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		std::cout << GetName() + " is not drawn." << std::endl;
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



Node* Node::GetChild(std::string name){
	if (m_vChilds.empty())
		return this;

	for (short i = 0; i < m_vChilds.size(); i++){
		if (m_vChilds[i]->GetName() == name)
			return m_vChilds[i];
	}

	return this;
}



int Node::GetChildsCount(){
	if (m_vChilds.empty())
		return -1;
	return m_vChilds.size();
}


void Node::SetBB(){
	if (!m_vMeshes.empty()){
		D3DXVECTOR3 v_vertices[8];
		GetBBCenter(m_vMeshes[0]->m_pBB);
		for (int i = 0; i < 8; i++)
			D3DXVec3TransformCoord(&v_vertices[0], &m_vMeshes[0]->m_pBB[i], &world);

		m_BoundMax = v_vertices[0];

		for (int i = 1; i < 8; i++){
			// X
			if (v_vertices[i].x > m_BoundMax.x)
				m_BoundMax.x = v_vertices[i].x;

			// Y
			if (v_vertices[i].y > m_BoundMax.y)
				m_BoundMax.y = v_vertices[i].y;

			// Z
			if (v_vertices[i].z > m_BoundMax.z)
				m_BoundMax.z = v_vertices[i].z;
		}
	}
	else if (!m_vChilds.empty()){

		for (int i = 0; i < m_vChilds.size(); i++){
			D3DXVECTOR3 vChildMax = m_vChilds[i]->m_BoundMax;

			if (vChildMax.x > m_BoundMax.x)
				m_BoundMax.x = vChildMax.x;

			if (vChildMax.y > m_BoundMax.y)
				m_BoundMax.y = vChildMax.y;

			if (vChildMax.z > m_BoundMax.z)
				m_BoundMax.z = vChildMax.z;
		}
	}
}



void Node::GetBBCenter(D3DXVECTOR3* vertices){
	for (int i = 0; i < 8; i++){
		m_bbCenter += vertices[i];
	}

	m_bbCenter /= 8;
}