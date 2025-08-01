#include "stdafx.h"
#include "PollingStation.h"

PollingStation::PollingStation()
{
	ourInstance = this;
}

PollingStation::~PollingStation()
{
	ourInstance = nullptr;
}

void PollingStation::AddActor(Actor* anActor)
{
	myActors.push_back(anActor);
}

void PollingStation::RemoveActor(Actor* anActor)
{
	myActors.erase(std::remove(myActors.begin(), myActors.end(), anActor));
}

const std::vector<Actor*>& PollingStation::GetActors()
{
	return myActors;
}

PollingStation* PollingStation::GetInstance()
{
	return ourInstance;
}

void PollingStation::AddAI1(AI1* aAI1)
{
	myAI1 = aAI1;
}

void PollingStation::AddAI2(GameObject* aAI1)
{
	myAI2 = aAI1;
}

GameObject* PollingStation::GetAI1()
{
	return myAI1;
}

GameObject* PollingStation::GetAI2()
{
	return myAI2;
}
