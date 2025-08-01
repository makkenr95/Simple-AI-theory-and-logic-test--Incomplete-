#pragma once
namespace Tga2D
{
	class CSprite;
}

namespace AI
{
	class Controller;
}

class Actor
{
public:
	Actor();
	~Actor();
	void Init(const char* aSpritePath, const float aSpeed, AI::Controller* aAIController, const Tga2D::Vector2f& aStartPosition);
	void Render();
	void Update(const float aDeltaTime);

	const Tga2D::Vector2f& GetPosition() const;
	void SetPosition(const Tga2D::Vector2f& aPosition);

	AI::Controller* GetController();

private:
	Tga2D::Vector2f myPosition;
	Tga2D::CSprite* mySprite;
	AI::Controller* myController;
	float mySpeed;
	float myDirection;
};

