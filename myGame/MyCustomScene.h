#include "Scene.h"
#include "timer\pg1_timer.h"
#include <iostream>
namespace MiJuego{
	class MyCustomScene : public engine::Scene{
	public:
		MyCustomScene(std::string s) : Scene(s){ }
		~MyCustomScene() { }
		virtual void OnStart() { std::cout << "Testing My Custom Scene " << std::endl;  }
		virtual void OnUpdate(engine::Timer*) { /*std::cout << Testing MyCustomScene Loop" << std::endl;*/ }
		virtual void OnShutdown() { std::cout << "Testing my custom scene shutdown" << std::endl; }
	};
}