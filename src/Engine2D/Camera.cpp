#include <Camera.h>
#include "Renderer.h"
using namespace Engine;


Camera::Camera(Renderer* renderer){
	mp_kRenderer = renderer;
	
	kLookPos = D3DXVECTOR3(posX, posY, posZ);			// (1, 0, 0)
	kViewPos = D3DXVECTOR3(0.00f, 0.00f, -900.00f);
	kViewUp = D3DXVECTOR3(0.00f, 1.00f, 0.00f);			// (0, 1, 0)
	kRight = D3DXVECTOR3(1.00f, 0.00f, 0.00f);

}



void Camera::Walk(float ammount){
	float movX = (kLookPos.x - kViewPos.x) * ammount * speed;
	float movZ = (kLookPos.z - kViewPos.z) * ammount * speed;

	kViewPos.x += movX;
	kViewPos.z += movZ;
	kLookPos.x += movX;
	kLookPos.z += movZ;
}


void Camera::Strafe(float ammount){
	D3DXVec3Cross(&kRight, &(kLookPos-kViewPos), &kViewUp);
	float movX = (kRight.x - kViewPos.x) * ammount * speed;
	float movZ = (kRight.z - kViewPos.z) * ammount * speed;

	kViewPos.x += movX;
	kViewPos.z += movZ;
	kLookPos.x += movX;
	kLookPos.z += movZ;
	/*
	float movX = (kViewPos.x - kViewPos.z) * ammount * speed;
	float movZ = (kViewPos.z + kViewPos.x) * ammount * speed;

	kViewPos.x += movX;
	kViewPos.z += movZ;
	kLookPos.x += movX;
	kLookPos.z += movZ;
	*/
	//kViewPos.x += ammount * speed;
}

void Camera::Fly(float ammount){
	kViewPos.y += ammount * speed;
}

//y
void Camera::Yaw(float angle){
	kLookPos.x = kLookPos.x * cos(angle * speed) + kLookPos.z * sin(angle * speed);
	kLookPos.z = -kLookPos.x * sin(angle * speed) + kLookPos.z * cos(angle * speed);
}

//x
void Camera::Pitch(float angle){
	kLookPos.y = kLookPos.y * cos(angle * speed) - kLookPos.z * sin(angle * speed);
	kLookPos.z = kLookPos.y * sin(angle * speed) + kLookPos.z * cos(angle * speed);
}

//z
void Camera::Roll(float angle){
	kLookPos.x = kLookPos.x * cos(angle * speed) - kLookPos.y * sin(angle * speed);
	kLookPos.y = kLookPos.x * sin(angle * speed) + kLookPos.y * cos(angle * speed);
}


void Camera::UpdateCamera(){
	mp_kRenderer->UpdateView(&kViewPos, &kLookPos);
}



Camera::~Camera(){
	delete mp_kRenderer;
	mp_kRenderer = NULL;
}