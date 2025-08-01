#include "stdafx.h"
#include "WanderState.h"
#include "AI1.h"
#include "../CollisionManager.h"
#include "../PollingStation.h"
#include "../LerpStuff.h"

#define Deg2Rad 0.0174532925 

float Lerp2(const float a, const float b, const float aTime)
{
	float aa = a * (1 - aTime);
	float bb = b * aTime;
	return aa + bb;
}

WanderState::WanderState(AI1* aActor)
	: AIState(aActor)
{
	myActor = aActor;
}

WanderState::~WanderState()
{
}

void WanderState::Init()
{
	SetStateName("wander");
}

void WanderState::OnEnterState()
{
}

void WanderState::OnExitState()
{
}

void WanderState::Update(float aDeltaTime)
{
	AI1Data::myRandomizeProgress += aDeltaTime;

	{
		Tga2D::Vector2f velocity = { (float)cos(AI1Data::myAngle * Deg2Rad), (float)sin(AI1Data::myAngle * Deg2Rad) };
		auto start = myActor->GetPosition();
		if (CollisionManager::Get().Raycast(start.x, start.y, velocity.x, velocity.y, .1f, eTag::Obstacle))
		{
			AI1Data::toAngle += 45.f * aDeltaTime;
			AI1Data::mySpeed = 0.001f;
			AI1Data::myObstacle = true;
		}
		else
		{
			AI1Data::mySpeed = 0.05f;
			if (AI1Data::myRandomizeProgress > AI1Data::myRandomizeDelay)
			{
				AI1Data::myRandomizeProgress = 0;
				AI1Data::beforeAngle = AI1Data::myAngle;

				if (AI1Data::myObstacle)
				{
					AI1Data::myObstacle = false;
					return;
				}


				float randomVal = (float)(rand() % 90) - 45.0f;
				AI1Data::toAngle = AI1Data::myAngle + randomVal;
				AI1Data::beforeAngle = AI1Data::myAngle;
			}
		}
	}

	float delay = AI1Data::myRandomizeProgress / AI1Data::myRandomizeDelay;
	float lerp = LerpTrue(AI1Data::beforeAngle, AI1Data::toAngle, delay);

	AI1Data::myAngle = lerp;

	Tga2D::Vector2f velocity = { (float)cos(AI1Data::myAngle * Deg2Rad), (float)sin(AI1Data::myAngle * Deg2Rad) };

	myActor->Move(velocity * aDeltaTime * AI1Data::mySpeed);


	velocity.Normalize();

	//myPosition += velocity * mySpeed * aDeltaTime;
	myActor->myRotation = atan2f(velocity.y, velocity.x);

	//myRandomizeProgress += Tga2D::CEngine::GetInstance()->GetDeltaTime();

	//static float toAngle = 0;
	//static float beforeAngle = 0;
	//if (myRandomizeProgress > myRandomizeDelay)
	//{
	//	myRandomizeProgress = 0;
	//	float randomVal = (float)(rand() % 90) - 45.0f;
	//	toAngle = myAngle + randomVal;
	//	beforeAngle = myAngle;
	//}

	//float delay = myRandomizeProgress / myRandomizeDelay;
	//float lerp = Lerp2(beforeAngle, toAngle, delay);
	//myAngle = lerp;

	//Tga2D::Vector2f velocity = { (float)cos(myAngle * Deg2Rad), (float)sin(myAngle * Deg2Rad) };

	//myActor->Move(velocity * aDeltaTime * mySpeed);
	//

	//velocity.Normalize();
	////myPosition += velocity * mySpeed * aDeltaTime;
	//myActor->myRotation = atan2f(velocity.y, velocity.x);

}

bool WanderState::ShouldTransitionToAttackStateState()
{
	auto AI2 = PollingStation::GetInstance()->GetAI2();

	auto dir = myActor->GetPosition() - AI2->GetPosition();
	auto dist = std::sqrt(dir.x * dir.x + dir.y * dir.y);

	//Tga2D::CDebugDrawer::DrawArrow(AI2->GetPosition(), AI2->GetPosition() + dir * dist, {1, 0, 0, 1});

	dir.Normalize();
	if ((dist < .6f))
	{
		auto start = AI2->GetPosition();
		if (CollisionManager::Get().Raycast(start.x, start.y, dir.x, dir.y, dist, eTag::Obstacle))
		{
			return false;
		}
		return true;
	}

	return false;
}
