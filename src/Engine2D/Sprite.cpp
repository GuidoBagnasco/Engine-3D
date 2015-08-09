#define NOMINMAX

#include "Texture.h"
#include "Sprite.h"
#include "Renderer.h"

#include "Importer.h"
#include "Timer.h"

#include <cstddef>
#include <limits>
#include <iostream>



using namespace Engine;


Sprite::Sprite() : Entity2D(), m_pkAnimation(NULL), m_uiPreviousFrame( std::numeric_limits<unsigned int>::max() ){

	uiVertexCount = 4;

	vertices[0].x = -0.5;
	vertices[0].y =  0.5;
	vertices[0].z =  1.0f;
	vertices[0].u =  0.0f;
	vertices[0].v =  0.0f;

	vertices[1].x =  0.5;
	vertices[1].y =  0.5;
	vertices[1].z =  1.0f;
	vertices[1].u =  1.0f;
	vertices[1].v =  0.0f;

	vertices[2].x = -0.5;
	vertices[2].y = -0.5;
	vertices[2].z =  1.0f;
	vertices[2].u =  0.0f;
	vertices[2].v =  1.0f;

	vertices[3].x =  0.5;
	vertices[3].y = -0.5;
	vertices[3].z =  1.0f;
	vertices[3].u =  1.0f;
	vertices[3].v =  1.0f;

	SetScale(1, 1);
}



void Sprite::SetTexture(boost::shared_ptr<Texture> _Texture){
	texture = _Texture.get();
}



void Sprite::SetTexture(Texture& _Texture){
	texture = &_Texture;
}



void Sprite::SetCoords(float U1, float V1, float U2, float V2, float U3, float V3, float U4, float V4){
	vertices[0].u = U1;
	vertices[0].v = V1;

	vertices[1].u = U2;
	vertices[1].v = V2;

	vertices[2].u = U3;
	vertices[2].v = V3;

	vertices[3].u = U4;
	vertices[3].v = V4;
}



void Sprite::Draw(Renderer* renderer){
	Entity2D::Draw(renderer);
	renderer->SetTexture(texture);
	renderer->DrawSP(vertices, uiVertexCount);
}



void Sprite::Update(Timer& pkTimer){
	if(!m_pkAnimation){
		return;
	}

	m_pkAnimation->Update(pkTimer);
	unsigned int uiCurrentFrame = m_pkAnimation->currentFrame();
	if(uiCurrentFrame != m_uiPreviousFrame){
		const Animation::Frame& rkFrame = m_pkAnimation->Frames()[uiCurrentFrame];
		SetCoords(rkFrame.U1, rkFrame.V1, rkFrame.U2, rkFrame.V2, rkFrame.U3, rkFrame.V3, rkFrame.U4, rkFrame.V4);
	}
}



void Sprite::AddAnimation(Animation* pkAnimation){
	m_pkAnimationList.push_back(*pkAnimation);
}



void Sprite::AddAnimation(std::vector<Animation> animation){
	m_pkAnimationList = animation;
	if(!m_pkAnimationList.empty())
		m_pkAnimation = &m_pkAnimationList[0];
}



void Sprite::SetAnimation(std::string pkName){
	if(m_pkAnimationList.empty()) return;
	std::vector<Animation>::iterator iter;
	for(iter = m_pkAnimationList.begin(); iter != m_pkAnimationList.end(); iter++){
		if(iter->GetName() == pkName){
			m_pkAnimation = iter._Ptr;
			return;
		}
	}
}



void Sprite::SetAnimation(Animation* pkAnimation){
	m_pkAnimation = pkAnimation;
	m_pkAnimationList.push_back(*pkAnimation);
}



void Sprite::SetSpriteArea(unsigned int p_iPosX, unsigned int p_iPosY, unsigned int p_uiWidth, unsigned int p_uiHeight, unsigned int textWidth, unsigned int textHeight){
// Width and height of the texture
	unsigned int f_uiTextureWidth = textWidth;
	unsigned int f_uiTextureHeight = textHeight;

	double f_fUnear = ((float)p_iPosX) / f_uiTextureWidth; // Near u
	double f_fUfar = (((float)p_iPosX + (float)p_uiWidth)) / f_uiTextureWidth;	// Far u
	double f_fVnear = ((float)p_iPosY) / f_uiTextureHeight;	// Near v
	double f_fVfar = (((float)p_iPosY + (float)p_uiHeight)) / f_uiTextureHeight;	// Far v
	
	vertices[0].u = f_fUnear;
	vertices[1].u = f_fUfar;
	vertices[2].u = f_fUnear;
	vertices[3].u = f_fUfar;

	vertices[0].v = f_fVnear;
	vertices[1].v = f_fVnear;
	vertices[2].v = f_fVfar;
	vertices[3].v = f_fVfar;
}



Sprite::~Sprite(){
	delete[] &vertices;
	m_pkAnimationList.clear();
}