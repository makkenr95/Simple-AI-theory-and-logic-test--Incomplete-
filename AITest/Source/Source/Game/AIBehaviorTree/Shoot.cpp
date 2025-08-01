#include "stdafx.h"
#include "Shoot.h"
#include "../LerpStuff.h"
#include "../Bullet.h"
#include "../GameWorld.h"

void Shoot::Fire()
{
	auto AI1 = PollingStation::GetInstance()->GetAI1();

	myRandomizeProgress += Tga2D::CEngine::GetInstance()->GetDeltaTime();
	float deltaTime = Tga2D::CEngine::GetInstance()->GetDeltaTime();

	if (myRandomizeProgress > myRandomizeDelay)
	{
		myRandomizeProgress = 0;
		auto dir = AI1->GetPosition() - blackboard->GetOwner()->GetPosition();
		dir.Normalize();

		float angle = atan2f(dir.y, dir.x);

		AI2Data::toAngle = angle * Rad2Deg;
		AI2Data::beforeAngle = myAngle;
	}



	float delay = myRandomizeProgress / myRandomizeDelay;
	float lerp = LerpTrue(AI2Data::beforeAngle, AI2Data::toAngle, delay);
	myAngle = lerp;

	Tga2D::Vector2f velocity = { (float)cos(myAngle * Deg2Rad), (float)sin(myAngle * Deg2Rad) };

	velocity.Normalize();
	blackboard->GetOwner()->myRotation = atan2f(velocity.y, velocity.x);

	AI2Data::myBulletTimer -= deltaTime;

	if (AI2Data::myBulletTimer <= 0)
	{
		// Spawn Bullet
		auto* bullet = new Bullet();
		bullet->SetBullet();
		bullet->SetPosition(blackboard->GetOwner()->GetPosition());
		bullet->SetDir(velocity);
		bullet->SetTarget(eTag::AI1);

		AI2Data::myBulletTimer = AI2Data::myBulletCooldown;
	}
}
