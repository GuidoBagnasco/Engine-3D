#ifndef SPRITE_H
#define SPRITE_H
#include "Entity2D.h"
#include "boost\shared_ptr.hpp"
#include <string>
#include "Animation.h"
#include <vector>

namespace Engine{
class Texture;
class Importer;
class Timer;
class Animation;
class ENGINE_API Sprite : public Entity2D{

private:
	int uiVertexCount;
	D3DTVERTEX vertices[4];
	Texture* texture;

	Importer* mk_importer;

	std::vector<Animation> m_pkAnimationList;
	Animation* m_pkAnimation;
	unsigned int m_uiPreviousFrame;

public:
	Sprite();
	~Sprite();
	void SetTexture(boost::shared_ptr<Texture> _Texture);
	void SetTexture(Texture& _Texture);
	void SetCoords(float U1, float V1, float U2, float V2, float U3, float V3, float U4, float V4);

	void SetAnimation(Animation* pkAnimation);
	void SetAnimation(std::string);

	void Draw(Renderer* renderer);

	void Update(Timer& pkTimer);
	void AddAnimation(Animation* pkAnimation);
	void AddAnimation(std::vector<Animation>);

	void SetSpriteArea(unsigned int p_iPosX, unsigned int p_iPosY, unsigned int p_uiWidth, unsigned int p_uiHeight, unsigned int textWidth, unsigned int textHeight);

};
}

#endif