#ifndef GAME_H
#define GAME_H
#include "Defines.h"
#include "Window.h"
#include "Timer.h"
#include <vector>
#include <map>

namespace Engine{
class Entity2D;
class Sprite;
class Renderer;
class DirectInput;
class Scene;

class ENGINE_API Game{
	private:
		HINSTANCE m_instance;
		Window* m_pkWindow;
		std::map<std::string, Scene*> m_scenesMap;
		std::map<std::string, Scene*>::iterator m_ItScenesMap;

	public:
		Game(HINSTANCE hInstance);
		~Game();
		bool AddEntity(Entity2D* entity);
		bool GetEntity(Sprite** entity, std::string name);
		bool StartUp();
		bool Loop();
		bool ShutDown();
		std::vector<Entity2D*> m_pkEntities;
		void CreateScene(std::string std);
		Scene* GetScene(std::string std);
		void DrawScene(Renderer* m_renderer, Timer* t);

	protected:
		virtual bool OnStartUp() = 0;
		virtual bool OnLoop() = 0;
		virtual bool OnShutDown() = 0;
	
		Timer timer;
		Renderer* m_renderer;
		DirectInput* dInput;
	};
}

#endif