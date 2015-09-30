#pragma once
#include "myEngine_API.h"
#include "TinyXML\tinyxml2.h"
#include <string>
#include <map>
#include <vector>
#include "RenderTypes.h"
#include "XMLParser.h"
#pragma comment(lib, "../external/assimp/lib/assimp.lib")

// Estructuras de ayuda de Assimp
struct aiNode;
struct aiMesh;
struct aiMaterial;
struct aiScene;
struct aiAnimation;
// - Fin Estructuras de Ayuda de Assimp


namespace engine{
	class Scene;
	class Sprite;
	class Quad;
	class Renderer;
	class Animation;
	class Importer;
	class TileMap;
	class Tile;
	class Mesh;
	class Node;

	class MYENGINE_API Importer{
		public:
			Importer();
			~Importer();
			bool Init(Renderer&);
			bool ImportScene(Scene&, std::string fileName);

			bool importNode(Node& kNode, aiNode* AiNode, const aiScene* AiScene);
			bool importMesh(const aiMesh* AiMesh, const aiMaterial* AiMaterial, Mesh& kMesh);
			bool importScene(const std::string& FileName, Node& theNode);


			void ImportMesh(Mesh& mesh, std::string FileName);
			void ImportAnimations(std::vector<Animation*>&, tinyxml2::XMLElement*);

			static Importer* GetInstance(){
				return m_pInstance;
			}

			Renderer* GetRenderer() const;
			Texture LoadTexture(std::string path, int KeyCode);
			Texture LoadTexture(XMLNode& kTextureNode, const char* textureName);

		private:
			TileMap* LoadTileMap(XMLNode& kTileMapNode);
			Tile* CreateTile(XMLNode& kTileSetNode, Texture pkTexture, unsigned int iId, int textWidth, int textHeight);
			int ColorConverter(int);
			std::string m_sCurrentModelPath;
			static Importer* m_pInstance;
				   Renderer* m_pRenderer;
				   std::map<std::string, Texture> m_mTextureMap;
				   std::map<std::string , TileMap*> m_mTilemaps;
	};
}