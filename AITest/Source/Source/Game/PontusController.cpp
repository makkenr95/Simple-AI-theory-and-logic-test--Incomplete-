#include "stdafx.h"
#include "PontusController.h"
#include "PollingStation.h"
#include "Actor.h"

#define Deg2Rad 0.0174532925 

float Lerp(const float a, const float b, const float aTime)
{
	float aa = a * (1 - aTime);
	float bb = b * aTime;
	return aa + bb;
}

Tga2D::Vector2f Lerp(const Tga2D::Vector2f& a, const Tga2D::Vector2f& b, const float aTime)
{
	return Tga2D::Vector2f{ Lerp(a.x, b.x, aTime), Lerp(a.y, b.y, aTime) };
}

extern float globalSeparationRange = 0.25f;
extern float globalCohesionRange = 0.35f;
extern float globalVMatchingRange = 0.3;

extern float globalWanderingMultiplier = .0f;
extern float globalSeparationMultiplier = 0.7f;
extern float globalCohesionMultiplier = .05f;
extern float globalVMatchingMultiplier = .1f;

PontusController::PontusController()
{
	myPreviousVelocity = Tga2D::Vector2f{ (float)rand() / RAND_MAX - RAND_MAX * .5f, (float)rand() / RAND_MAX - RAND_MAX * .5f }.Normalize();
}

Tga2D::Vector2f PontusController::Update(const Tga2D::Vector2f& aPosition)
{
	myPosition = aPosition;

	Tga2D::Vector2f separation = Separation() * globalSeparationMultiplier;
	Tga2D::Vector2f cohesion = Cohesion() * globalCohesionMultiplier;
	Tga2D::Vector2f vMatching = VMatching() * globalVMatchingMultiplier;

	Tga2D::CDebugDrawer::DrawArrow(myPosition, myPosition + separation, { 1, 0, 0, .3f }, .5f);
	Tga2D::CDebugDrawer::DrawArrow(myPosition, myPosition + cohesion, { 0, 1, 0, .3f }, .5f);
	Tga2D::CDebugDrawer::DrawArrow(myPosition, myPosition + vMatching, { 0, 0, 1, .3f }, .5f);

	auto vel = separation + cohesion + vMatching;
	if (vel.Length() <= .005f)
		return myPreviousVelocity;

	float time = 2 * Tga2D::CEngine::GetInstance()->GetDeltaTime();

	auto newVel = Lerp(myPreviousVelocity, vel, time);

	myPreviousVelocity = newVel;
	return myPreviousVelocity;
}

Tga2D::Vector2f PontusController::Separation()
{
	Tga2D::Vector2f direction;

	for (auto* actor : PollingStation::GetInstance()->GetActors())
	{
		float distance = (actor->GetPosition() - myPosition).Length();

		if (distance < globalSeparationRange)
		{
			Tga2D::Vector2f dir = myPosition - actor->GetPosition();
			float invDist = globalSeparationRange - distance;

			float pow = powf(invDist / globalSeparationRange, 2.5f);

			direction += dir.Normalize() * invDist * pow;
		}
	}

	return direction;
}

Tga2D::Vector2f PontusController::Cohesion()
{
	Tga2D::Vector2f direction;

	for (auto* actor : PollingStation::GetInstance()->GetActors())
	{
		float distance = (actor->GetPosition() - myPosition).Length();

		if (distance < globalCohesionRange)
		{
			Tga2D::Vector2f dir = actor->GetPosition() - myPosition;
			direction += dir;
		}
	}

	return direction;
}

Tga2D::Vector2f PontusController::VMatching()
{
	Tga2D::Vector2f direction;

	for (auto* actor : PollingStation::GetInstance()->GetActors())
	{
		float distance = (actor->GetPosition() - myPosition).Length();

		if (distance < globalVMatchingRange)
		{
			if (PontusController* controller = dynamic_cast<PontusController*>(actor->GetController()))
			{
				direction += controller->myPreviousVelocity;
			}
		}
	}
	if (direction.Length() < 1.f)
	{
		return direction;
	}
	return direction.Normalize();
}

Tga2D::Vector2f PontusController::Wandering()
{
	myRandomizeProgress += Tga2D::CEngine::GetInstance()->GetDeltaTime();

	if (myRandomizeProgress > myRandomizeDelay)
	{
		myRandomizeProgress = 0;
		float randomVal = (float)(rand() % 90) - 45.0f;
		myToAngle = myAngle + randomVal;
		myBeforeAngle = myAngle;
	}

	float delay = myRandomizeProgress / myRandomizeDelay;
	float lerp = Lerp(myBeforeAngle, myToAngle, delay);
	myAngle = lerp;

	Tga2D::Vector2f velocity = { (float)cos(myAngle * Deg2Rad), (float)sin(myAngle * Deg2Rad) };

	return velocity;
}
