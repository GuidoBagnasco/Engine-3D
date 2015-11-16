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

			
			void UpdateTransformation(D3DXMATRIX transformation);

			std::vector<Node*> m_vChilds;
			std::vector<Mesh*> m_vMeshes;

			void SetBB();
			void GetBBCenter(D3DXVECTOR3* vertices);

		public:
			void Draw(Renderer&);
			void NodeDraw(Renderer&);


		public:
			
			D3DXMATRIX local;
			D3DXMATRIX world;
			D3DXMATRIX defaultMatrix;

			D3DXVECTOR3 m_BoundMin;
			D3DXVECTOR3 m_BoundMax;
			D3DXVECTOR3 m_bbCenter;


			Node();
			~Node();

			void SetTransformationFromAssimp(float a1, float a2, float a3, float a4, 
											float b1, float b2, float b3, float b4, 
											float c1, float c2, float c3, float c4, 
											float d1, float d2, float d3, float d4);


			void AddChild(Node* child);
			void AddMesh(Mesh* child);
			Node* GetChild(int index);
			Node* GetChild(std::string name);
			int GetChildsCount();
	};

}