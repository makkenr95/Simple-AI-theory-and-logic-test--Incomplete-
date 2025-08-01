#include "stdafx.h"
#include "AIHazmatSuitPositionState.h"
#include "AIHazmatSuitIdleState.h"
#include "AI1.h"

AIHazmatSuitPositionState::AIHazmatSuitPositionState(AI1* aActor) :
AIState(aActor)
{
	myHazmatSuit = aActor;
}

AIHazmatSuitPositionState::~AIHazmatSuitPositionState()
{
}

void AIHazmatSuitPositionState::Init()
{
	SetStateName("AIHazmatSuitPositionState");
}

void AIHazmatSuitPositionState::OnEnterState()
{

}

void AIHazmatSuitPositionState::OnExitState()
{

}

void AIHazmatSuitPositionState::Update(float aDeltaTime)
{

	myTimer += aDeltaTime;
	if (myTimer >= myDuration)
	{
		myChangeState = true;
		myTimer = 0.f;
	}
}

bool AIHazmatSuitPositionState::ShouldTransitionToAIIdleState()
{
	if (myChangeState)
	{
		myChangeState = false;
		return true;
	}

	return false;
}


