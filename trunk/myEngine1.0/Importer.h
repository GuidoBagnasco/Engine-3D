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

			bool ImportNode(Node&, aiNode*, const aiScene*);
			bool ImportMesh(const aiMesh*, const aiMaterial*, Mesh&);
			bool ImportScene(const std::string&, Node&);

			void ImportAnimations(std::vector<Animation*>&, tinyxml2::XMLElement*);		// Sprites --- Not in use

			static Importer* GetInstance(){
				return m_pInstance;
			}

			Renderer* GetRenderer() const;
			Texture LoadTexture(std::string path, int KeyCode);

		private:
			int ColorConverter(int);
			std::string m_sCurrentModelPath;
			static Importer* m_pInstance;
				   Renderer* m_pRenderer;
				   std::map<std::string, Texture> m_mTextureMap;
	};
}