#pragma once

#include <string>
#include <unordered_map>
#include <vector>

class GameObject;

class Event {

public:
	Event(std::string eventType) {		
		mEventType = eventType;
		mTimer = 0.0f;
	}

public:
	std::string mEventType;
	float mTimer;
};

class EventManager
{

public:
	EventManager() {};
	~EventManager() {};

	void Subscribe(std::string eventType, GameObject* pSubscriber);
	void UnsubscribeDestroyedObjects();
	
	void BroadcastEvent(Event* pEvent);
	void BroadcastEventToSubscribers(Event* pEvent);
	void AddTimedEvent(Event* pEvent);
	void Update(float frameTime);

	void DisplayMap();

private:
	std::vector <Event*> mListOfEvents;
	std::unordered_map <std::string, std::vector<GameObject*>> mSubscribers;
};

