#include "Importer.h"
#include "Scene.h"
#include "Mesh.h"
#include "animation.h"
#include "Renderer.h"

// ----------------- Assimp ----------------- //
#include "assimp\include\Importer.hpp"
#include "assimp\include\scene.h"
#include "assimp\include\postprocess.h"
// ------------------------------------------ //

using namespace engine;


Importer* Importer::m_pInstance = NULL;

Importer::Importer() : m_pRenderer(NULL){

}

//--------------------------------------------------------------------------------//

bool Importer::Init(Renderer& r){
	m_pRenderer = &r;
	m_pInstance = this;	// Seteo mi singleton a this!
	return true;
}

//--------------------------------------------------------------------------------//

Renderer* Importer::GetRenderer() const {
	return m_pRenderer;
}

//--------------------------------------------------------------------------------//

bool Importer::ImportScene(Scene& mScene, std::string fileName){
	tinyxml2::XMLDocument xmlDoc;
	xmlDoc.LoadFile(fileName.c_str());
	if (xmlDoc.Error())
		return false;

	tinyxml2::XMLElement* root = xmlDoc.FirstChildElement("SCENE");

	//ImportMesh(mScene, root);
	return true;
}

//--------------------------------------------------------------------------------//

void Importer::ImportMesh(Mesh& mesh, std::string fileName){
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(fileName, aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);
	
	if(!scene)
		return;

	//mesh = new Mesh(GetRenderer());

	int nIndices;
	unsigned short *pIndices;

	if(scene->mMeshes[0]){
		aiMesh * pAIMesh = scene->mMeshes[0];
		if (pAIMesh->HasFaces()){
			aiFace* pAIFaces;
			pAIFaces = pAIMesh->mFaces;
			nIndices = pAIMesh->mNumFaces * 3;
			pIndices = new unsigned short[nIndices];
			for(DWORD i = 0; i < pAIMesh->mNumFaces; i++){
				if(pAIFaces[i].mNumIndices != 3){
					delete[] pIndices;
					return;
				}
				for(DWORD j = 0; j < 3; j++){
					pIndices[i * 3 + j] = pAIFaces[i].mIndices[j];
				}
			}
		}

		if (pAIMesh->HasPositions()){
			int nVertices;
			MeshVertex * pVertices;
			nVertices = pAIMesh->mNumVertices;
			pVertices = new MeshVertex[nVertices];

			for(DWORD i = 0; i < nVertices; i++){
				pVertices[i].x = pAIMesh->mVertices[i].x;
				pVertices[i].y = pAIMesh->mVertices[i].y;
				pVertices[i].z = pAIMesh->mVertices[i].z;
			}

			if(pAIMesh->HasNormals()){
				for(DWORD i = 0; i < nVertices; i++){
					pVertices[i].nx = pAIMesh->mNormals[i].x;
					pVertices[i].ny = pAIMesh->mNormals[i].y;
					pVertices[i].nz = pAIMesh->mNormals[i].z;
				}
			}

			if(pAIMesh->HasTextureCoords(0)){
				for(DWORD i = 0; i < nVertices; i++){
					pVertices[i].u = pAIMesh->mTextureCoords[0][i].x;
					pVertices[i].v = pAIMesh->mTextureCoords[0][i].y;
				}
			}

			mesh.SetData(pVertices, nVertices, Primitive::TriangleList, pIndices, nIndices);
			mesh.SetName(pAIMesh->mName.C_Str());
		}
	}

	return;
}

//--------------------------------------------------------------------------------//

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

//--------------------------------------------------------------------------------//

Texture Importer::LoadTexture(std::string path, int KeyCode){

	if (!m_mTextureMap.count(path)){
		Texture t = m_pRenderer->LoadTexture(path, KeyCode);
		m_mTextureMap[path] = t;
		return t;
	}

	return m_mTextureMap[path];
}

//--------------------------------------------------------------------------------//

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

		Texture text = m_pRenderer->LoadTexture(sFilePath, keycode);
		m_mTextureMap[textureName] = text;
        return text;
}

//--------------------------------------------------------------------------------//

int Importer::ColorConverter(int hexValue) {
  int r = ((hexValue >> 16) & 0xFF) / 255.0;  // Extract the RR byte
  int g = ((hexValue >> 8) & 0xFF) / 255.0;   // Extract the GG byte
  int b = ((hexValue) & 0xFF) / 255.0;        // Extract the BB byte
  return engine_COLOR_RGB(r,g,b);
}
