#include "stdafx.h"
#include "SeekController.h"
#include "PollingStation.h"
#include "WanderController.h"
#include "Actor.h"

float SeekController::Lerp(const float a, const float b, const float aTime)
{
	float aa = a * (1 - aTime);
	float bb = b * aTime;
	return aa + bb;
}

SeekController::SeekController()
{
}

Tga2D::Vector2f SeekController::Update(const Tga2D::Vector2f& aPosition)
{
	Tga2D::Vector2f targetPos = { 0, 0 };

	for (auto val : PollingStation::GetInstance()->GetActors())
	{
		if (dynamic_cast<WanderController*>(val->GetController()))
		{
			targetPos = val->GetPosition();
		}
	}

	targetPos = targetPos - aPosition;
	float targetAngle = atan2f(targetPos.y, targetPos.x);

	myAngleToPlayer = Lerp(myAngleToPlayer, targetAngle, 0.0005f);

	return Tga2D::Vector2f{cos(myAngleToPlayer), sin(myAngleToPlayer)};
}
