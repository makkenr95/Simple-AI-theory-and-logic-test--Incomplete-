#include "stdafx.h"
#include "EventController.h"
#include "Actor.h"

EventController::EventController()
{
	EventManager::GetInstance()->AddSubscriber(this, EventType::PlayerStartHacking);
}

EventController::~EventController()
{
	EventManager::GetInstance()->RemoveSubscriber(this, EventType::PlayerStartHacking);
}

Tga2D::Vector2f EventController::Update(const Tga2D::Vector2f& aPosition)
{
	if (!hasFoundPosition)
	{
		return { 0, 0 };
	}

	return (myTargetPosition - aPosition).Normalize();
}

void EventController::ReceiveEvent(EventType aType, void* aPtr)
{
	if (aType == EventType::PlayerStartHacking)
	{
		hasFoundPosition = true;
		const Actor* computer = (const Actor*)aPtr;

		myTargetPosition = computer->GetPosition();
	}
}
