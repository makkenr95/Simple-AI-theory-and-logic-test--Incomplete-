#pragma once
#include <string>

class Collider;

struct eTag
{
	enum Enum
	{
		Default =	(1 << 0),
		AI1 =	(1 << 1),
		AI2 =		(1 << 2),
		Obstacle =	(1 << 3),
	};
};

namespace Tga2D
{
	class CSprite;
	class CText;
};

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Update(float aDeltaTime);
	virtual void Render();

	void SetActive(const bool aIsActive);
	void SetName(const std::string& aName);

	Tga2D::CSprite* GetSprite() { return mySprite; }
	void SetSprite(Tga2D::CSprite* aSprite) { mySprite = aSprite; }

	[[nodiscard]] const bool IsActive() const;
	[[nodiscard]] const std::string GetName() const;

	float GetRadius() const { return myRadius; }
	const Tga2D::Vector2f& GetPosition() { return myPosition; }

	void SetPosition(const Tga2D::Vector2f& aPos);
	void Move(const Tga2D::Vector2f& aMovement);

	Collider* GetCollider() { return myCollider; }
	void SetCollider(Collider* aCollider) { myCollider = aCollider; }

	void SetHp(int aHp) { myHP = aHp; }
	int GetHp() const { return myHP; }

	void SetBullet();
protected:
	friend class Scene;

	Collider* myCollider = nullptr;

	bool myIsBullet = false;
	Tga2D::Vector2f myPosition;
	float myRadius = .1f;

	bool myIsActive = true;
	std::string myName = "GameObject";
	Tga2D::CSprite* mySprite = nullptr;
	Tga2D::CText* myText = nullptr;

	int myHP = 25;

public:
	float myRotation = 0.f;
};

