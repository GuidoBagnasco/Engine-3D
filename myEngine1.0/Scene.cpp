#include "Scene.h"
#include "Renderer.h"
#include "Sprite.h"
#include "Entity.h"
#include "Quad.h"
#include "TileMap.h"
#include <algorithm>
using namespace engine;

Scene::Scene(std::string sName){
	m_sName = sName;
}
Scene::~Scene()
{
	m_pClsGroups.clear();
	//m_pEntVectorA->clear();
	//m_pEntVectorB->clear();
	for (m_mIteratorEntity = m_mapaEntity.begin(); m_mIteratorEntity != m_mapaEntity.end(); m_mIteratorEntity++)
	{
		delete m_mIteratorEntity->second;
	}
}
void Scene::SetName(std::string sName)
{
	m_sName = sName;
}
std::string Scene::GetName()
{
	return m_sName;
}
void Scene::Draw(Renderer* m_pRender)
{
	if (m_mTileMaps.size() > 0)
	{
		m_mTileMapsIter = m_mTileMaps.begin();
		do
		{
			m_mTileMapsIter->second->Draw(m_pRender);
			m_mTileMapsIter++;
		} while (m_mTileMapsIter != m_mTileMaps.end());
	}

	if (m_mapaEntity.size() > 0)
	{
		m_mIteratorEntity = m_mapaEntity.begin();
		do
		{
			/* DISABLE THIS ! Para no dibujar AABBS!*/ //m_mIteratorEntity->second->drawAABB(*m_pRender);
			m_mIteratorEntity->second->draw(*m_pRender);
			m_mIteratorEntity++;
		} while (m_mIteratorEntity != m_mapaEntity.end());
	}
}
void Scene::Update(Timer* timer)
{
	if (m_mapaEntity.size() > 0){
		CheckColisions();
		m_mIteratorEntity = m_mapaEntity.begin();
		do
		{
			m_mIteratorEntity->second->update(*timer);
			m_mIteratorEntity++;
		} while (m_mIteratorEntity != m_mapaEntity.end());
	}
}
void Scene::Add(std::string sNombre, Entity* pEntidad)
{
	m_mIteratorEntity = m_mapaEntity.begin();
	m_mIteratorEntity = m_mapaEntity.find(sNombre);
	if (m_mIteratorEntity != m_mapaEntity.end())
		return;
	m_mapaEntity[sNombre] = pEntidad;
}

