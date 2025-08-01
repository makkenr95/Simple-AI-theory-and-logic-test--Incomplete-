#pragma once
#include "AIState.h"

class AI1;
class AIHazmatSuitIdleState;

class AIHazmatSuitPositionState : public AIState
{
public:
	AIHazmatSuitPositionState(AI1* aActor);
	virtual ~AIHazmatSuitPositionState() override;

	void Init();

	void OnEnterState() override;
	void OnExitState() override;

	void Update(float aDeltaTime) override;

	bool ShouldTransitionToAIIdleState();

private:
	AI1* myHazmatSuit = nullptr;

	float myTimer = 0.f;
	float myDuration = 3.f;

	bool myChangeState = false;
};