#include "stdafx.h"
#include "WanderController.h"

#define Deg2Rad 0.0174532925 

float Lerp(const float a, const float b, const float aTime)
{
	float aa = a * (1 - aTime);
	float bb = b * aTime;
	return aa + bb;
}

WanderController::WanderController()
{

}

Tga2D::Vector2f WanderController::Update(const Tga2D::Vector2f& aPosition)
{
	myRandomizeProgress += Tga2D::CEngine::GetInstance()->GetDeltaTime();

	static float toAngle = 0; 
	static float beforeAngle = 0; 
	if (myRandomizeProgress > myRandomizeDelay)
	{
		myRandomizeProgress = 0;
		float randomVal = (float)(rand() % 90) - 45.0f;
		toAngle = myAngle + randomVal;
		beforeAngle = myAngle;
	}

	float delay = myRandomizeProgress / myRandomizeDelay;
	float lerp = Lerp(beforeAngle, toAngle, delay);
	myAngle = lerp;

	Tga2D::Vector2f velocity = { (float)cos(myAngle * Deg2Rad), (float)sin(myAngle * Deg2Rad) };

	return velocity;
}
