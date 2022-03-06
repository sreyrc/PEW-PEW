/* Start Header -------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
Project Name: Game Engine.sln, Game Engine.vcxproj
Game Name: PEW PEW 
Student Name: Srey Raychaudhuri
DigiPen ID: 60000721
Program: MSCS
Language: C++, MSVC
- End Header --------------------------------------------------------*/

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <SDL_image.h>

#include <ctime>
#include <cmath>

#include <SDL.h>
#include <iostream>
#include "stdio.h"

#include "Windows.h"

#include "InputManager.h"
#include "FrameRateController.h"
#include "ResourceManager.h"
#include "GameObjectManager.h"
#include "EventManager.h"
#include "CollisionManager.h"
#include "Shader.h"
#include "Renderer.h"
#include "Mesh.h"
#include "GameObject.h"
#include "Transform.h"
#include "GameObjectFactory.h"
#include "WorldVariables.h"
#include "GameObjectSpawner.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


FILE _iob[] = { *stdin, *stdout, *stderr };

extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}

#pragma comment(lib, "legacy_stdio_definitions.lib")

SDL_Window* pWindow;

InputManager* gpInputManager;
FrameRateController* gpFrameRateController;
ResourceManager* gpResourceManager;
GameObjectFactory* gpGameObjectFactory;
GameObjectManager* gpGameObjectManager;
EventManager* gpEventManager;
CollisionManager* gpCollisionManager;
Shader* gpShader;
Renderer* gpRenderer;
Mesh* gpMesh;
GameObjectSpawner* gpGameObjectSpawner;

