#include "stdafx.h"
#include "GameWorld.h"
#include "DummyController.h"
#include "PlayerController.h"
#include "PollingController.h"
#include "EventController.h"
#include "WanderController.h"
#include "PontusController.h"

#include <tga2d/sprite/sprite.h>
#include <tga2d/error/error_manager.h>

#include "PollingStation.h"
#include "EventManager.h"

#include "SeparationController.h"
#include "SeekController.h"
#include "imgui.h"
#include "Bullet.h"
#include "AIBehaviorTree/BrainTree.h"
#include "AIBehaviorTree/Dead.h"
#include "AIBehaviorTree/EnemyLineOfSight.h"
#include "AIBehaviorTree/EnemyVisible.h"
#include "AIBehaviorTree/LowHealth.h"
#include "AIBehaviorTree/Print.h"
#include "AIBehaviorTree/Shoot.h"
#include "AIBehaviorTree/WalkToHeal.h"
#include "AIBehaviorTree/Wander.h"

extern float globalSeparationRange;
extern float globalCohesionRange;
extern float globalVMatchingRange;

extern float globalSeparationMultiplier;
extern float globalCohesionMultiplier;
extern float globalVMatchingMultiplier;

CGameWorld::CGameWorld()
{
}

CGameWorld::~CGameWorld()
{
	delete PollingStation::GetInstance();
}


#define Deg2Rad 0.0174532925f
#define Rad2Deg 1.f / 0.0174532925f

float Lerp3(const float a, const float b, const float aTime)
{
	float aa = a * (1 - aTime);
	float bb = b * aTime;
	return aa + bb;
}

void CGameWorld::Init()
{
	new PollingStation();
	new EventManager();

	//myRobots.push_back(new Actor());
	//myRobots.back()->Init("sprites/robot.png", 0.1f, new WanderController(), { 0.7f, 0.7f });
	//myWanderer = myRobots.back();

	SpawnObstacles(7);
	//SpawnActors(20);

	myAI1 = new AI1();
	myAI1->SetPosition({ 0.3f, 0.3f });
	{
		auto* coll = new Collider();
		coll->gameobject = myAI1;
		coll->radius = .02f;
		coll->tag = eTag::AI1;
		myAI1->SetCollider(coll);
	}

	PollingStation::GetInstance()->AddAI1(myAI1);

	myAI2 = new GameObject();
	myAI2->SetPosition({ 0.7f, .7f });
	{
		auto* coll = new Collider();
		coll->gameobject = myAI2;
		coll->radius = .02f;
		coll->tag = eTag::AI2;
		myAI2->SetCollider(coll);
	}
	PollingStation::GetInstance()->AddAI2(myAI2);

	{ // behavior tree

		/*BrainTree::Blackboard::Ptr blackboard = std::make_shared<BrainTree::Blackboard>(myAI2);
		myBTree = BrainTree::Builder()
			.composite<BrainTree::Selector>()
				.composite<BrainTree::Sequence>()
					.decorator<EnemyVisible>(blackboard)
						.end()
					.leaf<Print>("first", true)
					.leaf<Print>("first 2", true)
					.end()
				.composite<BrainTree::Sequence>()
					.leaf<Print>("second", true)
					.end()
				.end()
			.build();*/



		BrainTree::Blackboard::Ptr blackboard = std::make_shared<BrainTree::Blackboard>(myAI2);
		myBTree = BrainTree::Builder()
			.composite<BrainTree::Selector>()
				.composite<BrainTree::Sequence>()
					.decorator<Dead>(blackboard)
						.end()
					.decorator<LowHealth>(blackboard)
						.end()
					//.composite<BrainTree::Sequence>()
					.leaf<WalkToHeal>(blackboard)
						//.end()
					.end()
				.composite<BrainTree::Sequence>()
					.decorator<EnemyVisible>(blackboard)
						.end()
					.composite<BrainTree::Sequence>()
						.leaf<Shoot>(blackboard)
						.end()
					.end()
				.leaf<Wander>(blackboard)
			.end()
			.build();
	}

}

