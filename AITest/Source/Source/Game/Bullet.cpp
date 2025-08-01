#include "stdafx.h"
#include "Bullet.h"
#include "tga2d/drawers/debug_drawer.h"

Bullet::Bullet()
{
	ourBullets.emplace_back(this);
	myCollider = new Collider();
	myCollider->radius = .006f;
}

Bullet::~Bullet()
{
	auto it = std::find(ourBullets.begin(), ourBullets.end(), this);
	if (it != ourBullets.end())
	{
		ourBullets.erase(it);
	}
}

void Bullet::Update(float aDeltaTime)
{
	GameObject::Update(aDeltaTime);

	const float speed = .5f;
	Move(myDir * aDeltaTime * speed);
	std::vector<Collider*> hits;
	if (CollisionManager::Get().Colliding(myCollider, hits))	
	{
		for (auto* hit : hits)
		{
			if (hit->tag == myTarget)
			{
				auto obj = hit->gameobject;
				if (obj)
				{
					obj->SetHp(obj->GetHp() - 1);
				}
				auto it = std::find(ourBullets.begin(), ourBullets.end(), this);
				if (it != ourBullets.end())
				{
					ourBullets.erase(it);
				}
			}

			if (hit->tag == eTag::Obstacle)
			{
				auto it = std::find(ourBullets.begin(), ourBullets.end(), this);
				if (it != ourBullets.end())
				{
					ourBullets.erase(it);
				}
			}
		}
	}

	if (myPosition.x < -1.f || myPosition.x > 2.f || myPosition.y < -1.f || myPosition.y > 2.f)
	{
		auto it = std::find(ourBullets.begin(), ourBullets.end(), this);
		if (it != ourBullets.end())
		{
			ourBullets.erase(it);
		}
	}

	Tga2D::CDebugDrawer::DrawCircle(myPosition, myCollider->radius);
}
