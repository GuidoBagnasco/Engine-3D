#pragma once
#include "myEngine_API.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include "Entity.h"


namespace engine{
	
	class Mesh;
	class Renderer;

	class MYENGINE_API Node : public Entity{
		private:

			D3DXVECTOR3 m_Pos;
			D3DXVECTOR3 m_Sc;

			float _PosX, _PosY, _PosZ;
			float m_fPrevPosX, m_fPrevPosY, m_fPrevPosZ;
			float _RotX, _RotY, _RotZ;
			float _ScaleX;
			float _ScaleY;
			float _ScaleZ;
			void UpdateTransformation(D3DXMATRIX transformation);

			std::vector<Node*> m_vChilds;
			std::vector<Mesh*> m_vMeshes;

		public:
			void Draw(Renderer&);	// Llama UpdateTransformation, NodeDraw, 
			void NodeDraw(Renderer&);


		public:
			D3DXVECTOR3 pivot;
			D3DXMATRIX local;
			D3DXMATRIX world;
			D3DXMATRIX defaultMatrix;

			Node();
			~Node();

			void SetPos(float fPosX, float fPosY, float fPosZ);
			void SetRotation(float,float,float);
			void SetScale(float fScale, float fScaleY, float fScaleZ = 1.0f);
			void SetPivot(float, float, float);
			void SetFirstTransformationFromAssimp(float a1, float a2, float a3, float a4, 
												  float b1, float b2, float b3, float b4, 
												  float c1, float c2, float c3, float c4, 
												  float d1, float d2, float d3, float d4);
			void SetDiscomposedTransformationFromAssimp(D3DXVECTOR3, D3DXQUATERNION, D3DXVECTOR3);

			float PosX() const;
			float PosY() const;
			float PosZ() const;
			float RotationX() const;
			float RotationY() const;
			float RotationZ() const;
			float ScaleX() const;
			float ScaleY() const;
			float ScaleZ() const;

			void ReturnToPreviousPos();

			void AddChild(Node* child);
			void AddMesh(Mesh* child);
			Node* GetChild(int index);
			int GetChildsCount();
	};

}	// namespace