#include "stdafx.h"
#include "DummyController.h"

AI::DummyController::DummyController()
{
	CreateRandomTargetPosition();
}

Tga2D::Vector2f AI::DummyController::Update(const Tga2D::Vector2f& aPosition)
{
	if ((abs(aPosition.x - myTargetPosition.x) + abs(aPosition.y - myTargetPosition.y)) < 0.05f * 0.05f) // squared distance test
	{
		CreateRandomTargetPosition();
	}

	return myTargetPosition - aPosition;
}

void AI::DummyController::CreateRandomTargetPosition()
{
	myTargetPosition.x = (rand() % 100) / 100.f;
	myTargetPosition.y = (rand() % 100) / 100.f;
}