void Scene::AddTileMap(std::string sNombre, TileMap* p_NombreTM)//agrego tilemap
{
	m_mTileMapsIter = m_mTileMaps.begin();
	m_mTileMapsIter = m_mTileMaps.find(sNombre);
	if (m_mTileMapsIter != m_mTileMaps.end())
		return;
	m_mTileMaps[sNombre] = p_NombreTM;
}
void Scene::RemoveEntity(std::string sNombre)
{
	m_mapaEntity.erase(sNombre);
}
void Scene::RemoveEntity(Entity* pEntity)
{
	m_mIteratorEntity = m_mapaEntity.begin();
	while (m_mIteratorEntity != m_mapaEntity.end())
	{
		if (m_mIteratorEntity->second == pEntity)
			m_mapaEntity.erase(m_mIteratorEntity);
	}
}
Entity*Scene::GetEntity(std::string sNombre)
{
	/*m_mIteratorEntity = m_mapaEntity.begin();
	m_mIteratorEntity = m_mapaEntity.find(sNombre);
	return m_mIteratorEntity->second;*/

	if (m_mapaEntity.count(sNombre))
		return m_mapaEntity[sNombre];
	else
		return NULL;
}
TileMap* Scene::GetTileMap(std::string sNombre){
	if (m_mTileMaps.count(sNombre))
		return m_mTileMaps[sNombre];
	else
		return NULL;
}
bool Scene::AddClsGroup(std::string p_Name)
{
	if (p_Name == "") // que no pase nombre vacio
		return false;
	CollisionGroupMapIter iter = m_pClsGroups.find(p_Name); // y q no existe ya
	if (iter != m_pClsGroups.end())
		return false;

	Entity2DVector* NuevoGroupo = new Entity2DVector();
	m_pClsGroups[p_Name] = NuevoGroupo;

	return true;
}
bool Scene::RemoveClsGroup(std::string p_Name)
{
	if (p_Name == "") //que no sea vacio
		return false;
	CollisionGroupMapIter iter = m_pClsGroups.find(p_Name);
	if (iter == m_pClsGroups.end())
		return false; // y que existe

	m_pClsGroups.erase(iter);//entonces borro
	return true;
}
void Scene::CheckColisions()
{
	if (m_pClsGroups.size()>1)//si el mapa es mayor a 1 tiene 2 grupos
	{
		//este no llega al end, porque va a llegar el siguiente, ya que sino hacemos todo doble
		for (m_pClsGroupsIterA = m_pClsGroups.begin(); m_pClsGroupsIterA != m_pClsGroups.end(); m_pClsGroupsIterA++)
		{
			m_pEntVectorA = m_pClsGroupsIterA->second;
			//lega al end
			for (m_pClsGroupsIterB = (++m_pClsGroupsIterA); m_pClsGroupsIterB != m_pClsGroups.end(); m_pClsGroupsIterB++)
			{
				m_pEntVectorB = m_pClsGroupsIterB->second;
				//recorro el primer vector
				for (int i = 0; i<m_pEntVectorA->size(); i++)
				{
					//me guardo la entity
					m_pEntA = (*m_pEntVectorA)[i];
					//recorro el SEGUNO vector
					for (int j = 0; j<m_pEntVectorB->size(); j++)
					{
						//me guardo la entity
						m_pEntB = (*m_pEntVectorB)[j];

						if (m_pEntA->checkCollision(*m_pEntB) != Entity::NoCollision) // me fijo si coliciono
						{
							//m_pEntA->returnToPreviousPos();
							m_pEntB->returnToPreviousPos();
						}
					}
				}
				if (m_pEntVectorA->size() < 2)
					break;
			}
			if (m_pEntVectorB->size() < 2)
				break;
		}
	}
}
bool Scene::AddEntityToClsGroup(Entity* p_pEntity, std::string p_ColGroup)
{
	//assert(p_pEntity);

	if (p_ColGroup != "")//me fijo que tenga nombre
	{
		m_pClsGroupsIter = m_pClsGroups.find(p_ColGroup);//lo busco

		if (m_pClsGroupsIter == m_pClsGroups.end())
			return false;//si no existe no lo agrego

		m_pEntVectorA = m_pClsGroupsIter->second;
		//assert(m_pEntVectorA);

		m_pEntVectorA->push_back(p_pEntity);//lo pongo en el vector grupo
		p_pEntity->setCollisionGroup(p_ColGroup);//le digo cual es su grupo
	}
	return true;
}
bool Scene::RemoveEntityFromClsGroup(Entity* p_pEntity)
{
	if (p_pEntity->getCollisionGroup() != "") // si tiene grupo
	{
		m_pEntVectorA = m_pClsGroups[p_pEntity->getCollisionGroup()];
		//assert(m_pEntVectorA);

		Entity2DVectorIter ClsIterador = find(m_pEntVectorA->begin(), m_pEntVectorA->end(), p_pEntity);

		if (ClsIterador != m_pEntVectorA->end())
			m_pEntVectorA->erase(ClsIterador);
	}
	return true;
}
bool Scene::ChangeEntityFromClsGroup(Entity* p_pEntity, std::string NewClsGroup)
{
	if (RemoveEntityFromClsGroup(p_pEntity))
	{
		if (AddEntityToClsGroup(p_pEntity, NewClsGroup))
			return true;
	}

	return false;
}