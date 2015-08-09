#include <Windows.h>
#include "TestGame.h"



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdName, int i_nShowCmd){
	TestGame* pkGame = new TestGame(hInstance);

	if(!pkGame->StartUp())
		return 0;


	bool bQuit = false;
	MSG kMsg;

	
	while(pkGame->Loop() && !bQuit){
		if(PeekMessage(&kMsg, NULL, 0, 0, PM_REMOVE)){
			switch(kMsg.message){
				case WM_QUIT:
					bQuit = true;
					break;

				case WM_KEYDOWN:
					int iKeyCode = (int)kMsg.wParam;
					switch(iKeyCode){
						case VK_ESCAPE:
							bQuit = true;
							break;
					}
					break;
				}

			TranslateMessage(&kMsg);
			DispatchMessage(&kMsg);
		}
	}

	if(pkGame){
		pkGame->ShutDown();
		delete pkGame;
		pkGame = NULL;
	}
	
	return 0;
}