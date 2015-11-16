#include "Importer.h"
#include "Scene.h"
#include "Mesh.h"
#include "animation.h"
#include "Renderer.h"
#include "Node.h"

// ----------------- Assimp ----------------- //
#include "assimp\include\Importer.hpp"
#include "assimp\include\scene.h"
#include "assimp\include\postprocess.h"
// ------------------------------------------ //

#include <iostream>

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
// Sprites --- Not in use
void Importer::ImportAnimations(std::vector<Animation*>& list, tinyxml2::XMLElement* animations){
	while (animations != NULL){
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

int Importer::ColorConverter(int hexValue) {
  int r = ((hexValue >> 16) & 0xFF) / 255.0;  // Extract the RR byte
  int g = ((hexValue >> 8) & 0xFF) / 255.0;   // Extract the GG byte
  int b = ((hexValue) & 0xFF) / 255.0;        // Extract the BB byte
  return engine_COLOR_RGB(r,g,b);
}


bool Importer::ImportScene(const std::string& fileName, Node& SceneRoot){
	Assimp::Importer kImporter;

	const aiScene* AiScene = kImporter.ReadFile(fileName,
												aiPrimitiveType_LINE | aiPrimitiveType_POINT |
												aiProcess_Triangulate | aiProcess_SortByPType | aiProcess_ConvertToLeftHanded);

	if (AiScene){
		SceneRoot.SetName(AiScene->mRootNode->mName.C_Str());
		m_sCurrentModelPath = fileName;
		ImportNode(SceneRoot, AiScene->mRootNode, AiScene);
		return true;
	}

	return false;
}



bool Importer::ImportNode(Node& kNode, aiNode* AiNode, const aiScene* AiScene){
	kNode.SetName(AiNode->mName.C_Str());

	aiMatrix4x4 mx = AiNode->mTransformation.Transpose();
	kNode.SetTransformationFromAssimp(mx.a1, mx.a2, mx.a3, mx.a4,
										mx.b1, mx.b2, mx.b3, mx.b4,
										mx.c1, mx.c2, mx.c3, mx.c4,
										mx.d1, mx.d2, mx.d3, mx.d4);

	for (unsigned int i = 0; i < AiNode->mNumChildren; i++){
		Node* pkNode = new Node();
		pkNode->SetName(AiNode->mChildren[i]->mName.C_Str());

		ImportNode(*pkNode, AiNode->mChildren[i], AiScene);
		kNode.AddChild(pkNode);
	}

	for (unsigned int i = 0; i < AiNode->mNumMeshes; i++){
		Mesh* pkMesh = new Mesh(*m_pRenderer, true);
		kNode.AddMesh(pkMesh);

		aiMesh* pkAiMesh = AiScene->mMeshes[AiNode->mMeshes[i]];
		aiMaterial* pkAiMaterial = AiScene->mMaterials[pkAiMesh->mMaterialIndex];

		ImportMesh(pkAiMesh, pkAiMaterial, *pkMesh);
	}
	
	return true;
}



bool Importer::ImportMesh(const aiMesh* pkAiMesh, const aiMaterial* pkAiMaterial, Mesh& kMesh){
	kMesh.SetName(pkAiMesh->mName.C_Str());

	MeshVertex* pVertices = new MeshVertex[pkAiMesh->mNumVertices];
	for (unsigned int i = 0; i<pkAiMesh->mNumVertices; i++){
		pVertices[i].x = pkAiMesh->mVertices[i].x;
		pVertices[i].y = pkAiMesh->mVertices[i].y;
		pVertices[i].z = pkAiMesh->mVertices[i].z;
		if (pkAiMesh->mTextureCoords[0] != NULL) {
			pVertices[i].u = pkAiMesh->mTextureCoords[0][i].x;
			pVertices[i].v = pkAiMesh->mTextureCoords[0][i].y;
		}


		if (pkAiMesh->HasNormals()){
			pVertices[i].nx = pkAiMesh->mNormals[i].x;
			pVertices[i].ny = pkAiMesh->mNormals[i].y;
			pVertices[i].nz = pkAiMesh->mNormals[i].z;
		}
	}
	size_t uiIndexCount = pkAiMesh->mNumFaces * 3;
	unsigned short* pausIndices = new unsigned short[uiIndexCount];
	for (unsigned int i = 0; i<pkAiMesh->mNumFaces; i++){
		pausIndices[i * 3 + 0] = pkAiMesh->mFaces[i].mIndices[0];
		pausIndices[i * 3 + 1] = pkAiMesh->mFaces[i].mIndices[1];
		pausIndices[i * 3 + 2] = pkAiMesh->mFaces[i].mIndices[2];
	}
	kMesh.SetData(pVertices, pkAiMesh->mNumVertices, engine::Primitive::TriangleList, pausIndices, uiIndexCount);
	kMesh.SetName(pkAiMesh->mName.C_Str());

	if (pkAiMaterial){
		size_t found = m_sCurrentModelPath.find_last_of("/\\");
		std::string texPath = m_sCurrentModelPath.substr(0, found + 1);
		aiString aipath;
		pkAiMaterial->Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), aipath);
		texPath.append(aipath.C_Str());

		Texture TheTexture = GetRenderer()->LoadTexture(texPath);
		kMesh.SetTexture(TheTexture);
	}

	return true;
}