void CGameWorld::Update(float aTimeDelta)
{
	myBTree.update();

	if (GetAsyncKeyState(VK_ESCAPE))
	{
		Tga2D::CEngine::Shutdown();
	}

	const Tga2D::Vector2f healingPos(.6f, .3f);
	Tga2D::CDebugDrawer::DrawCircle(healingPos, .15f, { 0, 1, 0, 1 });

	constexpr float hTime = 1.5f;
	static float hTimer = .1f;

	hTimer -= aTimeDelta;

	if (hTimer <= 0)
	{
		hTimer = hTime;

		{
			float dist = (myAI1->GetPosition() - healingPos).Length();
			if (dist < .15f)
			{
				myAI1->SetHp(min(myAI1->GetHp() + 1, 50));
			}

		}
		{
			float dist = (myAI2->GetPosition() - healingPos).Length();
			if (dist < .15f)
			{
				myAI2->SetHp(min(myAI2->GetHp() + 1, 50));
			}

		}
	}

	static bool ai1Respawning = false;
	static bool ai2Respawning = false;
	static float ai1Respawn = 0;
	static float ai2Respawn = 0;

	if (myAI1->GetHp() > 0)
	{
		myAI1->Update(aTimeDelta);
		myAI1->Render();
	}
	else if (!ai1Respawning)
	{
		ai1Respawning = true;
		ai1Respawn = 2.f;

		myAI1->SetPosition({ -1, -1 });
	}

	if (ai1Respawning)
	{
		ai1Respawn -= aTimeDelta;
		if (ai1Respawn <= 0)
		{
			ai1Respawning = false;
			ai1Respawn = 0;

			myAI1->SetPosition({ .3f, .3f });
			myAI1->SetHp(50);
		}
	}

	if (myAI2->GetHp() > 0)
	{
		//myTree->Update(aTimeDelta);
		myAI2->Update(aTimeDelta);
		myAI2->Render();
	}
	else if (!ai2Respawning)
	{
		ai2Respawning = true;
		ai2Respawn = 2.f;

		myAI2->SetPosition({ -1, -1 });
	}

	if (ai2Respawning)
	{
		ai2Respawn -= aTimeDelta;
		if (ai2Respawn <= 0)
		{
			ai2Respawning = false;
			ai2Respawn = 0;
			myAI2->SetHp(50);
			myAI2->SetPosition({ .7f, .7f });
		}
	}

	for (auto& obst : myObstacles) {
		obst->Update(aTimeDelta);
		obst->Render();
	}

	for (auto& bull : Bullet::GetBullets()) {
		bull->Update(aTimeDelta);
		bull->Render();
	}
}

void CGameWorld::SpawnActors(const int aCount)
{
	for (int i = 0; i < aCount; ++i)
	{
		myRobots.push_back(new Actor());
		myRobots.back()->Init("sprites/computer.png", 0.1f, new PontusController(), { (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX });
	}

	for (int i = 0; i < myRobots.size(); ++i)
	{
		PollingStation::GetInstance()->AddActor(myRobots[i]);
	}
}

void CGameWorld::SpawnObstacles(const int aCount)
{
	for (int i = 0; i < aCount; ++i)
	{
		auto* obj = new GameObject();
		obj->SetSprite(nullptr);

		obj->SetPosition(Tga2D::Vector2f{ (float)((rand() + 453) % 100) / 100.f, (float)((rand() + 312) % 100) / 100.f });

		{
			auto coll = new Collider();
			coll->gameobject = myAI2;
			coll->radius = (float)(rand() % 100) / 1000.f + .01f;
			coll->tag = eTag::Obstacle;
			obj->SetCollider(coll);
			coll->x = obj->GetPosition().x;
			coll->y = obj->GetPosition().y;
		}
		obj->SetSprite(nullptr);

		myObstacles.emplace_back(obj);
	}
}

void CGameWorld::ClearActors()
{
	for (int i = 0; i < myRobots.size(); ++i)
	{
		PollingStation::GetInstance()->RemoveActor(myRobots[i]);
		delete myRobots[i];
	}

	myRobots.clear();
}
