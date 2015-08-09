#ifndef TILE_H
#define TILE_H
#include "Defines.h"
#include "Sprite.h"
#include "Renderer.h"

namespace Engine{

class ENGINE_API Tile: public Sprite{
public:
	~Tile(){ }

	void Draw(Renderer *m_pkRenderer){
		Sprite::Draw(m_pkRenderer);
	}

};

}
#endif