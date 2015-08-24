#include "Importer.h"
#include "Scene.h"
#include "Mesh.h"
#include "animation.h"
#include "Renderer.h"

using namespace engine;

Importer* Importer::m_oInstance = NULL;

Importer::Importer() : m_oRenderer(NULL){

}


bool Importer::Init(Renderer& r){
	m_oRenderer = &r;
	m_oInstance = this;	// Seteo mi singleton a this!
	return true;
}


Renderer* Importer::GetRenderer() const {
	return m_oRenderer;
}


bool Importer::importScene(Scene& mScene, std::string fileName){
	tinyxml2::XMLDocument xmlDoc;
	xmlDoc.LoadFile(fileName.c_str());
	if (xmlDoc.Error())
		return false;

	tinyxml2::XMLElement* root = xmlDoc.FirstChildElement("SCENE");

	//ImportMesh(mScene, root);
	return true;
}



void Importer::ImportMesh(Scene& mScene, tinyxml2::XMLElement* root){
	tinyxml2::XMLElement *mesh = root->FirstChildElement("MESH");
	tinyxml2::XMLElement *instance = root->FirstChildElement("INSTANCE");

	while (mesh != NULL){
		std::string meshName = mesh->Attribute("name");
		int vertexCount = mesh->IntAttribute("vertices");
		//std::string texturePath = mesh->Attribute("texture");
		

		//engine::Texture texture = loadTexture(texturePath, engine_COLOR_RGB(r, g, b));

		instance = root->FirstChildElement("INSTANCE");
		while (instance != NULL){

			if (instance->Attribute("mesh") == meshName){
				std::string sName = instance->Attribute("name");
				float posX = instance->FloatAttribute("posX");
				float posY = instance->FloatAttribute("posY");
				float posZ = instance->FloatAttribute("posZ");
				float rotation = instance->FloatAttribute("rotation");
				float scaleX = instance->FloatAttribute("scaleX");
				float scaleY = instance->FloatAttribute("scaleY");
				float scaleZ = instance->FloatAttribute("scaleZ");
				std::string colGroup = instance->Attribute("layer");

				
				tinyxml2::XMLElement *xmlVertex = mesh->FirstChildElement("VERTEX");
				std::vector<ColorVertex> m_akVertices;
				while (xmlVertex != NULL){
					ColorVertex vertex;
					vertex.x = xmlVertex->FloatAttribute("posX");
					vertex.y = xmlVertex->FloatAttribute("posY");
					vertex.z = xmlVertex->FloatAttribute("posZ");
					vertex.color = engine_COLOR_ARGB(xmlVertex->IntAttribute("r"),
													xmlVertex->IntAttribute("g"),
													xmlVertex->IntAttribute("b"),
													xmlVertex->IntAttribute("a"));
					
					m_akVertices.push_back(vertex);
					xmlVertex = xmlVertex->NextSiblingElement("VERTEX");
				}

				//----------------------//
				tinyxml2::XMLElement *xmlTriangle = mesh->FirstChildElement("TRIANGLE");
				std::vector<Triangle> m_akTriangles;
				while (xmlTriangle != NULL){
					Triangle triangle;
					triangle.a = xmlVertex->IntAttribute("a");
					triangle.b = xmlVertex->IntAttribute("b");
					triangle.c = xmlVertex->IntAttribute("c");

					m_akTriangles.push_back(triangle);
					xmlTriangle = xmlTriangle->NextSiblingElement("TRIANGLE");
				}
				//----------------------//

				Mesh* entity = new Mesh(*m_oRenderer, m_akVertices);

				entity->SetPos(posX, posY, posZ);
				entity->SetName(sName);
				entity->SetRotation(rotation);
				entity->SetScale(scaleX, scaleY, scaleZ);
				//entity->setTexture(texture);
				entity->SetCollisionGroup(colGroup);

				mScene.Add(sName, entity);
				mScene.AddClsGroup(colGroup);
				mScene.AddEntityToClsGroup(entity, colGroup);
			}

			instance = instance->NextSiblingElement("INSTANCE");
		}
		mesh = mesh->NextSiblingElement("MESH");
	}

}


void Importer::ImportAnimations(std::vector<Animation*>& list, tinyxml2::XMLElement* animations){
	while (animations != NULL)
	{
		//CREATE ANIMATION AUX
		Animation *anim = new Animation();

		std::string name = animations->Attribute("name");
		float lenght = animations->FloatAttribute("length");
		float t_width = animations->FloatAttribute("width");
		float t_height = animations->FloatAttribute("height");

		anim->setName(name);
		anim->setLength(lenght);

		tinyxml2::XMLElement *frame = animations->FirstChildElement("FRAME");
		while (frame != NULL){

			float posX = frame->FloatAttribute("posX");
			float posY = frame->FloatAttribute("posY");
			float width = frame->FloatAttribute("width");
			float height = frame->FloatAttribute("height");

			//ADDFRAME (t_width, t_height, posX, posY, width, height);
			anim->addFrame(t_width, t_height, posX, posY, width, height);

			frame = frame->NextSiblingElement("FRAME");
		}
		// PUSH_BACK ANIMATION
		list.push_back(anim);

		animations = animations->NextSiblingElement("ANIMATION");
	}
}

Texture Importer::LoadTexture(std::string path, int KeyCode){

	if (!m_mTextureMap.count(path)){
		Texture t = m_oRenderer->LoadTexture(path, KeyCode);
		m_mTextureMap[path] = t;
		return t;
	}

	return m_mTextureMap[path];
}

//--------------------------------------------------------------------------------

Texture Importer::LoadTexture(XMLNode& kTextureNode, const char* textureName){
        // se fija si existe, si existe lo retorna, si no lo crea.
        if (m_mTextureMap.count(textureName)){
                return m_mTextureMap[textureName];
        }
        
		//toma al path a la imagen en si.
        std::string sFilePath = kTextureNode.getAttribute("FilePath");

		int keycode = 0;
		if(kTextureNode.isAttributeSet("trans") != 0)
			keycode = ColorConverter(atoi(kTextureNode.getAttribute("trans")));

		Texture text = m_oRenderer->LoadTexture(sFilePath, keycode);
		m_mTextureMap[textureName] = text;
        return text;
}


int Importer::ColorConverter(int hexValue) {
  int r = ((hexValue >> 16) & 0xFF) / 255.0;  // Extract the RR byte
  int g = ((hexValue >> 8) & 0xFF) / 255.0;   // Extract the GG byte
  int b = ((hexValue) & 0xFF) / 255.0;        // Extract the BB byte
  return engine_COLOR_RGB(r,g,b);
}