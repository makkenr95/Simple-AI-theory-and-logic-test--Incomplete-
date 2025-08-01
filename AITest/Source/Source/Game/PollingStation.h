#pragma once
#include "Statemachine/AI1.h"

class Actor;

class PollingStation
{
public:
	PollingStation();
	~PollingStation();

	void AddActor(Actor* anActor);
	void RemoveActor(Actor* anActor);
	const std::vector<Actor*>& GetActors();

	static PollingStation* GetInstance();

	void AddAI1(AI1* aAI1);
	void AddAI2(GameObject* aAI1);
	GameObject* GetAI1();
	GameObject* GetAI2();
private:
	std::vector<Actor*> myActors;

	AI1* myAI1 = nullptr;
	GameObject* myAI2 = nullptr;

private:
	inline static PollingStation* ourInstance = nullptr;
};