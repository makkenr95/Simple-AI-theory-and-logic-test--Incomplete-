#include "stdafx.h"
#include "AI1.h"

#include "WanderState.h"
#include "AttackState.h"
#include "HealState.h"

AI1::AI1()
{
	SetUpStates();
}

AI1::~AI1()
{
}

void AI1::Update(float aDeltaTime)
{
	AIBase::Update(aDeltaTime);
}

void AI1::SetUpStates()
{
	auto wanderState = CreateState<WanderState>(this);
	auto attackState = CreateState<AttackState>(this);
	auto healState = CreateState<HealState>(this);

	wanderState->AddTransition([wanderState, attackState]()->AIState*
		{
			if (wanderState->ShouldTransitionToAttackStateState())
			{
				return attackState;
			}
			return nullptr;
		});

	attackState->AddTransition([attackState, healState]()->AIState*
		{
			if (attackState->ShouldTransitionHealStateState())
			{
				return healState;
			}
			return nullptr;
		});

	attackState->AddTransition([attackState, wanderState]()->AIState*
		{
			if (attackState->ShouldTransitionWanderStateState())
			{
				return wanderState;
			}
			return nullptr;
		});

	healState->AddTransition([healState, wanderState]()->AIState*
		{
			if (healState->ShouldTransitionToWanderState())
			{
				return wanderState;
			}
			return nullptr;
		});

	SetStartState(wanderState);
}

void AI1::StartAnimation()
{
}

