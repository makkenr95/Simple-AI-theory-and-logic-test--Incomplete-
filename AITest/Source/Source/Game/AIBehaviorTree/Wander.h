#pragma once
#include <iostream>
#include "BrainTree.h"
#include "../PollingStation.h"
#include "../LerpStuff.h"
#include "../CollisionManager.h"
#include "../GameWorld.h"

#define Deg2Rad 0.0174532925

class Wander : public BrainTree::Leaf
{
public:;
	  Wander(BrainTree::Blackboard::Ptr blackboard) : BrainTree::Leaf(blackboard) {};

	  Status update() override
	  {
		  float aDeltaTime = Tga2D::CEngine::GetInstance()->GetDeltaTime();

		  AI2Data::myRandomizeProgress += aDeltaTime;

		  {
			  Tga2D::Vector2f velocity = { (float)cos(AI2Data::myAngle * Deg2Rad), (float)sin(AI2Data::myAngle * Deg2Rad) };
			  auto start = blackboard->GetOwner()->GetPosition();
			  if (CollisionManager::Get().Raycast(start.x, start.y, velocity.x, velocity.y, .1f, eTag::Obstacle))
			  {
				  AI2Data::toAngle += 45.f * aDeltaTime;
				  AI2Data::mySpeed = 0.001f;
				  AI2Data::myObstacle = true;
			  }
			  else
			  {
				  AI2Data::mySpeed = 0.05f;
				  if (AI2Data::myRandomizeProgress > AI2Data::myRandomizeDelay)
				  {
					  AI2Data::myRandomizeProgress = 0;
					  AI2Data::beforeAngle = AI2Data::myAngle;

					  if (AI2Data::myObstacle)
					  {
						  AI2Data::myObstacle = false;
						  //return;	
					  }


					  float randomVal = (float)(rand() % 90) - 45.0f;
					  AI2Data::toAngle = AI2Data::myAngle + randomVal;
					  AI2Data::beforeAngle = AI2Data::myAngle;
				  }
			  }
		  }

		  float delay = AI2Data::myRandomizeProgress / AI2Data::myRandomizeDelay;
		  float lerp = LerpTrue(AI2Data::beforeAngle, AI2Data::toAngle, delay);

		  AI2Data::myAngle = lerp;

		  Tga2D::Vector2f velocity = { (float)cos(AI2Data::myAngle * Deg2Rad), (float)sin(AI2Data::myAngle * Deg2Rad) };

		  blackboard->GetOwner()->Move(velocity * aDeltaTime * AI2Data::mySpeed);


		  velocity.Normalize();

		  blackboard->GetOwner()->myRotation = atan2f(velocity.y, velocity.x);
		  return Status::Success;
	  }

private:
	float myRandomizeDelay = 0.5f;
	float myRandomizeProgress = 0;

	float myAngle = 0;
};