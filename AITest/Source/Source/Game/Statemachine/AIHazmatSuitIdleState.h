#pragma once
#include <string>

#include "AIState.h"

class AI1;
class AIHazmatSuitPositionState;

class AIHazmatSuitIdleState : public AIState
{
public:
	AIHazmatSuitIdleState(AI1* aActor);
	virtual ~AIHazmatSuitIdleState() override;

	void Init();

	void OnEnterState() override;
	void OnExitState() override;

	void Update(float aDeltaTime) override;

	bool ShouldTransitionToAIPositionState();

private:
	AI1* myHazmatSuit = nullptr;

	float myTimer = 0.f;
	float myDuration = 3.f;

	bool myChangeState = false;
};

