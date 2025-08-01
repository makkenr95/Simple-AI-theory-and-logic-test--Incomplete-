#pragma once

#include <map>

enum class EventType
{
	PlayerStartHacking
};

class EventSubscriber
{
public:
	virtual void ReceiveEvent(EventType aType, void* aPtr) = 0;
};

class EventManager
{
public:
	EventManager();
	~EventManager();
	static EventManager* GetInstance();

	void AddSubscriber(EventSubscriber* aSub, EventType aType);
	void RemoveSubscriber(EventSubscriber* aSub, EventType aType);

	void CallEvent(EventType aType, void* aPtr);

private:
	std::map<EventType, std::vector<EventSubscriber*>> mySubs;

private:
	inline static EventManager* ourInstance = nullptr;
};