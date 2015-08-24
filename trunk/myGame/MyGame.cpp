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

	importer->importScene(*scene1, "scene1.xml");

	//scene1->GetEntity("Cube01")->

	mesh = new engine::Mesh(r);

	engine::ColorVertex g_8Vertices[] = {
			{ -0.5f, 0.5f, -0.5f, D3DCOLOR_XRGB(255, 0, 0) }, // 0 
			{ 0.5f, 0.5f, -0.5f, D3DCOLOR_XRGB(0, 255, 0) }, // 1 
			{ 0.5f, 0.5f, 0.5f, D3DCOLOR_XRGB(40, 0, 120) }, // 2 
			{ -0.5f, 0.5f, 0.5f, D3DCOLOR_XRGB(255, 0, 0) }, // 3

			{ -0.5f, -0.5f, 0.5f, D3DCOLOR_XRGB(0, 255, 0) }, // 4
			{ 0.5f, -0.5f, 0.5f, D3DCOLOR_XRGB(40, 0, 120) }, // 5
			{ 0.5f, -0.5f, -0.5f, D3DCOLOR_XRGB(255, 0, 0) }, // 6
			{ -0.5f, -0.5f, -0.5f, D3DCOLOR_XRGB(0, 255, 0) } // 7
	};

	USHORT g_indices[] = { 0, 1, 2, 0, 2, 3,
		4, 5, 6, 4, 6, 7,
		3, 2, 5, 3, 5, 4,
		2, 1, 6, 2, 6, 5,
		1, 7, 6, 1, 0, 7,
		0, 3, 4, 0, 4, 7 };

	mesh->SetData(g_8Vertices, 8, engine::TriangleList, g_indices, 36);
	mesh->SetScale(200, 200, 200);
	r.SetBackgroundColor(300, 300, 300);

	//
	return true;
}


void Game::Frame(engine::Renderer& r, engine::DirectInput& dInput, engine::Timer& timer){

	// Camera Update 

	if (dInput.keyDown(engine::Input::KEY_UP) || dInput.keyDown(engine::Input::KEY_W)){
		mainCamera->Walk(mSpeed * timer.timeBetweenFrames());
	}

	if (dInput.keyDown(engine::Input::KEY_DOWN) || dInput.keyDown(engine::Input::KEY_S)){
		mainCamera->Walk(-mSpeed * timer.timeBetweenFrames());
	}

	if (dInput.keyDown(engine::Input::KEY_LEFT) || dInput.keyDown(engine::Input::KEY_A)){
		mainCamera->Strafe(-mSpeed * timer.timeBetweenFrames());
	}

	if (dInput.keyDown(engine::Input::KEY_RIGHT) || dInput.keyDown(engine::Input::KEY_D)){
		mainCamera->Strafe(mSpeed * timer.timeBetweenFrames());
	}

	mainCamera->Yaw(dInput.mouseRelPosX() * mSpeed / 100 * timer.timeBetweenFrames());

	mainCamera->Pitch(dInput.mouseRelPosY() * mSpeed / 100 * timer.timeBetweenFrames());

	if (dInput.keyDown(engine::Input::KEY_SPACE)){
		mainCamera->Jump(mSpeed * timer.timeBetweenFrames());
	}

	if (dInput.keyDown(engine::Input::KEY_LCONTROL)){
		mainCamera->Jump(-mSpeed * timer.timeBetweenFrames());
	}

	if (dInput.keyDown(engine::Input::KEY_E)){
		mainCamera->Roll(-mSpeed / 100 * timer.timeBetweenFrames());
	}

	if (dInput.keyDown(engine::Input::KEY_Q)){
		mainCamera->Roll(mSpeed / 100 * timer.timeBetweenFrames());
	}

	mesh->Draw();
	// Fin camera Update
}


void Game::DeInit(){
	if (mesh)
	{
		delete mesh;
		mesh = NULL;
	}
		
}
