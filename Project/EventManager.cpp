#include "EventManager.h"
#include "GameObjectManager.h"

extern GameObjectManager* gpGameObjectManager;

void EventManager::Subscribe(std::string eventType, GameObject* pSubscriber)
{
	if (!mSubscribers[eventType].empty()) {
		for (GameObject* subscriber : mSubscribers[eventType]) {
			if (subscriber == pSubscriber) {
				return;
			}
		}
	}

	mSubscribers[eventType].push_back(pSubscriber);
}

void EventManager::UnsubscribeDestroyedObjects()
{
	for (auto it = mSubscribers.begin(); it != mSubscribers.end();) {

		std::vector<GameObject*>* vec = &it->second;
		for (int i = 0; i < vec->size();) {
			
			if (vec->at(i)->mDestroyed == true) {
				vec->erase(vec->begin() + i);
			}
			else i++;
		}

		if (vec->empty()) {
			it = mSubscribers.erase(it);
		}
		else { it++; }
		
	}
	
}

void EventManager::BroadcastEvent(Event* pEvent)
{
	auto pAllGameObjects = gpGameObjectManager->GetGameObjectList();
	for (auto it = (*pAllGameObjects).begin(); it != (*pAllGameObjects).end(); it++) {
		(*it)->HandleEvent(pEvent);
	}
}

void EventManager::BroadcastEventToSubscribers(Event* pEvent)
{
	if (!mSubscribers[pEvent->mEventType].empty()) {
		for (auto it = mSubscribers[pEvent->mEventType].begin(); it != mSubscribers[pEvent->mEventType].end(); it++) {
			(*it)->HandleEvent(pEvent);
		}
	}
}

void EventManager::AddTimedEvent(Event* pEvent)
{
	mListOfEvents.push_back(pEvent);
}

void EventManager::Update(float deltaTime)
{
	if (!mListOfEvents.empty())
	{
		for (int i = 0; i < mListOfEvents.size();) {

			Event* pEvent = mListOfEvents[i];
			pEvent->mTimer -= deltaTime;

			if (pEvent->mTimer < 0.0f) {
				BroadcastEventToSubscribers(pEvent);
				delete pEvent;
				mListOfEvents.erase(mListOfEvents.begin() + i);
			}
			else i++;
		}
	}
}

void EventManager::DisplayMap()
{
	for (auto const& [key, val] : mSubscribers) {
		std::cout << key << ": \t";
		for (auto it = val.begin(); it != val.end(); it++) {
			std::cout << (*it)->mName << ", ";
		}
		std::cout << std::endl;
	}

}
