#include "stdafx.h"
#include "AttackState.h"
#include "AI1.h"
#include "../LerpStuff.h"
#include "../PollingStation.h"
#include "../Bullet.h"

#define Deg2Rad 0.0174532925 

AttackState::AttackState(AI1* aActor)
	: AIState(aActor)
{
	myActor = aActor;
}

AttackState::~AttackState()
{
}

void AttackState::Init()
{
	SetStateName("Attack");

}

void AttackState::OnEnterState()
{
}

void AttackState::OnExitState()
{
}

void AttackState::Update(float aDeltaTime)
{
	auto AI2 = PollingStation::GetInstance()->GetAI2();

	myRandomizeProgress += Tga2D::CEngine::GetInstance()->GetDeltaTime();
	
	if (myRandomizeProgress > myRandomizeDelay)
	{
		myRandomizeProgress = 0;
		auto dir = AI2->GetPosition() - myActor->GetPosition();
		dir.Normalize();

		float angle = atan2f(dir.y, dir.x);

		AI1Data::toAngle = angle * Rad2Deg;
		AI1Data::beforeAngle = myAngle;
	}



	float delay = myRandomizeProgress / myRandomizeDelay;
	float lerp = LerpTrue(AI1Data::beforeAngle, AI1Data::toAngle, delay);
	myAngle = lerp;

	Tga2D::Vector2f velocity = { (float)cos(myAngle * Deg2Rad), (float)sin(myAngle * Deg2Rad) };

	velocity.Normalize();
	myActor->myRotation = atan2f(velocity.y, velocity.x);

	AI1Data::myBulletTimer -= aDeltaTime;

	if (AI1Data::myBulletTimer <= 0)
	{
		// Spawn Bullet
		auto* bullet = new Bullet();
		bullet->SetBullet();
		bullet->SetPosition(myActor->GetPosition());
		bullet->SetDir(velocity);
		bullet->SetTarget(eTag::AI2);

		AI1Data::myBulletTimer = AI1Data::myBulletCooldown;
	}

}

bool AttackState::ShouldTransitionHealStateState()
{
	Tga2D::Vector2f healingPos(.6f, .3f);

	auto dir = healingPos - myActor->GetPosition();

	auto length = dir.Length();

	if (length < .15f)
	{
		return false;
	}

	if (myActor->GetHp() < 25)
	{
		return true;
	}
	return false;
}

bool AttackState::ShouldTransitionWanderStateState()
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
			return true;
		}
		return false;
	}

	return true;
}
