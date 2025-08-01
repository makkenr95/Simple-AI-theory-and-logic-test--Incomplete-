#pragma once
#include <vector>

class GameObject;

class Collider
{
public:
	Collider();
	~Collider();

	GameObject* gameobject = nullptr;
	float x, y;
	float radius;
	unsigned int tag;
};

class CollisionManager
{
public:
	bool	Colliding(Collider* aCollider, std::vector<Collider*>& aHits);
	bool	Raycast(float startX, float startY, float dirX, float dirY, float aDistance, unsigned int aLayer, float aStep = .015f);
			
	void	RegisterCollider(Collider* aCollider) { myColliders.emplace_back(aCollider); }
	void	UnregisterCollider(Collider* aCollider);

	static CollisionManager& Get() { static CollisionManager inst; return inst; }
private:
	std::vector<Collider*> myColliders;
};

