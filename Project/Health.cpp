#include "Health.h"
#include "GameObject.h"
#include "GameObjectFactory.h"

extern GameObjectFactory* gpGameObjectFactory;

void Health::HandleEvent(Event* pEvent) {

	if (pEvent->mEventType == "ENEMY HITS RED LINE") {
		if (mpGameObjectOwner->mType == "Player") {
			mHealth--;
		}
		if (mpGameObjectOwner->mType == "Enemy") {
			mHealth++;
		}
	}

	if (pEvent->mEventType == "PLAYER HIT ENEMY!") {
		if (mpGameObjectOwner->mType == "Enemy") {
			mpGameObjectOwner->mDestroyed = true;
		}
		else {
			mHealth--;
		}
	}

	if (pEvent->mEventType == "ENEMY BULLET HITS PLAYER") {
		if (mpGameObjectOwner->mType == "Enemy Bullet") {
			mpGameObjectOwner->mDestroyed = true;
		}
		else {
			mHealth--;
		}
	}


	if (pEvent->mEventType == "BEAM HIT ENEMY" && mpGameObjectOwner->mType == "Enemy") {
		mpGameObjectOwner->mDestroyed = true;
	}

	if (mpGameObjectOwner->mType == "Enemy") {
		mHealth--;
	}

	if (pEvent->mEventType == "PLAYER GETS HEART") {
		mHealth++;
	}

	if (mHealth == 0) {
		mpGameObjectOwner->mDestroyed = true;
		if (mpGameObjectOwner->mName == "Player") {
			gpGameObjectFactory->BuildObject("Death Text.json");
		}
	}
}