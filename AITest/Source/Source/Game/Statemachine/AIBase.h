#pragma once
#include <vector>
#include <memory>

#include "AIState.h"
#include "GameObject.h"

class AIBase : public GameObject
{
public:
	AIBase() = default;
	virtual ~AIBase() = default;

	virtual void Update(float aDeltaTime) override;

	void SetStartState(AIState* aStartUpState);

	void DoStateTransition();

	template<typename T, typename U>
	T* CreateState(U aAIBase);

	void Move(Tga2D::Vector2f& aDir);
	void SetPosition(Tga2D::Vector2f aPos);

protected:
	std::vector<std::unique_ptr<AIState>> myStates;

	AIState* myCurrentState = nullptr;
};

template <typename T, typename U>
T* AIBase::CreateState(U aAIBase)
{
	auto state = std::make_unique<T>(aAIBase);
	state->Init();

	T* rawPtr = state.get();

	myStates.push_back(std::move(state));

	return rawPtr;
}


