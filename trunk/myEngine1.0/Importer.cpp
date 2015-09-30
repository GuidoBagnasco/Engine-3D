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
	const aiScene* scene = importer.ReadFile(fileName,
		aiProcess_CalcTangentSpace | aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);
	
	if(!scene)
		return;

	//mesh = new Mesh(&m_pRenderer->GetRenderer());

	int nIndices;
	unsigned short *pIndices;

	if(scene->mMeshes[0]){
		aiMesh * p_AIMesh = scene->mMeshes[0];
		if(p_AIMesh->HasFaces()){
			aiFace* pAIFaces;
			pAIFaces = p_AIMesh->mFaces;
			nIndices = p_AIMesh->mNumFaces * 3;
			pIndices = new unsigned short[nIndices];
			for(DWORD i = 0; i < p_AIMesh->mNumFaces; i++){
				if(pAIFaces[i].mNumIndices != 3){
					delete[] pIndices;
					return;
				}

				for(DWORD j = 0; j < 3; j++){
					pIndices[i * 3 + j] = pAIFaces[i].mIndices[j];
				}
			}
		}

		if(p_AIMesh->HasPositions()){
			int nVertices;
			MeshVertex * pVertices;
			nVertices = p_AIMesh->mNumVertices;
			pVertices = new MeshVertex[nVertices];

			for(DWORD i = 0; i < nVertices; i++){
				pVertices[i].x = p_AIMesh->mVertices[i].x;
				pVertices[i].y = p_AIMesh->mVertices[i].y;
				pVertices[i].z = p_AIMesh->mVertices[i].z;
			}

			if(p_AIMesh->HasNormals()){
				for(DWORD i = 0; i < nVertices; i++){
					pVertices[i].nx = p_AIMesh->mNormals[i].x;
					pVertices[i].ny = p_AIMesh->mNormals[i].y;
					pVertices[i].nz = p_AIMesh->mNormals[i].z;
				}
			}

			if(p_AIMesh->HasTextureCoords(0)){
				for(DWORD i = 0; i < nVertices; i++){
					pVertices[i].u = p_AIMesh->mTextureCoords[0][i].x;
					pVertices[i].v = p_AIMesh->mTextureCoords[0][i].y;
				}
			}

			mesh.SetData(pVertices, nVertices, Primitive::TriangleList, pIndices, nIndices);
			mesh.SetName(p_AIMesh->mName.C_Str());
		}
	}

	return;
}

//--------------------------------------------------------------------------------//

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


bool Importer::importScene(const std::string& fileName, Node& SceneRoot){

	Assimp::Importer kImporter;

	const aiScene* AiScene = kImporter.ReadFile(fileName,
		aiPrimitiveType_LINE | aiPrimitiveType_POINT |
		aiProcess_Triangulate | aiProcess_SortByPType | aiProcess_ConvertToLeftHanded);

	if (AiScene){
		SceneRoot.SetName(AiScene->mRootNode->mName.C_Str());
		m_sCurrentModelPath = fileName;
		importNode(SceneRoot, AiScene->mRootNode, AiScene);
		return true;
	}

	return false;
}
#include <iostream>
bool Importer::importNode(Node& kNode, aiNode* AiNode, const aiScene* AiScene){

	kNode.SetName(AiNode->mName.C_Str());

	aiMatrix4x4 m = AiNode->mTransformation.Transpose();
	kNode.SetFirstTransformationFromAssimp(m.a1, m.a2, m.a3, m.a4,
		m.b1, m.b2, m.b3, m.b4,
		m.c1, m.c2, m.c3, m.c4,
		m.d1, m.d2, m.d3, m.d4);

	/*
	aiVector3D * s;
	aiQuaternion * q;
	aiVector3D * p;

	m.Decompose(*s, *q, *p);

	D3DXVECTOR3 dxS = D3DXVECTOR3(s->x, s->y, s->z);
	D3DXQUATERNION dxQ = D3DXQUATERNION(q->x, q->y, q->z, q->w);
	D3DXVECTOR3 dxP = D3DXVECTOR3(p->x, p->y, p->z);

	kNode.SetDiscomposedTransformationFromAssimp(dxS,dxQ,dxP);
	*/

	for (unsigned int i = 0; i<AiNode->mNumChildren; i++){
		Node* pkNode = new Node();
		pkNode->SetName(AiNode->mChildren[i]->mName.C_Str());

		//pkNode->SetPos(AiNode->mChildren[i]->mTransformation)
		//std::cout << pkNode->GetName() << std::endl;
		importNode(*pkNode, AiNode->mChildren[i], AiScene);
		kNode.AddChild(pkNode);
		std::cout << pkNode->GetName() << " is child of " << kNode.GetName() << std::endl;
	}

	for (unsigned int i = 0; i<AiNode->mNumMeshes; i++){
		Mesh* pkMesh = new Mesh(*m_pRenderer, true);
		kNode.AddMesh(pkMesh);

		aiMesh* pkAiMesh = AiScene->mMeshes[AiNode->mMeshes[i]];
		aiMaterial* pkAiMaterial = AiScene->mMaterials[pkAiMesh->mMaterialIndex];

		importMesh(pkAiMesh, pkAiMaterial, *pkMesh);
	}
	//std::cout << std::endl << std::endl;
	return true;
}

bool Importer::importMesh(const aiMesh* pkAiMesh, const aiMaterial* pkAiMaterial, Mesh& kMesh){

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