//----------------
#include "Engine.h"
#include "Juego.h"
#include <iostream>

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow){
	engine::Engine myEngine(hInst, "Graficos 1", 640, 480);
	myEngine.init();
	myEngine.G = new MiJuego::Game();
	myEngine.run();
}