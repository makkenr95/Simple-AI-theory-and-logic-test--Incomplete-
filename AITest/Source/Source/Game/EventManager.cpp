#include "stdafx.h"
#include "EventManager.h"

EventManager::EventManager()
{
	ourInstance = this;
}

EventManager::~EventManager()
{
	ourInstance = nullptr;
}

EventManager* EventManager::GetInstance()
{
	return ourInstance;
}

void EventManager::AddSubscriber(EventSubscriber* aSub, EventType aType)
{
	mySubs[aType].push_back(aSub);
}

void EventManager::RemoveSubscriber(EventSubscriber* aSub, EventType aType)
{
	mySubs[aType].erase(std::remove(mySubs[aType].begin(), mySubs[aType].end(), aSub));
}

void EventManager::CallEvent(EventType aType, void* aPtr)
{
	for (auto sub : mySubs[aType])
	{
		sub->ReceiveEvent(aType, aPtr);
	}
}
