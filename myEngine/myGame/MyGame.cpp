#include "MyGame.h"
#include "animation.h"
#include "Scene.h"
#include "Importer.h"
#include "MyCustomScene.h"
#include <iostream>

using namespace MyGame;
float mSpeed = 0.1f;


bool Game::Init(engine::Renderer& r){
	mainCamera = r.c;
	mainCamera->SetPosition(0, 10, -50);
	CreateScene("Scene1");
	engine::Scene* scene1 = GetScene("Scene1");

	MyCustomScene* mcs = new MyCustomScene("MyCustomSceneYAY");
	AddScene(mcs);

	engine::Importer* importer = engine::Importer::GetInstance();

	r.SetBackgroundColor(0, 0, 0);
	
	car = new engine::Node();
	if (importer->ImportScene("Porsche.obj", *car)){
		car->SetPos(-50.0f, 0.0f, -50.0f);
		car->SetScale(10.0f, 10.0f, 10.0f);
	}
	else{
		delete car;
		car = NULL;
	}

	tiny = new engine::Node();
	if (importer->ImportScene("Airplane/airplane 2.x", *tiny)) {
		tiny->SetPos(50.0f, 0.0f, -50.0f);
		tiny->SetScale(1.0f, 1.0f, 1.0f);
	}
	else {
		delete tiny;
		tiny = NULL;
	}

	pig = new engine::Node();
	if (importer->ImportScene("cerdo.obj", *pig)){
		pig->SetScale(1.0f, 1.0f, 1.0f);
	}
	else{
		delete pig;
		pig = NULL;
	}

	return true;
}


void Game::Frame(engine::Renderer& r, engine::DirectInput& dInput, engine::Timer& timer){

	engine::Game::Frame(r, dInput, timer);

	if(dInput.keyDown(engine::Input::KEY_UP) || dInput.keyDown(engine::Input::KEY_W)){
		mainCamera->MoveForward(mSpeed * timer.timeBetweenFrames());
	}

	if(dInput.keyDown(engine::Input::KEY_DOWN) || dInput.keyDown(engine::Input::KEY_S)){
		mainCamera->MoveForward(-mSpeed * timer.timeBetweenFrames());
	}

	if(dInput.keyDown(engine::Input::KEY_LEFT) || dInput.keyDown(engine::Input::KEY_A)){
		mainCamera->MoveRight(-mSpeed * timer.timeBetweenFrames());
	}

	if(dInput.keyDown(engine::Input::KEY_RIGHT) || dInput.keyDown(engine::Input::KEY_D)){
		mainCamera->MoveRight(mSpeed * timer.timeBetweenFrames());
	}

	if (dInput.mouseDown(engine::Input::MB_1)){
		mainCamera->Yaw(dInput.mouseRelPosX() * mSpeed / 200 * timer.timeBetweenFrames());
		mainCamera->Pitch(dInput.mouseRelPosY() * mSpeed / 200 * timer.timeBetweenFrames());
	}

	

	if(dInput.keyDown(engine::Input::KEY_SPACE)){
		mainCamera->MoveUp(mSpeed * timer.timeBetweenFrames());
	}

	if(dInput.keyDown(engine::Input::KEY_LCONTROL)){
		mainCamera->MoveUp(-mSpeed * timer.timeBetweenFrames());
	}

	if(dInput.keyDown(engine::Input::KEY_E)){
		mainCamera->Roll(-mSpeed / 100 * timer.timeBetweenFrames());
	}

	if(dInput.keyDown(engine::Input::KEY_Q)){
		mainCamera->Roll(mSpeed / 100 * timer.timeBetweenFrames());
	}

	if (dInput.keyDown(engine::Input::KEY_ESCAPE))
		setGame(false);

	if (dInput.keyDown(engine::Input::KEY_P)){
		pig->SetPos(pig->PosX() + timer.timeBetweenFrames() * 0.01f, pig->PosY(), pig->PosZ());
	}
	
	if (car != NULL)
		car->Draw(r);

	if (pig != NULL)
		pig->Draw(r);

	if (tiny != NULL)
		tiny->Draw(r);
}


void Game::DeInit(){
	if (car){
		delete car;
		car = NULL;
	}

	if (pig){
		delete pig;
		pig = NULL;
	}

	if (tiny) {
		delete tiny;
		tiny = NULL;
	}
}
