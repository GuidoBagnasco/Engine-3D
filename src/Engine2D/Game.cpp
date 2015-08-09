#include "Game.h"
#include "Scene.h"
#include "Entity2D.h"
#include "Sprite.h"
#include "Renderer.h"
#include "DirectInput.h"
#include <sstream>

using namespace Engine;



Game::Game(HINSTANCE hInstance):
	m_instance (hInstance), dInput (new DirectInput())
{
	
}



bool Game::StartUp(){
	HWND hWnd = NULL;
	
	m_pkWindow = new Window(m_instance);
	if(m_pkWindow == NULL)
		return false;	
	m_pkWindow->CreateWindowE(WINDOW_HEIGHT, WINDOW_WIDTH, hWnd);


	m_renderer = new Renderer(hWnd);
	if(!m_renderer)
		return false;
	if(!m_renderer->InitDX(hWnd))
		return false;

	if(!dInput->init(m_instance, hWnd))
		return false;

	if(!OnStartUp())
		return false;

	timer.FirstMeasure();

	return true;
}




bool Game::Loop(){
	dInput->reacquire();
	m_renderer->StartFrame();

	if(!OnLoop()){
		return false;
	}else{
		DrawScene(m_renderer, &timer);
	}

	timer.Measure();
	std::stringstream s;	//: Updates the FPS count.
	s << "Engine v0.61 - FPS:" << timer.GetFPS();
	m_pkWindow->SetWindowTitle(s.str().c_str());

	m_renderer->EndFrame();
	return true;
}




bool Game::ShutDown(){
	if(!OnShutDown()){
		return false;
	}
	return true;
}




bool Game::AddEntity(Entity2D* entity){
    m_pkEntities.push_back(entity);
    return true;
}



bool Game::GetEntity(Sprite** entity, std::string name){
    if(m_pkEntities.empty())
            return true;

    for(unsigned int i = 0; i < m_pkEntities.size(); i++){
        if(m_pkEntities[i]->GetName() == name){
            *entity = (Sprite*)m_pkEntities[i];
            return true;
        }
    }
    return false;
}



void Game::CreateScene(std::string str){
	Scene* scene = new Scene(str);
	m_scenesMap[str] = scene;
}



Scene* Game:: GetScene(std::string str){
	for (m_ItScenesMap = m_scenesMap.begin(); m_ItScenesMap != m_scenesMap.end(); m_ItScenesMap++){
		if (m_ItScenesMap->first == str)
			return m_ItScenesMap->second;
	}
	return NULL;
}



void Game::DrawScene(Renderer* m_renderer, Timer* t){
	m_ItScenesMap = m_scenesMap.begin();
	do{
		m_ItScenesMap->second->Update(t);
		m_ItScenesMap->second->Draw(m_renderer);
		m_ItScenesMap++;
	}while(m_ItScenesMap != m_scenesMap.end());
}



Game::~Game(){
	delete m_renderer;
	delete m_pkWindow;
	delete dInput;
	if(m_pkEntities.empty()) return;

    for(unsigned int i = 0; i < m_pkEntities.size() ; i++){
        delete m_pkEntities[i];
        m_pkEntities[i] = NULL;
    }

    m_pkEntities.clear();
    return;
}