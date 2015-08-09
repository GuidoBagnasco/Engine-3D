#include "TileMap.h"
#include <string>
using namespace Engine;
#pragma Warning(disable:4996)

TileMap::TileMap(std::string name) :
s_name(name)
{

}



TileMap::~TileMap(){
	m_LayerInfo.clear();
	for(m_TilesIt = m_Tiles.begin(); m_TilesIt != m_Tiles.end(); m_TilesIt++){
		delete m_TilesIt->second;
	}
}

//-----------------------------------------------------------------

void TileMap::Draw(Renderer* pRenderer){
	char f_sTileName[255];
	m_LayerInfoIter = m_LayerInfo.begin();

	do{
		for(int i = 0 ; i <  m_LayerInfoIter->second.size(); i++){
			for (int j = 0; j < m_LayerInfoIter->second[i].size(); j++){
				if (m_LayerInfoIter->second[i][j] != 0){
					itoa(m_LayerInfoIter->second[i][j], f_sTileName, 10);
					GetTile(f_sTileName)->SetPosition((j * GetTile(f_sTileName)->GetScaleX())+ m_fPosX, (-i * GetTile(f_sTileName)->GetScaleY()) + m_fPosY);
					GetTile(f_sTileName)->Draw(pRenderer);
				}
			}
		}

		m_LayerInfoIter++;

	}while(m_LayerInfoIter != m_LayerInfo.end());
}



void TileMap::AddLayer(std::string name,std::vector<std::vector<int>> layer){	
	m_LayerInfoIter = m_LayerInfo.find(name);

	if (m_LayerInfoIter != m_LayerInfo.end())
		return;

	m_LayerInfo[name] = layer;
}



void TileMap::AddTile(std::string name, Tile* p_Tile){	
	m_TilesIt = m_Tiles.find(name);

	if(m_TilesIt != m_Tiles.end())
		return;

	m_Tiles[name] = p_Tile;
}



Tile* TileMap::GetTile(std::string name){	
	m_TilesIt = m_Tiles.find(name);

	if (m_TilesIt == m_Tiles.end())
		return NULL;

	return m_Tiles[name];
}



bool TileMap::TileExists(std::string name){	
	m_TilesIt = m_Tiles.find(name);

	if (m_TilesIt == m_Tiles.end())
		return false;

	return true;
}



void TileMap::SetMapScale(float p_fWidth, float p_fHeight){
	char f_sTileName [255];
	m_LayerInfoIter = m_LayerInfo.begin();

	do{
		for(int i = 0; i < m_LayerInfoIter->second.size()-1; i++){
			for (int j = 0; j < m_LayerInfoIter->second[i].size(); j++){
				if (m_LayerInfoIter->second[i][j] != 0){
					itoa(m_LayerInfoIter->second[i][j], f_sTileName, 10);
					GetTile(f_sTileName)->SetScale((p_fWidth/m_uiCols), (p_fHeight/m_uiRows));
				}
			}
		}

		m_LayerInfoIter++;

	}while(m_LayerInfoIter != m_LayerInfo.end());
}



void TileMap::SetTileScale(float p_fWidth, float p_fHeight){
	char f_sTileName [255];
	m_LayerInfoIter = m_LayerInfo.begin();

	do{
		for(int i = 0; i < m_LayerInfoIter->second.size()-1; i++){
			for (int j = 0; j < m_LayerInfoIter->second[i].size(); j++){
				if (m_LayerInfoIter->second[i][j] != 0){
					itoa(m_LayerInfoIter->second[i][j], f_sTileName, 10);
					GetTile(f_sTileName)->SetScale(p_fWidth,p_fHeight);
				}
			}
		}

		m_LayerInfoIter++;

	}while(m_LayerInfoIter!=m_LayerInfo.end());
}



void TileMap::SetMapPosition(float x, float y){
	m_fPosX = x;
	m_fPosY = y;
}



void TileMap::SetColsRows(unsigned int cols, unsigned int rows){
	m_uiCols = cols;
	m_uiRows = rows;
}



std::string TileMap::GetName(){
	return s_name;
}



void TileMap::GetColsRows(int Pos, int Cols, int *Col, int* Row){
	int AuxCol = 0;
	int AuxRow = 0;

	while (Pos >= Cols){
		Pos -= Cols;
		AuxRow++;
	}

	AuxCol = Pos;

	*Col = AuxCol;
	*Row = AuxRow;
}