#ifndef CAMERA_H
#define CAMERA_H
#include "Defines.h"
#include "D3dx9math.h"
#include <vector>
#include <string>

namespace Engine{
	class Renderer;

	class ENGINE_API Camera{
	private:
		D3DXMATRIX kMatrix;
		D3DXVECTOR3 kLookPos;
		D3DXVECTOR3 kViewPos;
		D3DXVECTOR3 kViewUp;
		D3DXVECTOR3 kRight;

		Renderer* mp_kRenderer;

		float speed = 1.00f;
		float posX, posY, posZ;

	public:
		Camera(Renderer* renderer);
		~Camera();
		void Init();
		void Walk(float speed);
		void Strafe(float speed);
		void Fly(float speed);

		void Yaw(float speed);
		void Pitch(float speed);
		void Roll(float speed);

		void UpdateCamera();
	};
};

#endif
