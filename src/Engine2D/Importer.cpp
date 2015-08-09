#include "Defines.h"
#include "Importer.h"
#include "Sprite.h"
#include "Texture.h"
#include "Renderer.h"
#include "Tile.h"
#include "TileMap.h"
#include "Game.h"
#include "Box.h"
using namespace Engine;


Importer::Importer(Renderer* renderer){
	pk_Renderer = renderer;
}

void Importer::LoadAnimation(std::vector<Animation>** list_animations, tinyxml2::XMLElement* animations){
	while(animations != NULL){
		Animation* anim = new Animation();
		std::string name = animations->Attribute("Name");
		float length = animations->FloatAttribute("Length");
		float t_width = animations->FloatAttribute("Width");
		float t_height = animations->FloatAttribute("Height");

		anim->SetName(name);
		anim->SetLength(length);

		tinyxml2::XMLElement *frame = animations->FirstChildElement("FRAME");
		while(frame != NULL){
			float posX		= frame->FloatAttribute("POS_X");
			float posY		= frame->FloatAttribute("POS_Y");
			float width		= frame->FloatAttribute("Width");
			float height	= frame->FloatAttribute("Height");

			anim->AddFrame(t_width, t_height, posX, posY, width, height);

			frame = frame -> NextSiblingElement("FRAME");
		}
		(*list_animations)->push_back(*anim);
		animations = animations -> NextSiblingElement("ANIMATION");
	}
}

void Importer::ImportSprite(Scene& pkScene, tinyxml2::XMLElement* element){
	tinyxml2::XMLElement *sprite = element->FirstChildElement("SPRITE");
	tinyxml2::XMLElement *instance = element->FirstChildElement("INSTANCE");

	while(sprite != NULL){
		std::string nameSprite = sprite->Attribute("Name");
		std::string texturePath = sprite->Attribute("Sheet");
		int r = sprite->IntAttribute("R");
		int g = sprite->IntAttribute("G");
		int b = sprite->IntAttribute("B");
		LoadTexture(texturePath, Engine_COLOR_RGB(r,g,b));

		Texture* pk_texture = m_sTex[texturePath].get();

		std::vector<Animation>* list_animations = new std::vector<Animation>();
		LoadAnimation(&list_animations,sprite->FirstChildElement("ANIMATION"));

		tinyxml2::XMLElement* instance = element->FirstChildElement("INSTANCE");

		while(instance != NULL){
			if(instance->Attribute("Sprite") == nameSprite){
				Sprite* ent_sprite = new Sprite();
				std::string name = instance->Attribute("Name");
				float posX = instance->FloatAttribute("POS_X");
				float posY = instance->FloatAttribute("POS_Y");
				float rotation = instance->FloatAttribute("ROTATION");
				float scaleX = instance->FloatAttribute("SCALE_X");
				float scaleY = instance->FloatAttribute("SCALE_Y");
				std::string layer = instance->Attribute("LAYER");
                                                 
				ent_sprite->SetPosition(posX, posY);
				ent_sprite->SetName(name);
				ent_sprite->SetRotation(rotation);
				ent_sprite->SetScale(scaleX, scaleY);
				ent_sprite->SetTexture(m_sTex[texturePath]);
				ent_sprite->SetCollisionsGroup(layer);
		
				ent_sprite->AddAnimation(*list_animations);
				pkScene.Add(name, ent_sprite);
				pkScene.AddCollidersGroup(layer);
				pkScene.AddEntityToCollidersGroup(ent_sprite, layer);
			}
			instance = instance->NextSiblingElement("INSTANCE");
		}
		sprite = sprite->NextSiblingElement("SPRITE");
	}
}



void Importer::ImportQuad(Scene& pkScene,tinyxml2::XMLElement* element){
	tinyxml2::XMLElement *quad = element->FirstChildElement("QUAD");

	while(quad != NULL){
		Box* ent_quad = new Box();

		std::string name = quad->Attribute("Name");
		float posX = quad->FloatAttribute("POS_X");
		float posY = quad->FloatAttribute("POS_Y");
		float rotation = quad->FloatAttribute("ROTATION");
		float scaleX = quad->FloatAttribute("SCALE_X");
		float scaleY = quad->FloatAttribute("SCALE_Y");
		int r = quad->IntAttribute("R");
		int g = quad->IntAttribute("G");
		int b = quad->IntAttribute("B");
		std::string layer = quad->Attribute("LAYER");

		ent_quad->SetName(name);
		ent_quad->SetPosition(posX, posY);
		ent_quad->SetRotation(rotation);
		ent_quad->SetScale(scaleX, scaleY);
		ent_quad->SetColor(Engine_COLOR_RGB(r,g,b));

		pkScene.Add(name, ent_quad);

		quad = quad->NextSiblingElement("QUAD");
	}
}



spriteUVInfo Importer::SetUV(tinyxml2::XMLElement* element){
	
	float t_width, t_height, posX, posY, width, height = 0;

	while(element != NULL){
		t_width		= element->FloatAttribute("Width");
		t_height	= element->FloatAttribute("Height");

		tinyxml2::XMLElement *frame = element->FirstChildElement("FRAME");
		while(frame != NULL){
			posX		= frame->FloatAttribute("POS_X");
			posY		= frame->FloatAttribute("POS_Y");
			width		= frame->FloatAttribute("Width");
			height		= frame->FloatAttribute("Height");	

			frame = frame->NextSiblingElement("FRAME");
		}

		element = element->NextSiblingElement("ANIMATION");
	}

	spriteUVInfo info;

	info.U1 = (posX / t_width);
	info.V1 = (posY / t_height);
	
	info.U2 = ((posX + width) / t_width);
	info.V2 = (posY / t_height);

	info.U3 = (posX / t_width);
	info.V3 = ((posY + height) / t_height);

	info.U4 = ((posX + width) / t_width);
	info.V4 = ((posY + height)/ t_height);
	

	return info;
}



