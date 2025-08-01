#pragma once
#include "AIState.h"

class AI1;

class HealState :
	public AIState
{
public:
	HealState(AI1* aActor);
	virtual ~HealState() override;

	void Init();

	void OnEnterState() override;
	void OnExitState() override;

	void Update(float aDeltaTime) override;

	bool ShouldTransitionToWanderState();
private:
	AI1* myActor = nullptr;

	float myRandomizeDelay = 0.5f;
	float myRandomizeProgress = 0;

	float myAngle = 0;

	bool myShouldTransToWander = false;
};

