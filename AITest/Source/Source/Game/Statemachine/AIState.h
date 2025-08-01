#pragma once
#include <functional>
#include <string>
#include <vector>

class AI1Data {
public:
	inline static float toAngle = 0;
	inline static float beforeAngle = 0;
	inline static float myRandomizeDelay = 0.5f;
	inline static float myRandomizeProgress = 0;
	inline static float myAngle = 180;
	inline static float mySpeed = 0.05f;
	inline static float myBulletCooldown = .20f;
	inline static float myBulletTimer = .25f;
	inline static bool	myObstacle = false;
};

//class AI2Data {
//public:
//	inline static float toAngle = 0;
//	inline static float beforeAngle = 0;
//	inline static float myRandomizeDelay = 0.5f;
//	inline static float myRandomizeProgress = 0;
//	inline static float myAngle = 180;
//	inline static float mySpeed = 0.05f;
//	inline static float myBulletCooldown = .20f;
//	inline static float myBulletTimer = .25f;
//	inline static bool	myObstacle = false;
//};

class AIBase;
class StateMachineBase;

class AIState
{
public:
	AIState(AIBase* aActor);
	virtual ~AIState();

	virtual void OnEnterState() = 0;
	virtual void OnExitState() = 0;

	virtual void Update(float aDeltaTime) = 0;

	AIState* GetTransition();
	virtual void AddTransition(std::function<AIState* ()> aTransition);

	virtual void Move(const float& aDeltaTime);

	const std::string& GetAIStateName() const;

	void SetStateName(const std::string aStateName);
private:
	AIBase* myActor;
protected:
	std::vector< std::function<AIState* ()>> myTransitions;

	std::string myName = "Default";

};

