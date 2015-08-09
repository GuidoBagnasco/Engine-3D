#ifndef IMPORTER_H
#define IMPORTER_H

#include "Defines.h"
#include <map>
#include <string>
#include <boost/shared_ptr.hpp>
#include "tinyxml2.h"
#include <iostream>
#include "Scene.h"
#include "XMLParser.h"

#include "Animation.h"
#include <vector>

namespace Engine{
	class Sprite;
	class Renderer;
	class Texture;
	class Tile;
	class TileMap;
	class Game;
	class Animation;
	class ENGINE_API Importer{
	private:
		std::map<std::string, boost::shared_ptr<Texture>> m_sTex;
		std::map<std::string, Sprite> m_sSp;
		Renderer* pk_Renderer;
		tinyxml2::XMLDocument doc;
		tinyxml2::XMLElement *element;
		Texture* LoadTexture(std::string fileName, int keycode);
		void LoadAnimation(std::vector<Animation> **animations, tinyxml2::XMLElement* elements);
	public:
		Importer(Renderer* renderer);
		~Importer();
		bool Load(std::string fileName, Scene& pkScene);
		void ImportSprite(Scene& pkScene,tinyxml2::XMLElement* element);
		void ImportQuad(Scene& pkScene,tinyxml2::XMLElement* element);
		void ImportTileMap(Scene&, tinyxml2::XMLElement*);
		spriteUVInfo SetUV(tinyxml2::XMLElement* element);
	};
}


#endif