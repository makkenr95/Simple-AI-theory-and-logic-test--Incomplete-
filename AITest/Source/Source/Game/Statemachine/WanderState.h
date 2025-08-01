#pragma once
#include "AIState.h"

class AI1;

class WanderState :
    public AIState
{
public:
	WanderState(AI1* aActor);
	virtual ~WanderState() override;

	void Init();

	void OnEnterState() override;
	void OnExitState() override;

	void Update(float aDeltaTime) override;

	bool ShouldTransitionToAttackStateState();
private:
	AI1* myActor = nullptr;

	//float myRandomizeDelay = 0.5f;
	//float myRandomizeProgress = 0;

	//float myAngle = 0;

	//float mySpeed = 0.05f;

	float myRandomizeDelay = 0.5f;
	float myRandomizeProgress = 0;
	float myAngle = 180;
	float mySpeed = 0.05f;
	float myBulletCooldown = .25f;
	float myBulletTimer = .25f;
	float myObstacle = false;
};

