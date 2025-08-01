#include "stdafx.h"
#include "HealState.h"
#include "AI1.h"

#define Deg2Rad 0.0174532925 

HealState::HealState(AI1* aActor)
	: AIState(aActor)
{
	myActor = aActor;
}

HealState::~HealState()
{
}

void HealState::Init()
{
}

void HealState::OnEnterState()
{
}

void HealState::OnExitState()
{
	myShouldTransToWander = false;
}

void HealState::Update(float aDeltaTime)
{
	Tga2D::Vector2f healingPos(.6f, .3f);
	
	auto dir = healingPos - myActor->GetPosition();
	myActor->Move(dir.Normalize() * aDeltaTime);


}

bool HealState::ShouldTransitionToWanderState()
{
	Tga2D::Vector2f healingPos(.6f, .3f);

	auto dir = healingPos - myActor->GetPosition();

	auto length = dir.Length();
	return (length < 0.03f);
}