int main(int argc, char* args[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	if (AllocConsole())
	{
		FILE* file;

		freopen_s(&file, "CONOUT$", "wt", stdout);
		freopen_s(&file, "CONOUT$", "wt", stderr);
		freopen_s(&file, "CONOUT$", "wt", stdin);

		SetConsoleTitle(L"SDL 2.0 Test");
	}

	int error = 0;
	bool appIsRunning = true;
	SDL_Surface* pWindowSurface = NULL;

	SDL_Surface* pImageSurface = NULL;

	if ((error = SDL_Init(SDL_INIT_VIDEO)) < 0)
	{
		printf("Couldn't initialize SDL, error %i\n", error);
		return 1;
	}


	pWindow = SDL_CreateWindow("SDL2 window",		
		SDL_WINDOWPOS_CENTERED,					
		SDL_WINDOWPOS_CENTERED,					
		400,										
		600,										
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	if (NULL == pWindow)
	{
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);


	SDL_Renderer* renderer = SDL_CreateRenderer(pWindow, -1,
		SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr) {
		std::cerr << "SDL2 Renderer couldn't be created. Error: "
			<< SDL_GetError()
			<< std::endl;
		exit(1);
	}

	SDL_GLContext gl_context = SDL_GL_CreateContext(pWindow);
	SDL_GL_MakeCurrent(pWindow, gl_context);


	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		std::cerr << "Failed to initialize the OpenGL context." << std::endl;
		exit(1);
	}

	std::cout << "OpenGL version loaded: " << GLVersion.major << "."
		<< GLVersion.minor << std::endl;

	pWindowSurface = SDL_GetWindowSurface(pWindow);


	gpInputManager = new InputManager();
	gpFrameRateController = new FrameRateController(120);
	gpResourceManager = new ResourceManager();
	gpGameObjectFactory = new GameObjectFactory();
	gpGameObjectManager = new GameObjectManager();
	gpEventManager = new EventManager();
	gpCollisionManager = new CollisionManager();
	gpGameObjectSpawner = nullptr;


	gpShader = new Shader("Shader.vert", "Shader.frag");
	gpMesh = new Mesh();
	gpRenderer = new Renderer();

	gpMesh->CreateMeshes();

	srand(time(NULL));

	float gameStartTime = 0;

	bool mouseButtonDisabled = false;
	
	std::string state = "To Start Screen";

	// Game loop
	while (true == appIsRunning)
	{

		if (state == "To Start Screen") {
			gpGameObjectFactory->BuildObject("Start Screen.json");
			state = "Can Click";
		}

		if (state == "Start Game") {

			state = "Game Running";
			gpGameObjectManager->GetGameObject("Start Screen")->mDestroyed = true;
			gpGameObjectSpawner = new GameObjectSpawner();
			gpGameObjectFactory->LevelLoad("Level.json");
			gameStartTime = SDL_GetTicks() / 1000.0f;

			gpEventManager->Subscribe("PLAYER SHOOTS BEAM", gpGameObjectManager->GetGameObject("Player"));
			gpEventManager->Subscribe("ENEMY HITS RED LINE", gpGameObjectManager->GetGameObject("Player"));

			gpEventManager->Subscribe("PLAYER GETS HEART", gpGameObjectManager->GetGameObject("Stat Display Manager"));
			gpEventManager->Subscribe("PLAYER HIT ENEMY!", gpGameObjectManager->GetGameObject("Stat Display Manager"));
			gpEventManager->Subscribe("ENEMY HITS RED LINE", gpGameObjectManager->GetGameObject("Stat Display Manager"));
			gpEventManager->Subscribe("ENEMY BULLET HITS PLAYER", gpGameObjectManager->GetGameObject("Stat Display Manager"));
			gpEventManager->Subscribe("PLAYER SHOOTS BEAM", gpGameObjectManager->GetGameObject("Stat Display Manager"));
			gpEventManager->Subscribe("PLAYER GETS BEAM AMMO", gpGameObjectManager->GetGameObject("Stat Display Manager"));
		}


		if (gameStartTime) {
			if ((SDL_GetTicks() / 1000.0f) - gameStartTime >= 120.0f) {
				gpGameObjectFactory->BuildObject("Win Text.json");
				gpCollisionManager->StopTimers();
				gameStartTime = 0.0f;
			}
		}

		if (gameStartTime) {
			WorldVariables::t = ((SDL_GetTicks() / 1000.0f) - gameStartTime) / 120.0f;
		}

		gpInputManager->Update();

		gpFrameRateController->FrameStart();

		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				appIsRunning = false;
			}
		} // done with handling events

		if (gpInputManager->isLeftMouseButtonTriggered() && 
			gpInputManager->GetMousePos().y > 515.0f && gpInputManager->GetMousePos().y < 560.0f &&
			gpInputManager->GetMousePos().x > 99.0f && gpInputManager->GetMousePos().x < 301.0f &&
			!mouseButtonDisabled) {

			state = "Start Game";
			mouseButtonDisabled = true;
		}

		//std::cout << gpInputManager->GetMousePos().x << " " << gpInputManager->GetMousePos().y << std::endl;

		if (gpInputManager->IsKeyPressed(SDL_SCANCODE_ESCAPE)) {
			appIsRunning = false;
		}

		if (gpGameObjectSpawner != nullptr) {
			gpGameObjectSpawner->UpdateWorldTimers();
			gpGameObjectSpawner->SpawnObject();

		}

		gpCollisionManager->Update();
		
		gpEventManager->Update(gpFrameRateController->GetDeltaTime());

		gpGameObjectManager->RunUpdates();

		gpEventManager->UnsubscribeDestroyedObjects();

		if (gpGameObjectManager->GetGameObject("Player") != nullptr && 
			gpGameObjectManager->GetGameObject("Player")->mDestroyed) {
			state = "Game Over!";
		}

		gpGameObjectManager->DeleteDestroyedGameObjects();

		gpRenderer->Clear();
		gpRenderer->Draw();

		gpFrameRateController->FrameEnd();

		SDL_GL_SwapWindow(pWindow);

	}

	delete gpFrameRateController;
	delete gpInputManager;
	delete gpCollisionManager;
	delete gpResourceManager;
	delete gpGameObjectFactory;
	delete gpGameObjectManager;
	delete gpGameObjectSpawner;
	delete gpMesh;
	delete gpRenderer;
	delete gpShader;

	SDL_GL_DeleteContext(gl_context);
	SDL_DestroyRenderer(renderer);

	SDL_DestroyWindow(pWindow);

	SDL_Quit();

	return 0;
}
