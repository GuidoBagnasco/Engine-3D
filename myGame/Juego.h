#pragma once
#include "Game.h"
#include "Entity.h"
#include "Quad.h"
#include "Sprite.h"
#include "RenderTypes.h"
#include "Renderer.h"
#include "input\pg1_directinput.h"
#include "timer\pg1_timer.h"
#include <iostream>
#include "Camera.h"

namespace MiJuego{
	class Game : public engine::Game{
	public:
		bool Init(engine::Renderer&);
		void Frame(engine::Renderer&, engine::DirectInput&, engine::Timer&);
		void DeInit();
	private:
		engine::Quad _Cubo1;
		engine::Quad _Cubo2;
		engine::Sprite* _Sprite1;
		engine::Sprite* _Sprite2;
		engine::Camera* mainCamera;
		engine::Sprite* ent1;
	};
}