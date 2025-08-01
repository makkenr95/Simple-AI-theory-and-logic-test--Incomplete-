#include "stdafx.h"
#include "CollisionManager.h"
#include "Statemachine/GameObject.h"

Collider::Collider()
{
	CollisionManager::Get().RegisterCollider(this);
}

Collider::~Collider()
{
	CollisionManager::Get().UnregisterCollider(this);
}

bool CollisionManager::Colliding(Collider* aCollider, std::vector<Collider*>& aHits)
{
	bool result = false;
	for (auto* collider : myColliders)
	{
		if (collider == aCollider)
			continue;

		auto dx = aCollider->x - collider->x;
		auto dy = aCollider->y - collider->y;

		float distance = sqrtf(dx * dx + dy * dy);
		if (distance < collider->radius + aCollider->radius)
		{
			aHits.emplace_back(collider);
			result = true;
		}
	}

	return result;
}

bool CollisionManager::Raycast(float startX, float startY, float dirX, float dirY, float aDistance, unsigned int aLayer, float aStep)
{
	bool result = false;
	float distTraveled = 0;

	while (distTraveled < aDistance)
	{
		distTraveled += aStep;
		auto x = startX + dirX * distTraveled, y = startY + dirY * distTraveled;
		for (auto* collider : myColliders)
		{
			if (!(collider->tag == aLayer))
				continue;

			auto dx = x - collider->x;
			auto dy = y - collider->y;

			float distance = sqrtf(dx * dx + dy * dy);
			if (distance < collider->radius + 0.01f)
			{
				result = true;
				Tga2D::CDebugDrawer::DrawCircle({ x,y }, 0.012f, {1, 0, 0, 1});
			}

			if (aLayer == eTag::Obstacle)
			{
				if (x < 0.f || x > 1.f || y < 0.f || y > 1.f)
				{
					result = true;
					Tga2D::CDebugDrawer::DrawCircle({ x,y }, 0.012f, { 1, 0, 0, 1 });
				}
			}

		}

		Tga2D::CDebugDrawer::DrawCircle({ x,y }, 0.01f);
	}

	return result;
}

void CollisionManager::UnregisterCollider(Collider* aCollider)
{
	auto found = std::find(myColliders.begin(), myColliders.end(), aCollider);

	if (found != myColliders.end())
	{
		myColliders.erase(found);
	}
}
