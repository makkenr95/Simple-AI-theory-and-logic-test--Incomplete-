#include "stdafx.h"
#include "AIHazmatSuitIdleState.h"

#include "AI1.h"

AIHazmatSuitIdleState::AIHazmatSuitIdleState(AI1* aActor) :
	AIState(aActor)
{
	myHazmatSuit = aActor;
}

AIHazmatSuitIdleState::~AIHazmatSuitIdleState()
{
}

void AIHazmatSuitIdleState::Init()
{
	SetStateName("AIHazmatSuitIdleState");
}

void AIHazmatSuitIdleState::OnEnterState()
{
}

void AIHazmatSuitIdleState::OnExitState()
{
}

void AIHazmatSuitIdleState::Update(float aDeltaTime)
{
	myTimer += aDeltaTime;
	if (myTimer >= myDuration)
	{
		myChangeState = true;
		myTimer = 0.f;
	}
}

bool AIHazmatSuitIdleState::ShouldTransitionToAIPositionState()
{
	if (myChangeState)
	{
		myChangeState = false;
		return true;
	}

	return false;
}
