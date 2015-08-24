#pragma once
#include "myEngine_API.h"
#include "TinyXML\tinyxml2.h"
#include <string>
#include <map>
#include <vector>
#include "RenderTypes.h"
#include "XMLParser.h"

namespace engine{
	class Scene;
	class Sprite;
	class Quad;
	class Renderer;
	class Animation;
	class TileMap;
	class Tile;
	class Mesh;

	class MYENGINE_API Importer{
		public:
			Importer();
			~Importer();
			bool Init(Renderer&);
			bool importScene(Scene&, std::string fileName);

			//void importSprite(Scene&, tinyxml2::XMLElement*);
			void ImportMesh(Scene&, tinyxml2::XMLElement*);
			//void importQuad(Scene&, tinyxml2::XMLElement*);
			//void importTileMap(Scene&, const char*);
			void ImportAnimations(std::vector<Animation*>&, tinyxml2::XMLElement*);

		static Importer* GetInstance() {
			return m_oInstance;
		}

		Renderer* GetRenderer() const;
		Texture LoadTexture(std::string path, int KeyCode);
		Texture LoadTexture(XMLNode& kTextureNode, const char* textureName);
		private:
			TileMap* LoadTileMap(XMLNode& kTileMapNode);
			Tile* CreateTile(XMLNode& kTileSetNode, Texture pkTexture, unsigned int iId, int textWidth, int textHeight);
			int ColorConverter(int);
			static Importer* m_oInstance;
				   Renderer* m_oRenderer;
				   std::map<std::string, Texture> m_mTextureMap;
				   std::map<std::string , TileMap*> m_mTilemaps;
	};
}