bool Importer::Load(std::string fileName, Scene& scene){
	doc.LoadFile(fileName.c_str());

	if(doc.Error())
		return false;

	tinyxml2::XMLElement *element = doc.FirstChildElement("SHEET");
	ImportQuad(scene, element);
	ImportSprite(scene, element);
	ImportTileMap(scene, element);
	return true;
}



Texture* Importer::LoadTexture(std::string fileName, int keycode){
	
	/*boost::shared_ptr<Texture> pk_Texture;

	std::map<std::string, boost::shared_ptr<Texture>>::iterator iter = m_sTex.find(fileName);
	if (iter != m_sTex.end()){
		return NULL;
	}
	pk_Texture = boost::shared_ptr<Texture>(pk_Renderer->LoadTexture(fileName, keycode));
	m_sTex[fileName] = pk_Texture;
	return m_sTex[fileName].get();
	*/

	if(m_sTex.count(fileName)){
		return m_sTex[fileName].get();
	}

	m_sTex[fileName] = boost::shared_ptr<Texture>(pk_Renderer->LoadTexture(fileName, keycode));
	return m_sTex[fileName].get();
}



void Importer::ImportTileMap(Scene& mScene, tinyxml2::XMLElement* root){
	tinyxml2::XMLElement *map = root->FirstChildElement("TILEMAP");
	while(map != NULL){
		// data
		int width;
		int height;
		int tilewidth;
		int tileheight;

		int textWidth;
		int textHeight;

		int tilesX;
		int tilesY;
		int spacing = 2;
		int margin;
		XMLNode TileData;

		std::string f_TextureName;
		std::string f_TexturePath;
		// data

		std::string mapName = map->Attribute("name");
		std::string path = map->Attribute("path");

		TileMap * f_tmMap = new TileMap(mapName);	//MapName
		XMLNode f_XMLMapNode = XMLNode::openFileHelper(path.c_str(), "map");

		width = atoi(f_XMLMapNode.getAttribute("width"));
		height = atoi(f_XMLMapNode.getAttribute("height"));
		tilewidth = atoi(f_XMLMapNode.getAttribute("tilewidth"));
		tileheight = atoi(f_XMLMapNode.getAttribute("tileheight"));
		
		TileData = f_XMLMapNode.getChildNode("tileset");
		margin = atoi(TileData.getAttribute("margin"));
		tilesX = atoi(TileData.getAttribute("tilesX"));
		tilesY = atoi(TileData.getAttribute("tilesY"));
		TileData = TileData.getChildNode("image");
		f_TexturePath = TileData.getAttribute("source");
		f_TextureName = TileData.getAttribute("source");

		textWidth = atoi(TileData.getAttribute("width"));
		textHeight = atoi(TileData.getAttribute("height"));
		//textWidth = 512;
		//textHeight = 512;
		Texture* texture = LoadTexture(f_TexturePath, Engine_COLOR_RGB( atoi( TileData.getAttribute("r") ), atoi( TileData.getAttribute("g") ), atoi( TileData.getAttribute("b") ) ) );
		int CountLayers = f_XMLMapNode.nChildNode("layer");	// layers

		for(int l = 0; l<CountLayers; l++) {
			std::string LayerName;
			std::vector<std::vector<int>> Layer;
			XMLNode Data = f_XMLMapNode.getChildNode("layer", l);
			LayerName = Data.getAttribute("name");
			Data = Data.getChildNode("data");

			for(int i = 0, t = 0; i<height; i++) {
				std::vector<int> fila;
				for(int j = 0; j<width; j++, t++) {
					XMLNode tile = Data.getChildNode("tile", t);
					fila.push_back(atoi(tile.getAttribute("gid")));
					if(f_tmMap->TileExists(tile.getAttribute("gid")) == false) {
						int col, row;
						f_tmMap->GetColsRows(atoi(tile.getAttribute("gid")) - 1, tilesX, &col, &row);
						Tile * newTile = new Tile();
						newTile->SetName(tile.getAttribute("gid"));
						newTile->SetTexture(*texture);
						newTile->SetSpriteArea((col*tilewidth) + margin + spacing, (row*tileheight) + margin + spacing, tilewidth - 2 * spacing, tileheight - 2 * spacing, textWidth, textHeight);
						newTile->SetScale(tilewidth, tileheight);
						f_tmMap->AddTile(newTile->GetName(), newTile);
					}
				}
				Layer.push_back(fila);
			}
			f_tmMap->AddLayer(LayerName, Layer);
			f_tmMap->SetColsRows(width, height);
			f_tmMap->SetTileScale(tilewidth, tileheight);
			
			//f_tmMap->SetMapScale(800, 800);
			//f_tmMap->SetMapPosition(-350, 350);
		}
		mScene.AddTileMap(f_tmMap->GetName(), f_tmMap);
		map = map->NextSiblingElement("TILEMAP");
	}

}


Importer::~Importer(){

}