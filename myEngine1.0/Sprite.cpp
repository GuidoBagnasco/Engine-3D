#include "Sprite.h"
#include "Renderer.h"
#include "animation.h"
#include "timer\pg1_timer.h"
#include <d3dx9.h>
using namespace engine;

Sprite::Sprite() :
Entity(),
//m_kTexture(NoTexture),
m_tTexture(NoTexture),
m_pkCurrentAnimation(NULL),
_Vertex(new TextureVertex[4]){

	_Vertex[0].x = -0.5f;	_Vertex[0].y =  0.5f;	_Vertex[0].z = 0.0f;
	_Vertex[1].x =  0.5f;	_Vertex[1].y =  0.5f;	_Vertex[1].z = 0.0f;
	_Vertex[2].x = -0.5f;	_Vertex[2].y = -0.5f;	_Vertex[2].z = 0.0f;
	_Vertex[3].x =  0.5f;	_Vertex[3].y = -0.5f;	_Vertex[3].z = 0.0f;

	_Vertex[0].u = 0.0;	_Vertex[0].v = 0.0;
	_Vertex[1].u = 1.0;	_Vertex[1].v = 0.0;
	_Vertex[2].u = 0.0;	_Vertex[2].v = 1.0;
	_Vertex[3].u = 1.0;	_Vertex[3].v = 1.0;
}

Sprite::~Sprite(){
	delete[] _Vertex;
	_Vertex = NULL;

	m_pkAnimationList.clear();
}

void Sprite::setTextureCoords(float U1, float V1,
	float U2, float V2,
	float U3, float V3,
	float U4, float V4){
	_Vertex[0].u = U1;	_Vertex[0].v = V1;
	_Vertex[1].u = U2;	_Vertex[1].v = V2;
	_Vertex[2].u = U3;	_Vertex[2].v = V3;
	_Vertex[3].u = U4;	_Vertex[3].v = V4;
}

void Sprite::AddAnimation(Animation* pkAnimation){

	if (pkAnimation == NULL) return;

	if (m_pkAnimationList.count(pkAnimation->getName()))
		return;

	m_pkAnimationList[pkAnimation->getName()] = pkAnimation;
	return;
}
void Sprite::setAnimation(Animation* pkAnimation){
	if (pkAnimation == NULL) return;
	AddAnimation(pkAnimation);

	m_pkCurrentAnimation = pkAnimation;
}
void Sprite::setAnimation(std::string name){
	if (m_pkAnimationList.count(name)){
		Animation* anim = m_pkAnimationList[name];
		setAnimation(anim);
	}
}
void Sprite::update(Timer& t){
	if (!m_pkCurrentAnimation){
		return;
	}
	m_pkCurrentAnimation->update(t);
	unsigned int uiCurrentFrame = m_pkCurrentAnimation->currentFrame();
	if (uiCurrentFrame != m_uiPreviousFrame){
		const Animation::Frame& rkFrame = m_pkCurrentAnimation->frames()[uiCurrentFrame];
		setTextureCoords(rkFrame.u1, rkFrame.v1, rkFrame.u2, rkFrame.v2, rkFrame.u3, rkFrame.v3, rkFrame.u4, rkFrame.v4);
	}
}
void Sprite::SetSpriteArea(unsigned int p_iPosX, unsigned int p_iPosY, unsigned int p_uiWidth, unsigned int p_uiHeight, unsigned int textWidth, unsigned int textHeight)
{
	//obtengo el ancho y alto de la textura
	unsigned int f_uiTextureWidth = textWidth;
	unsigned int f_uiTextureHeight = textHeight;

	double f_fUnear = ((float)p_iPosX) / f_uiTextureWidth; //calculo el punto U cercano
	double f_fUfar = (((float)p_iPosX + (float)p_uiWidth)) / f_uiTextureWidth;//ahora el punto U lejano
	double f_fVnear = ((float)p_iPosY) / f_uiTextureHeight;//calculo elpunto V cercano
	double f_fVfar = (((float)p_iPosY + (float)p_uiHeight)) / f_uiTextureHeight;//calculo el punto V lejano

	//aplico a los vertices	
	_Vertex[2].u = f_fUnear;	_Vertex[0].v = f_fVnear;
	_Vertex[0].u = f_fUnear;	_Vertex[3].v = f_fVfar;
	_Vertex[3].u = f_fUfar;		_Vertex[1].v = f_fVnear;
	_Vertex[1].u = f_fUfar;		_Vertex[2].v = f_fVfar;
}
void Sprite::setTexture(Texture& texture){
	m_tTexture = texture;
}

void Sprite::draw(Renderer& r) const{
	r.setCurrentTexture(m_tTexture);
	r.setMatrix(World, _TrMatrix);
	r.Draw(_Vertex, engine::TriangleStrip, 4);
}
