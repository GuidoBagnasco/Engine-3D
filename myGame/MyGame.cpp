#include "MyGame.h"
#include "animation.h"
#include "Scene.h"
#include "Importer.h"
#include "TileMap.h"
#include "MyCustomScene.h"
#include <iostream>
//#include "Renderer.h"

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

	ent1 = ((engine::Sprite*)scene1->GetEntity("player1"));

	//scene1->GetTileMap("Mapa1")->setScaleTileMap(400, 400);
	//scene1->GetTileMap("Mapa1")->setTileMapPos(-200, 200);

	scene1->GetTileMap("WoodMap2")->ScaleMap(1, 1);
	scene1->GetTileMap("WoodMap2")->SetPosition(-200, 200);


	r.SetBackgroundColor(300, 300, 300);

	_Sprite1 = new engine::Sprite();//PONY

	_Sprite1->setScale(100, 100);
	_Sprite1->setPos(100.0f, 50.0f);

	engine::Texture t = r.loadTexture("Twilight.bmp", engine_COLOR_RGB(255, 255, 254));
	_Sprite1->setTexture(t);

	// Twilight animation
	engine::Animation* tIdle = new engine::Animation();

	tIdle->setName("Idleing");

	tIdle->addFrame(512, 512, 25, 2, 108, 91);

	tIdle->setLength(1000);


	_Sprite1->AddAnimation(tIdle);
	_Sprite1->setAnimation("Idleing");

	//

	engine::Animation* Trot = new engine::Animation();

	Trot->setName("Troting");

	Trot->addFrame(512, 512, 27, 117, 105, 83);
	Trot->addFrame(512, 512, 135, 117, 104, 83);
	Trot->addFrame(512, 512, 243, 117, 100, 83);
	Trot->addFrame(512, 512, 343, 112, 100, 89);

	Trot->addFrame(512, 512, 27, 207, 100, 89);
	Trot->addFrame(512, 512, 131, 209, 100, 84);
	Trot->addFrame(512, 512, 234, 214, 100, 83);
	Trot->addFrame(512, 512, 340, 217, 101, 83);

	Trot->addFrame(512, 512, 34, 315, 105, 83);
	Trot->addFrame(512, 512, 141, 316, 101, 80);
	Trot->addFrame(512, 512, 247, 312, 101, 87);
	Trot->addFrame(512, 512, 349, 311, 95, 82);

	Trot->addFrame(512, 512, 29, 412, 100, 83);
	Trot->addFrame(512, 512, 139, 418, 97, 77);
	Trot->addFrame(512, 512, 237, 417, 98, 80);
	Trot->addFrame(512, 512, 339, 421, 101, 80);

	Trot->setLength(800);

	_Sprite1->AddAnimation(Trot);
	//_Sprite1->setAnimation("Troting");

	// 

	_Sprite2 = new engine::Sprite();

	_Sprite2->setScale(100, 100);
	_Sprite2->setPos(-100.0f, 50.0f, 0.0f);

	engine::Texture t2 = r.loadTexture("Mario.png", engine_COLOR_WHITE);
	_Sprite2->setTexture(t2);



	_Cubo1.setScale(100.0f, 100.0f);
	_Cubo1.setPos(-100.0f, -100.0f);

	_Cubo2.setScale(200.0f, 200.0f);
	_Cubo2.setPos(-100.0f, -100.0f);
	_Cubo2.setRotation(-45.0f);

	_Cubo1.setColor(engine_COLOR_ARGB(0, 0, 255, 0), 0);

	/*_Cubo1.setColor(engine_COLOR_RGB(0, 255, 0), 1);
	_Cubo1.setColor(engine_COLOR_RGB(0, 0, 255), 2);
	_Cubo1.setColor(engine_COLOR_RGB(255, 255, 255), 3);
	*/

	for (int i = 0; i < 4; i++)
		_Cubo2.setColor(engine_COLOR_RGB(85 + (i * 15), 30 + (i * 30), 23 + (i * 10)), i);

	return true;
}
void Game::Frame(engine::Renderer& r, engine::DirectInput& dInput, engine::Timer& timer){

	static float fRot = 0.0f;
	fRot += 0.1f;
	//ent1->setRotation(fRot);
	//_Cubo1.setRotation(fRot);

	float fX = _Sprite1->posX();
	float fY = _Sprite1->posY();
	float fZ = _Sprite1->posZ();

	if (dInput.keyDown(engine::Input::KEY_Q)){
		fZ += 0.3f * timer.timeBetweenFrames();

		ent1->setPos(ent1->posX(), ent1->posY(), ent1->posZ() + 0.3f * timer.timeBetweenFrames());
		_Sprite1->setAnimation("Troting");
		// X1, Y2
	}
	if (dInput.keyDown(engine::Input::KEY_E)){
		fZ -= 0.3f * timer.timeBetweenFrames();

		ent1->setPos(ent1->posX(), ent1->posY(), ent1->posZ() - 0.3f * timer.timeBetweenFrames());
		_Sprite1->setAnimation("Troting");
		// X1, Y2
	}



	if (dInput.keyDown(engine::Input::KEY_W)){
		fY += 0.3f * timer.timeBetweenFrames();

		ent1->setPos(ent1->posX(), ent1->posY() + 0.3f * timer.timeBetweenFrames());
		_Sprite1->setAnimation("Troting");
		// X1, Y2
	}
	if (dInput.keyDown(engine::Input::KEY_S)){
		fY -= 0.3f * timer.timeBetweenFrames();

		ent1->setPos(ent1->posX(), ent1->posY() - 0.3f * timer.timeBetweenFrames());
		_Sprite1->setAnimation("Troting");
	}
	if (dInput.keyDown(engine::Input::KEY_A)){
		fX -= 0.3f * timer.timeBetweenFrames();

		ent1->setPos(ent1->posX() - 0.3f * timer.timeBetweenFrames(), ent1->posY());
		_Sprite1->setScale(-100, 100);
		_Sprite1->setAnimation("Troting");
		// X2, Y2
	}
	if (dInput.keyDown(engine::Input::KEY_D)){
		fX += 0.3f * timer.timeBetweenFrames();

		ent1->setPos(ent1->posX() + 0.3f * timer.timeBetweenFrames(), ent1->posY());

		_Sprite1->setScale(100, 100);
		_Sprite1->setAnimation("Troting");
	}

	if (dInput.keyDown(engine::Input::KEY_D) &
		dInput.keyDown(engine::Input::KEY_A)){
		_Sprite1->setAnimation("Idleing");
	}

	if (dInput.keyDown(engine::Input::KEY_W) &
		dInput.keyDown(engine::Input::KEY_S)){
		_Sprite1->setAnimation("Idleing");
	}

	if (dInput.keyUp(engine::Input::KEY_W) &
		dInput.keyUp(engine::Input::KEY_S) &
		dInput.keyUp(engine::Input::KEY_A) &
		dInput.keyUp(engine::Input::KEY_D)){
		_Sprite1->setAnimation("Idleing");
	}

	if (_Sprite1->checkCollision(_Cubo1) == engine::Entity::NoCollision) {
		_Sprite1->setPos(fX, fY);
	}
	else if (_Sprite1->checkCollision(_Cubo1) == engine::Entity::CollisionHorizontal) {
		_Sprite1->setPos(_Sprite1->posX(), fY);
	}
	else if (_Sprite1->checkCollision(_Cubo1) == engine::Entity::CollisionVertical) {
		_Sprite1->setPos(fX, _Sprite1->posY());
	}
	else if (_Sprite1->checkCollision(_Cubo1) == engine::Entity::CollisionZ) {
		_Sprite1->setPos(fX, fY, _Sprite1->posZ());
	}


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

	/*
	if (dInput.keyDown(engine::Input::KEY_D)){
		mainCamera->RotateRight(mSpeed / 100 * timer.timeBetweenFrames());
	}

	if (dInput.keyDown(engine::Input::KEY_A)){
		mainCamera->RotateRight(-mSpeed / 100 * timer.timeBetweenFrames());
	}
	*/

	mainCamera->Yaw(dInput.mouseRelPosX() * mSpeed / 100 * timer.timeBetweenFrames());

	/*
	if (dInput.keyDown(engine::Input::KEY_W)){
		mainCamera->RotateDown(-mSpeed / 100 * timer.timeBetweenFrames());
	}

	if (dInput.keyDown(engine::Input::KEY_S)){
		mainCamera->RotateDown(mSpeed / 100 * timer.timeBetweenFrames());
	}
	*/

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

	// Fin camera Update





	_Sprite1->update(timer);

	_Cubo2.draw(r);
	_Sprite1->draw(r);
	_Sprite2->draw(r);
	_Cubo1.draw(r);
}


void Game::DeInit(){
	delete _Sprite1;
	delete _Sprite2;

}
