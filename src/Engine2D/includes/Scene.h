#ifndef SCENE_H
#define SCENE_H
#include "Defines.h"
#include "Renderer.h"
#include "Entity2D.h"
#include "TileMap.h"
#include <map>
#include <vector>

namespace Engine{
	class ENGINE_API Scene{
	private:
		//std::string ms_name;

		std::string m_sName;
		std::map<std::string, Entity2D*> m_entitiesMap;	// Entities
		std::map<std::string, Entity2D*>::iterator m_ItEntity;
		std::map<std::string, TileMap*> m_tilesMap;
		std::map<std::string, TileMap*>::iterator m_tilesMapIt;
		typedef std::vector<Entity2D*> Entity2DVector;
		typedef Entity2DVector::iterator Entity2DVectorIter;
		typedef std::map<std::string, Entity2DVector*> CollisionGroupMap;
		typedef std::map<std::string, Entity2DVector*>::iterator CollisionGroupMapIter;
		CollisionGroupMap m_pCollidersGroup;
		CollisionGroupMapIter m_pCollidersGroupsIter;

		CollisionGroupMapIter m_pCollidersGroupsItA;
		CollisionGroupMapIter m_pCollidersGroupsItB;
		Entity2DVector *m_pEntVectorA;
		Entity2DVector *m_pEntVectorB;
		Entity2D *m_pEntA;
		Entity2D *m_pEntB;

	public:
		Scene(std::string name);
		~Scene();
		void Update(Timer* t);
		void Draw(Renderer* m_renderer);
	
		void Add(std::string s_name, Entity2D* p_entity);
		void AddTileMap(std::string s_name, TileMap* p_name);
		void RemoveEntity(Entity2D* entity);
		void RemoveEntity(std::string name);
		Entity2D* GetEntity(std::string name);
		TileMap* GetTileMap(std::string name);
		void SetName(std::string name);
		std::string GetName();

		bool AddCollidersGroup(std::string p_Name);
		bool RemoveCollidersGroup(std::string p_Name);
		bool AddEntityToCollidersGroup(Entity2D* entity, std::string p_ColsGroup);
		bool RemoveEntityFromCollidersGroup(Entity2D* entity);
		bool ChangeEntityFromCollidersGroup(Entity2D* entity, std::string NewColsGroup);

		void CheckCollisions();
	};
}


#endif