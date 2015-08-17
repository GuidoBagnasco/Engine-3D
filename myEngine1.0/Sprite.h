#pragma once
#include "Entity.h"
#include <string>
#include <map>
namespace engine{
	class Renderer;
	class Animation;
	class Timer;
	class MYENGINE_API Sprite : public Entity{

	public:
		Sprite();
		~Sprite();
	private:
		TextureVertex* _Vertex;
		Texture		m_tTexture;

		std::map<std::string, Animation*> m_pkAnimationList;
		Animation* m_pkCurrentAnimation;
		unsigned int m_uiPreviousFrame;

	public:
		void draw(Renderer& r) const;
		void setTexture(Texture&);
		void setTextureCoords(float, float, float, float,
							  float, float, float, float);
		void Sprite::SetSpriteArea(unsigned int p_iPosX, unsigned int p_iPosY, unsigned int p_uiWidth, unsigned int p_uiHeight, unsigned int textWidth, unsigned int textHeight);
		void AddAnimation(Animation* pkAnimation);
		void setAnimation(Animation* pkAnimation);
		void setAnimation(std::string);
		void update(Timer&);

	};
}