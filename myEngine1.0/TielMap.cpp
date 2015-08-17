#include "TileMap.h"
#include "Tile.h"
#include "Renderer.h"
#include <string>
using namespace engine;
TileMap::TileMap(std::string sName) :
m_sName(sName),
m_fPositionX(0),
m_fPositionY(0),
m_uiCols(0),
m_uiRows(0),
m_fTileHeight(1),
m_fTileWidth(1)
{
        SetPosition(0,0);
}
//-----------------------------------------------------------------
void TileMap::SetColRows(unsigned int uiCols, unsigned int uiRows)
{
        m_uiCols = uiCols;
        m_uiRows = uiRows;
}
//-----------------------------------------------------------------
void TileMap::Draw(Renderer* pkRenderer)
{
        for(int i =0; i < m_vLayers.size(); i++)
        {
                for (int j = 0; j < m_vLayers[i].size(); j++)
                {
                        if(m_vLayers[i][j] != NULL)
                        m_vLayers[i][j]->Draw(pkRenderer);
                }
        }
}
//-----------------------------------------------------------------
void TileMap::SetPosition(const float& x, const float& y)
{
	m_fPositionX = x;
	m_fPositionY = y;
	 //setea la posicion de los tiles.
	float fX = m_fPositionX;
	float fY = m_fPositionY;
        for (int k = 0; k < m_vLayers.size(); k++)
        {
                int i = 0;
                for (int row = 0 ; row< m_uiRows; row++)
                {
                        for(int col = 0; col < m_uiCols; col++)
                        {
                                if(m_vLayers[k][i] != NULL)
									m_vLayers[k][i]->setPos( m_vLayers[k][i]->scaleX() * col + fX, m_vLayers[k][i]->scaleY() * -row +fY);
                                i++;
                        }
                }
        }
}
//-----------------------------------------------------------------
void TileMap::ScaleTiles(float fWidth, float fHeight)
{
        m_fTileHeight = fHeight;
        m_fTileWidth = fWidth;

        //le cambio la escala a los tiles
        for(int i = 0; i < m_vLayers.size(); i++)
        {
                for (int j = 0; j < m_vLayers[i].size(); j++)
                {
                        if(m_vLayers[i][j] != NULL)
							m_vLayers[i][j]->setScale(fWidth, fHeight);
                }
        }
        //reposiciono para que queden bien
		SetPosition(m_fPositionX, m_fPositionY);
}
void TileMap::ScaleMap(float x, float y){
	for(int i = 0; i < m_vLayers.size(); i++)
    {
                for (int j = 0; j < m_vLayers[i].size(); j++)
                {
                        if(m_vLayers[i][j] != NULL)
							m_vLayers[i][j]->setScale(x / m_uiCols, y / m_uiRows);
                }
    }
	SetPosition(m_fPositionX, m_fPositionY);
}
//-----------------------------------------------------------------
std::string TileMap::GetName()
{
        return m_sName;
}
//-----------------------------------------------------------------
void TileMap::AddTile(Tile* pkSprite, unsigned int uiLayerNumber)
{
        m_vLayers[uiLayerNumber].push_back(pkSprite);
}
//-----------------------------------------------------------------
void TileMap::AddLayer()
{
        std::vector<Tile*> v;
        m_vLayers.push_back(v);
}
//-----------------------------------------------------------------
TileMap::~TileMap()
{
        //borro todos los tiles q no sean null
        for(int i = 0; i < m_vLayers.size(); i++)
        {
                for (int j = 0; j < m_vLayers[i].size(); j++)
                {
                        if(m_vLayers[i][j] != NULL)
                        delete m_vLayers[i][j];
                }
        }
}
//-----------------------------------------------------------------
