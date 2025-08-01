#pragma once
#include "AIState.h"

class AI1;

class AttackState :
	public AIState
{
public:
	AttackState(AI1* aActor);
	virtual ~AttackState() override;

	void Init();

	void OnEnterState() override;
	void OnExitState() override;

	void Update(float aDeltaTime) override;

	bool ShouldTransitionHealStateState();
	bool ShouldTransitionWanderStateState();
private:
	AI1* myActor = nullptr;

	float myRandomizeDelay = 0.5f;
	float myRandomizeProgress = 0;

	float myAngle = 0;
};

