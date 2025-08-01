#pragma once

#include "Controller.h"
#include <tga2d/math/vector2.h>
#include "EventManager.h"

class EventController : public AI::Controller, public EventSubscriber
{
public:
	EventController();
	~EventController();

	Tga2D::Vector2f Update(const Tga2D::Vector2f& aPosition) override;

	void ReceiveEvent(EventType aType, void* aPtr) override;

private:
	bool hasFoundPosition = false;
	Tga2D::Vector2f myTargetPosition = { 0, 0 };
};