#include "stdafx.h"
#include "Actor.h"
#include <tga2d/sprite/sprite.h>
#include "Controller.h"
#include <assert.h>

Actor::Actor()
{
	mySpeed = 0.f;
	myController = nullptr;
	mySprite = nullptr;
	myPosition.Set(0.f, 0.f);
	myDirection = 0.f;
}

Actor::~Actor()
{
	delete mySprite;
	mySprite = nullptr;

	if (myController)
	{
		delete myController;
		myController = nullptr;
	}
}

void Actor::Init(const char* aSpritePath, const float aSpeed, AI::Controller* aAIController, const Tga2D::Vector2f& aStartPosition)
{
	mySprite = new Tga2D::CSprite(aSpritePath);
	mySprite->SetPivot({ 0.5f, 0.5f });
	mySpeed = aSpeed;
	myController = aAIController;
	myPosition = aStartPosition;
}

void Actor::Render()
{
	assert(mySprite != nullptr && "Sprite is nullptr. Actor might not be initiated properly. Run Init first.");
	mySprite->SetPosition(myPosition);
	mySprite->SetRotation(myDirection);
	mySprite->Render();
}

void Actor::Update(const float aDeltaTime)
{
	if (!myController)
		return;

	if (myPosition.x > 1)
		myPosition.x = 0;

	if (myPosition.x < 0)
		myPosition.x = 1;

	if (myPosition.y > 1)
		myPosition.y = 0;

	if (myPosition.y < 0)
		myPosition.y = 1;

	Tga2D::Vector2f direction = myController->Update(myPosition);
	if (direction.x != 0.f && direction.y != 0.f) // Is not zero vector
	{
		direction.Normalize();
		myPosition += direction * mySpeed * aDeltaTime;
		myDirection = atan2f(direction.y, direction.x);
	}
}

const Tga2D::Vector2f& Actor::GetPosition() const
{
	return myPosition;
}

void Actor::SetPosition(const Tga2D::Vector2f& aPosition)
{
	myPosition = aPosition;
}

AI::Controller* Actor::GetController()
{
	return myController;
}
