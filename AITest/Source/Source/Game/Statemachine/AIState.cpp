#include "stdafx.h"
#include "AIState.h"

AIState::AIState(AIBase* aActor) :
myActor(aActor)
{
}

AIState::~AIState()
{
}

AIState* AIState::GetTransition()
{
	for (unsigned int i = 0; i < myTransitions.size(); i++)
	{
		AIState* transitionTo = myTransitions[i]();
		if (transitionTo != nullptr)
		{
			return transitionTo;
		}
	}
	return nullptr;
}

void AIState::AddTransition(std::function<AIState* ()> aTransition)
{
	myTransitions.push_back(aTransition);
}

void AIState::Move(const float& aDeltaTime)
{
}

const std::string& AIState::GetAIStateName() const
{
	return myName;
}

void AIState::SetStateName(const std::string aStateName)
{
	myName = aStateName;
}

