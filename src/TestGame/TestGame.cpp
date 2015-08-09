#include "TestGame.h"
#include "Timer.h"

TestGame::TestGame(HINSTANCE hInstance) : Game(hInstance){
	
}




bool TestGame::OnStartUp(){
	//t = new Triangle(SetVertex(-50, 0, -1, 152, 20, 71), SetVertex(50, 0, 0, 152, 20, 71), SetVertex(0, 50, 0, 152, 20, 71), 2, 4);

	//b = new Box(SetVertex(-50, -150, 0, 23, 17, 71), SetVertex(0, -150, 0, 23, 17, 71), SetVertex(-10, -50, 0, 23, 17, 71), SetVertex(40, -50, 0, 23, 17, 71), 1, 2);

	//c = new Circle(90, 0, 0, 255, 0, 0);

	importer = new Importer(m_renderer);

	CreateScene("MainScene");
	Engine::Scene* mainScene = GetScene("MainScene");
	importer->Load("Asuna.xml", *mainScene);

	s =  ((Engine::Sprite*)mainScene->GetEntity("character"));
	s2 = ((Engine::Sprite*)mainScene->GetEntity("character2"));

	mainScene->GetTileMap("Map")->SetMapScale(850,850);
	mainScene->GetTileMap("Map")->SetMapPosition(-400,350);
	return true;
}


static float fspeed = 0.20f;

bool TestGame::OnLoop(){
	//t->Draw(m_renderer);
	//b->Draw(m_renderer);					// Show
	//c->Draw(m_renderer);
	
	if(s2 != NULL){
		s2->SetAnimation("Idle");

		if(dInput->keyDown(Engine::Input::KEY_DOWN)){
			s2->SetPosition(s2->GetPositionX(), s2->GetPositionY() -  fspeed * timer.GetDT());
			s2->SetAnimation("WalkingS");
		}
		else if(dInput->keyDown(Engine::Input::KEY_UP)){
			s2->SetPosition(s2->GetPositionX(), s2->GetPositionY() +  fspeed * timer.GetDT());
			s2->SetAnimation("WalkingN");
		}
		else if(dInput->keyDown(Engine::Input::KEY_RIGHT)){
			s2->SetPosition(s2->GetPositionX()  +  fspeed * timer.GetDT(), s2->GetPositionY());
			s2->SetAnimation("WalkingE");
		}
		else if(dInput->keyDown(Engine::Input::KEY_LEFT)){
			s2->SetPosition(s2->GetPositionX() -  fspeed * timer.GetDT(), s2->GetPositionY());
			s2->SetAnimation("WalkingW");
		}
	}
	

	if(s != NULL){

		if(dInput->mouseDown(Input::MB_1)){
			s->SetAnimation("WalkingNE");
			s->SetPosition(s->GetPositionX() + dInput->mouseRelPosX(), s->GetPositionY() - dInput->mouseRelPosY());
		}
		else{
			s->SetAnimation("Idle");
		}
		/*
		if(dInput->mouseDown(Input::MB_1)){
			if(dInput->mouseRelPosX() > mouseX){
				if(dInput->mouseRelPosY() > mouseY){
					// North-west
					s->SetAnimation("WalkingNW");
				}
				else{
					// South-west
					s->SetAnimation("WalkingSW");
				}
			}
			else{
				if(dInput->mouseRelPosY() > mouseY){
					// North-east
					//s->SetAnimation("WalkingNE");
					s->SetAnimation("WalkingN");
				}
				else{
					// South-east
					//s->SetAnimation("WalkingSE");
					s->SetAnimation("WalkingE");
				}
			}
			mouseX = dInput->mouseRelPosX();
			mouseY = dInput->mouseRelPosY();
			s->SetPosition(s->GetPositionX() + dInput->mouseRelPosX(), s->GetPositionY() - dInput->mouseRelPosY());
		}
		else{
			s->SetAnimation("Idle");
		}
		*/
	}

	return true;
}




bool TestGame::OnShutDown(){
	return true;
}