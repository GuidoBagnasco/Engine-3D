#include "Scene.h"
using namespace Engine;


Scene::Scene(std::string name){
	m_sName = name;
}



Scene::~Scene(){
	m_pCollidersGroup.clear();
	m_pEntVectorA->clear();
	m_pEntVectorB->clear();
}



void Scene::Add(std::string s_name, Entity2D* p_entity){
	m_ItEntity = m_entitiesMap.begin();
	m_ItEntity = m_entitiesMap.find(s_name);
	if (m_ItEntity != m_entitiesMap.end())
		return;
	m_entitiesMap[s_name] = p_entity;
}


// Adds a tilesmap
void Scene::AddTileMap(std::string s_name, TileMap* p_name){
	m_tilesMapIt = m_tilesMap.begin();
	m_tilesMapIt = m_tilesMap.find(s_name);

	if(m_tilesMapIt != m_tilesMap.end())
		return;

	m_tilesMap[s_name] = p_name;
}



void Scene::SetName(std::string name){
	m_sName = name;
}



std::string Scene::GetName(){
	return m_sName;
}



void Scene::RemoveEntity(std::string name){
	m_entitiesMap.erase(name);
}



void Scene::RemoveEntity(Entity2D* entity){
	m_ItEntity = m_entitiesMap.begin();
	while (m_ItEntity != m_entitiesMap.end())
	{
		if (m_ItEntity->second == entity)
			m_entitiesMap.erase(m_ItEntity);
	}
}



Entity2D*Scene::GetEntity(std::string name){
	if (m_entitiesMap.count(name)){
		return m_entitiesMap[name];
	}
	else{
		return NULL;
	}
}



void Scene::Draw(Renderer* m_renderer){
	if(m_tilesMap.size() > 0){
		m_tilesMapIt = m_tilesMap.begin();
		do{
			m_tilesMapIt->second->Draw(m_renderer);
			m_tilesMapIt++;
		} while(m_tilesMapIt != m_tilesMap.end());
	}

	if(m_entitiesMap.size() > 0){
		m_ItEntity = m_entitiesMap.begin();
		do{
			m_ItEntity->second->Draw(m_renderer);
			m_ItEntity++;
		}while(m_ItEntity != m_entitiesMap.end());
	}
}



void Scene::Update(Timer* t){
	if(m_entitiesMap.size() > 0){
		CheckCollisions();
		m_ItEntity = m_entitiesMap.begin();
		do{
			m_ItEntity->second->Update(*t);
			m_ItEntity++;
		} while(m_ItEntity != m_entitiesMap.end());
	}
}



TileMap* Scene::GetTileMap(std::string name){
	if (m_tilesMap.count(name)){
		return m_tilesMap[name];
	}
	else{
		return NULL;
	}
}



bool Scene::AddCollidersGroup(std::string name){
	if (name == "")
		return false;

	CollisionGroupMapIter iter = m_pCollidersGroup.find(name);
	if (iter != m_pCollidersGroup.end())
		return false;

	Entity2DVector* newGroup = new Entity2DVector();
	m_pCollidersGroup[name] = newGroup;

	return true;
}



bool Scene::RemoveCollidersGroup(std::string name){
	if (name == "")
		return false;

	CollisionGroupMapIter it = m_pCollidersGroup.find(name);
	if (it == m_pCollidersGroup.end())
		return false;

	m_pCollidersGroup.erase(it);
	return true;
}



void Scene::CheckCollisions(){
	if(m_pCollidersGroup.size() > 1){
		for(m_pCollidersGroupsItA = m_pCollidersGroup.begin(); m_pCollidersGroupsItA != m_pCollidersGroup.end(); m_pCollidersGroupsItA++){
			m_pEntVectorA = m_pCollidersGroupsItA->second;

			for(m_pCollidersGroupsItB = (++m_pCollidersGroupsItA); m_pCollidersGroupsItB != m_pCollidersGroup.end(); m_pCollidersGroupsItB++){
				m_pEntVectorB = m_pCollidersGroupsItB->second;

				// First vector
				for(int i = 0; i < m_pEntVectorA->size(); i++){
					// Saves the entity
					m_pEntA = (*m_pEntVectorA)[i];

					// Second vector
					for(int j = 0; j < m_pEntVectorB->size(); j++){
						// Saves the entity
						m_pEntB = (*m_pEntVectorB)[j];

						// Checks if the two objects are colliding with each other
						if(m_pEntA->CheckCollision(*m_pEntB) != Entity2D::NoCollision){
							m_pEntA->SetPosition(m_pEntA->GetPreviousX(), m_pEntA->GetPreviousY());
							m_pEntB->SetPosition(m_pEntB->GetPreviousX(), m_pEntB->GetPreviousY());
						}
					}
				}
				
			}
			if(m_pEntVectorA->size() < 2)
					break;
		}
	}
}



bool Scene::AddEntityToCollidersGroup(Entity2D* entity, std::string p_ColsGroup){
	if(p_ColsGroup != ""){
		m_pCollidersGroupsIter = m_pCollidersGroup.find(p_ColsGroup);

		if (m_pCollidersGroupsIter == m_pCollidersGroup.end())
			return false;

		m_pEntVectorA = m_pCollidersGroupsIter->second;

		m_pEntVectorA->push_back(entity);
		entity->SetCollisionsGroup(p_ColsGroup);
	}
	return true;
}



bool Scene::RemoveEntityFromCollidersGroup(Entity2D* entity){
	if (entity->GetCollisionsGroup() != ""){
		m_pEntVectorA = m_pCollidersGroup[entity->GetCollisionsGroup()];

		Entity2DVectorIter CollidersIt = find(m_pEntVectorA->begin(), m_pEntVectorA->end(), entity);

		if (CollidersIt != m_pEntVectorA->end())
			m_pEntVectorA->erase(CollidersIt);
	}
	return true;
}



bool Scene::ChangeEntityFromCollidersGroup(Entity2D* entity, std::string NewClsGroup){
	if(RemoveEntityFromCollidersGroup(entity)){
		if (AddEntityToCollidersGroup(entity, NewClsGroup))
			return true;
	}
	else{
		return false;
	}
}