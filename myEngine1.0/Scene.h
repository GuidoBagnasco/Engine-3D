#pragma once
#include <string>
#include <map>
#include <vector>
#include "myEngine_API.h"

namespace engine{
	class Renderer;
	class Entity;
	class TileMap;
	class Timer;

	class MYENGINE_API Scene{
	public:
		Scene(std::string name); //le pasamos un nombre para identificarlo
		~Scene();
		void Update(Timer*);
		void Draw(Renderer* m_pRender);
		void Add(std::string sNombre, Entity* pEntidad);//agrego entidad
		void AddTileMap(std::string sNombre, TileMap* p_NombreTM);//agrego entidad
		void RemoveEntity(Entity* pEntity);//quito entidad
		void RemoveEntity(std::string sNombre);//quito entidad por nombre
		Entity* GetEntity(std::string sNombre);
		TileMap* GetTileMap(std::string sNombre);
		void SetName(std::string sName);
		std::string GetName();
		//colisiones
		bool AddClsGroup(std::string p_Name);
		bool RemoveClsGroup(std::string p_Name);
		bool AddEntityToClsGroup(Entity* p_pEntity, std::string p_ColGroup);
		bool RemoveEntityFromClsGroup(Entity* p_pEntity);
		bool ChangeEntityFromClsGroup(Entity* p_pEntity, std::string NewClsGroup);
		void CheckColisions();
		//-----------------------------------------
	private:
		std::string m_sName;
		std::map<std::string, Entity*> m_mapaEntity;//entidades que tiene
		std::map<std::string, Entity*>::iterator m_mIteratorEntity;//iterador para recorrerlas	
		std::map<std::string, TileMap*> m_mTileMaps;//entidades que tiene
		std::map<std::string, TileMap*>::iterator m_mTileMapsIter;//iterador para recorrerlas	
		typedef std::vector<Entity*> Entity2DVector;//defino
		typedef Entity2DVector::iterator Entity2DVectorIter;//defino	
		typedef std::map< std::string, Entity2DVector*> CollisionGroupMap;// defino
		typedef std::map< std::string, Entity2DVector*>::iterator CollisionGroupMapIter; //defino
		CollisionGroupMap m_pClsGroups;
		CollisionGroupMapIter m_pClsGroupsIter;
		//------------------
		//Todo esto es para el los for del check col
		CollisionGroupMapIter m_pClsGroupsIterA;
		CollisionGroupMapIter m_pClsGroupsIterB;
		Entity2DVector *m_pEntVectorA;
		Entity2DVector *m_pEntVectorB;
		Entity *m_pEntA;
		Entity *m_pEntB;
		//------------------

	public:	// Virtual functions to override if the user want to make his own scenes...
		virtual void OnStart() { }
		virtual void OnUpdate(Timer*) { } 
		virtual void OnShutdown() { }
	};
}