#pragma once
#include "myEngine_API.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>
namespace engine{
	class Renderer;
	class Timer;
	class MYENGINE_API Camera{
	public:
		Camera(Renderer& r);

	protected:
		Renderer* m_pkRenderer;
		D3DXVECTOR3 m_Position;
		D3DXVECTOR3 m_LookAt;
		D3DXVECTOR3 m_Right;
		D3DXVECTOR3 m_Up;
		bool m_bChanged;
		float m_RotateAroundUp;
		float m_RotateAroundRight;
		float m_RotateAroundLookAt;

		D3DXMATRIX m_MatView;

	public:

		static Camera* Main(){
			return instance;
		}


		void SetPosition(float fX, float fY, float fZ);
		D3DXVECTOR3	GetPosition() { return m_Position; }
		void MoveForward(float Dist);
		void MoveRight(float Dist);
		void MoveUp(float Dist);
		void MoveInDirection(float Dist, float fDirectionX, float fDirectionY, float fDirectionZ);
		void RotateDown(float Angle);
		void RotateRight(float Angle);
		void Roll(float Angle);

	protected:
		void Update();
		friend class Engine;
	private:
		~Camera();
		static Camera* instance;
		friend class Renderer;
	};
}