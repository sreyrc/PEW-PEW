#include <SDL.h>
#include "Controller.h"
#include "GameObject.h"
#include "Transform.h"
#include "EventManager.h"
#include "WorldVariables.h"

#include "Component.h"
#include "InputManager.h"
#include "FrameRateController.h"
#include "GameObjectManager.h"
#include "GameObjectFactory.h"
#include "Renderer.h"

extern InputManager* gpInputManager;
extern FrameRateController* gpFrameRateController;
extern EventManager* gpEventManager;
extern GameObjectManager* gpGameObjectManager;
extern GameObjectFactory* gpGameObjectFactory;
extern Renderer* gpRenderer;

void Controller::Update()
{
	if (gpInputManager->IsKeyPressed(SDL_SCANCODE_UP) || gpInputManager->IsKeyPressed(SDL_SCANCODE_W)) {
		mpGameObjectOwner->GetComponent<Transform>()->mPos.y -= 200 * gpFrameRateController->GetDeltaTime();
	}

	if (gpInputManager->IsKeyPressed(SDL_SCANCODE_DOWN) || gpInputManager->IsKeyPressed(SDL_SCANCODE_S)) {
		mpGameObjectOwner->GetComponent<Transform>()->mPos.y += 200 * gpFrameRateController->GetDeltaTime();
	}

	if (gpInputManager->IsKeyPressed(SDL_SCANCODE_LEFT) || gpInputManager->IsKeyPressed(SDL_SCANCODE_A)) {
		mpGameObjectOwner->GetComponent<Transform>()->mPos.x -= 200 * gpFrameRateController->GetDeltaTime();
		mpGameObjectOwner->GetComponent<Transform>()->mRotation = -20;
	}

	if (gpInputManager->IsKeyPressed(SDL_SCANCODE_RIGHT) || gpInputManager->IsKeyPressed(SDL_SCANCODE_D)) {
		mpGameObjectOwner->GetComponent<Transform>()->mPos.x += 200 * gpFrameRateController->GetDeltaTime();
		mpGameObjectOwner->GetComponent<Transform>()->mRotation = 20;
	}

	if (gpInputManager->IsKeyReleased(SDL_SCANCODE_LEFT) || gpInputManager->IsKeyReleased(SDL_SCANCODE_A) ||
		gpInputManager->IsKeyReleased(SDL_SCANCODE_RIGHT) || gpInputManager->IsKeyReleased(SDL_SCANCODE_D) ) {
		mpGameObjectOwner->GetComponent<Transform>()->mRotation = 0.0f;
	}

	if (gpInputManager->IsKeyTriggered(SDL_SCANCODE_SPACE) && WorldVariables::timeTillCanShootBullet <= 0.0f) {

		GameObject* newBullet = gpGameObjectFactory->BuildObject("Bullet.json");
		newBullet->mName = "Bullet " + std::to_string(++WorldVariables::bulletCount);
		newBullet->GetComponent<Transform>()->mPos = mpGameObjectOwner->GetComponent<Transform>()->mPos;
		newBullet->GetComponent<Transform>()->mRotation = mpGameObjectOwner->GetComponent<Transform>()->mRotation;

		WorldVariables::timeTillCanShootBullet = 0.2f;
	}

	if (gpInputManager->IsKeyTriggered(SDL_SCANCODE_K)
		&& WorldVariables::timeTillCanShootBeam <= 0.0f
		&& mpGameObjectOwner->GetComponent<BeamAmmo>()->mAmmo > 0) {

		Event newEvent("PLAYER SHOOTS BEAM");
		gpEventManager->BroadcastEventToSubscribers(&newEvent);

		std::cout << mpGameObjectOwner->GetComponent<BeamAmmo>()->mAmmo << std::endl;

		GameObject* newBeam = gpGameObjectFactory->BuildObject("Beam.json");
		newBeam->GetComponent<Transform>()->mPos = mpGameObjectOwner->GetComponent<Transform>()->mPos;

		WorldVariables::timeTillCanShootBeam = 5.0f;
	}

	if (gpInputManager->IsKeyTriggered(SDL_SCANCODE_TAB)) {
		gpRenderer->ToggleDebugMode();
	}
}
