#include "stdafx.h"

#include "AIBase.h"

#include <iostream>

#include "AIHazmatSuitPositionState.h"

void AIBase::Update(float aDeltaTime)
{
	myCurrentState->Update(aDeltaTime);
	DoStateTransition();
	GameObject::Update(aDeltaTime);
}

void AIBase::SetStartState(AIState* aStartUpState)
{
	myCurrentState = aStartUpState;
}

void AIBase::DoStateTransition()
{
	AIState* newState = myCurrentState->GetTransition();
	if (newState != nullptr)
	{
		myCurrentState->OnEnterState();
		myCurrentState = newState;
		myCurrentState->OnExitState();
		std::cout << "Enter: " + myCurrentState->GetAIStateName() << std::endl;
	}
}

void AIBase::Move(Tga2D::Vector2f& aDir)
{
	myPosition += aDir;
}

void AIBase::SetPosition(Tga2D::Vector2f aPos)
{
	myPosition = aPos;
	
}

