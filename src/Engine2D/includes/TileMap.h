#ifndef TILEMAP_H
#define TILEMAP_H
#include "Defines.h"
#include "Renderer.h"
#include "Tile.h"
#include <map>
#include <vector>

namespace Engine{

class ENGINE_API TileMap{
private:
	unsigned int m_uiCols;
	unsigned int m_uiRows;
	float m_fPosX, m_fPosY;
	std::string s_name;

public:
	TileMap(std::string name);
	~TileMap();

	void Draw(Renderer* pRenderer);
	void AddTile(std::string name, Tile* p_tile);
	Tile* GetTile(std::string name);
	bool TileExists(std::string name);
	void AddLayer(std::string name, std::vector<std::vector<int>> layer);
	
	void SetMapScale(float width, float height);
	void SetTileScale(float width, float height);
	void SetMapPosition(float x, float y);
	void SetColsRows(unsigned int cols, unsigned int rows);

	std::string GetName();
	void GetColsRows(int pos, int cols, int* col, int* rows);

	std::map<std::string, Tile*>::iterator m_TilesIt;
	std::map<std::string, Tile*> m_Tiles;
	
	std::map<std::string,std::vector<std::vector<int>>> m_LayerInfo;
	std::map<std::string,std::vector<std::vector<int>>>::iterator m_LayerInfoIter;
	void AddTile();
};

}
#endif