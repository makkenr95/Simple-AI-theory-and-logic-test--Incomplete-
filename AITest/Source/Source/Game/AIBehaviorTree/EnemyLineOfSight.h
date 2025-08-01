#pragma once
#include <iostream>
#include "BrainTree.h"
#include "../PollingStation.h"
#include "../CollisionManager.h"

class EnemyLineOfSight : public BrainTree::Decorator
{
public:;
	  EnemyLineOfSight(BrainTree::Blackboard::Ptr blackboard) { myBlackboard = blackboard; };

	  Status update() override
	  {
		  auto AI1 = PollingStation::GetInstance()->GetAI1();

		  auto dir = AI1->GetPosition() - myBlackboard->GetOwner()->GetPosition();
		  auto dist = std::sqrt(dir.x * dir.x + dir.y * dir.y);

		  dir.Normalize();
		  if ((dist < .6f))
		  {
			  auto start = myBlackboard->GetOwner()->GetPosition();
			  if (CollisionManager::Get().Raycast(start.x, start.y, dir.x, dir.y, dist, eTag::Obstacle))
			  {
				  INFO_PRINT("Line of sight failure")
					  return Status::Failure;
			  }
			  INFO_PRINT("Line of sight success")
				  return Status::Success;
		  }
	  }

private:
	BrainTree::Blackboard::Ptr myBlackboard;
};

