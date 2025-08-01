#include "stdafx.h"
#include "SeparationController.h"
#include "PollingStation.h"
#include "Actor.h"

SeparationController::SeparationController()
{

}

float DistanceSqr(const Tga2D::Vector2f& aFirst, const Tga2D::Vector2f& aSecond)
{
	float x = aFirst.x - aSecond.x;
	float y = aFirst.y - aSecond.y;
	return x * x + y * y;
}

Tga2D::Vector2f SeparationController::Update(const Tga2D::Vector2f& aPosition)
{
	auto entities = PollingStation::GetInstance()->GetActors();

	Tga2D::Vector2f velocity = { 0, 0 };
	for (auto ent : entities)
	{
		if (ent->GetPosition() == aPosition)
			continue;

		float distSqr = DistanceSqr(aPosition, ent->GetPosition());

		if (distSqr < myThreshhold)
		{
			Tga2D::Vector2f dir = aPosition - ent->GetPosition();
			velocity += dir * distSqr;
		}
	}

	return velocity.Normalize();
}
