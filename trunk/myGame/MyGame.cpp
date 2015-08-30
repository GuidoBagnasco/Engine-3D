#include "MyGame.h"
#include "animation.h"
#include "Scene.h"
#include "Importer.h"
#include "MyCustomScene.h"
#include <iostream>

using namespace MyGame;
float mSpeed = 0.1f;


bool Game::Init(engine::Renderer& r){

	mainCamera = engine::Camera::Main();
	mainCamera->SetPosition(0, 0, -200);
	CreateScene("Scene1");
	engine::Scene* scene1 = GetScene("Scene1");

	MyCustomScene* mcs = new MyCustomScene("MyCustomSceneYAY");
	AddScene(mcs);

	engine::Importer* importer = engine::Importer::GetInstance();

	importer->ImportScene(*scene1, "scene1.xml");

	plane = new engine::Mesh(*importer->GetInstance()->GetRenderer());
	importer->ImportMesh(*plane, "Mesh.obj");
	plane->SetPos(0.0f, 0.0f, 0.0f);
	plane->SetScale(10.0f,10.0f, 10.0f);
	
	mesh = new engine::Cube(r);

	mesh->SetScale(100, 100, 100);



	r.SetBackgroundColor(31, 67, 243);

	//
	return true;
}


void Game::Frame(engine::Renderer& r, engine::DirectInput& dInput, engine::Timer& timer){

	// Camera Update 

	if(dInput.keyDown(engine::Input::KEY_UP) || dInput.keyDown(engine::Input::KEY_W)){
		mainCamera->Walk(mSpeed * timer.timeBetweenFrames());
	}

	if(dInput.keyDown(engine::Input::KEY_DOWN) || dInput.keyDown(engine::Input::KEY_S)){
		mainCamera->Walk(-mSpeed * timer.timeBetweenFrames());
	}

	if(dInput.keyDown(engine::Input::KEY_LEFT) || dInput.keyDown(engine::Input::KEY_A)){
		mainCamera->Strafe(-mSpeed * timer.timeBetweenFrames());
	}

	if(dInput.keyDown(engine::Input::KEY_RIGHT) || dInput.keyDown(engine::Input::KEY_D)){
		mainCamera->Strafe(mSpeed * timer.timeBetweenFrames());
	}

	mainCamera->Yaw(dInput.mouseRelPosX() * mSpeed / 100 * timer.timeBetweenFrames());

	mainCamera->Pitch(dInput.mouseRelPosY() * mSpeed / 100 * timer.timeBetweenFrames());

	if(dInput.keyDown(engine::Input::KEY_SPACE)){
		mainCamera->Jump(mSpeed * timer.timeBetweenFrames());
	}

	if(dInput.keyDown(engine::Input::KEY_LCONTROL)){
		mainCamera->Jump(-mSpeed * timer.timeBetweenFrames());
	}

	if(dInput.keyDown(engine::Input::KEY_E)){
		mainCamera->Roll(-mSpeed / 100 * timer.timeBetweenFrames());
	}

	if(dInput.keyDown(engine::Input::KEY_Q)){
		mainCamera->Roll(mSpeed / 100 * timer.timeBetweenFrames());
	}

	if(mesh != NULL)
		mesh->Draw();

	if(plane != NULL)
		plane->Draw();
	// Fin camera Update
}


void Game::DeInit(){
	if(mesh){
		delete mesh;
		mesh = NULL;
	}	
}
