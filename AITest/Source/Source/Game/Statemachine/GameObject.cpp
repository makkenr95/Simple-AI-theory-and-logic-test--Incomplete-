#include "stdafx.h"
#include "GameObject.h"

#include "../CollisionManager.h"
#include "tga2d/sprite/sprite.h"
#include "tga2d/text/text.h"

GameObject::GameObject()
{
	mySprite = new Tga2D::CSprite("Sprites/robot.png");
	mySprite->SetPivot({0.5f, 0.5f});

	myText = new Tga2D::CText();
}

GameObject::~GameObject()
{
}

void GameObject::Update(float aDeltaTime)
{
	if (mySprite)
	{
		mySprite->SetRotation(myRotation);
	}

	if (myCollider)
	{
		myCollider->x = myPosition.x;
		myCollider->y = myPosition.y;

		Tga2D::CDebugDrawer::DrawCircle(myPosition, myCollider->radius);
	}
}

void GameObject::Render()
{
	if (!mySprite)
		return;

	mySprite->SetPosition(myPosition);
	mySprite->Render();
	if (myIsBullet)
		return;
	
	myText->SetText(std::to_string(myHP));
	myText->SetPosition(myPosition + Tga2D::Vector2f{ 0.02f, 0.0f });
	myText->Render();
}

void GameObject::SetActive(const bool aIsActive)
{
	myIsActive = aIsActive;
}

void GameObject::SetName(const std::string& aName)
{
	myName = aName;
}

const bool GameObject::IsActive() const
{
	return myIsActive;
}

const std::string GameObject::GetName() const
{
	return myName;
}

void GameObject::SetPosition(const Tga2D::Vector2f& aPos)
{
	myPosition = aPos;
}

void GameObject::Move(const Tga2D::Vector2f& aMovement)
{
	myPosition += aMovement;
}

void GameObject::SetBullet()
{
	myIsBullet = true;
	mySprite = new Tga2D::CSprite("Sprites/computer.png");
	mySprite->SetPivot({ 0.5f, 0.5f });
	mySprite->SetSizeRelativeToImage({ .3f, .3f });
}
