#pragma once

#include "Actor.h"
#include "AIBehaviorTree/BrainTree.h"
#include "Statemachine/AI1.h"
#include "Decision/DecisionTree.h"



class AI2Data {
public:
	inline static float toAngle = 0.0f;
	inline static float beforeAngle = 0.0f;
	inline static float myRandomizeDelay = 0.5f;
	inline static float myRandomizeProgress = 0;
	inline static float myAngle = 180;
	inline static float mySpeed = 0.05f;
	inline static float myBulletCooldown = .25f;
	inline static float myBulletTimer = .25f;
	inline static bool	myObstacle = false;
};

class CGameWorld
{
public:
	CGameWorld();
	~CGameWorld();

	void Init();
	void Update(float aTimeDelta);

private:
	void SpawnActors(const int aCount);
	void SpawnObstacles(const int aCount);
	void ClearActors();

private:
	BrainTree::BehaviorTree myBTree;

	Actor* myWanderer;
	std::vector<Actor*> myRobots;
	std::vector<Actor*> myComputers;
	std::vector<GameObject*> myObstacles;

	AI1* myAI1;
	GameObject* myAI2;
	DecisionTree* myTree;
};