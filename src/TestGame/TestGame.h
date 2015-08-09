#ifndef TESTGAME_H
#define TESTGAME_H
#include "Game.h"

#include "Triangle.h"
#include "Box.h"
#include "Circle.h"
#include "Sprite.h"
#include "Importer.h"
#include "DirectInput.h"
#include "Timer.h"
#include "Scene.h"
using namespace Engine;

class TestGame : public Game{
private:
	Triangle* t;
	Box* b;
	Circle* c;
	
	Sprite* s2;
	Importer* importer;
	float mouseX, mouseY;

protected:
	bool OnStartUp();
	bool OnLoop();
	bool OnShutDown();

public:
	TestGame(HINSTANCE hInstance);
	Sprite* s;

};

#endif