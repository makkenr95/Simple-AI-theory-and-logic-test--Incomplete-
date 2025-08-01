#pragma once
#include <iostream>
#include "BrainTree.h"
#include "../PollingStation.h"
#include "../CollisionManager.h"

class EnemyVisible : public BrainTree::Decorator
{
public:;
	  EnemyVisible(BrainTree::Blackboard::Ptr blackboard) { myBlackboard = blackboard; };

	  Status update() override
	  {
		  bool rayhit = false;
		  auto AI1 = PollingStation::GetInstance()->GetAI1();

		  auto dir = AI1->GetPosition() - myBlackboard->GetOwner()->GetPosition();
		  auto dist2 = std::sqrt(dir.x * dir.x + dir.y * dir.y);

		  dir.Normalize();
		  if ((dist2 < .6f))
		  {
			  auto start = myBlackboard->GetOwner()->GetPosition();
			  if (CollisionManager::Get().Raycast(start.x, start.y, dir.x, dir.y, dist2, eTag::Obstacle))
			  {
				  INFO_PRINT("Line of sight failure")
					  rayhit = true;
				  return Status::Failure;
			  }
			  else
			  {
				  INFO_PRINT("Line of sight success")
					  rayhit = false;
			  }
		  }

		  auto ai1 = PollingStation::GetInstance()->GetAI1();

		  auto dist = (ai1->GetPosition() - myBlackboard->GetOwner()->GetPosition()).Length();

		  if (dist <= 0.6f && rayhit == false)
		  {
			  INFO_PRINT("Visible success")

				  return Status::Success;
		  }
		  INFO_PRINT("Visible failure")
			  return Status::Failure;
	  }

private:
	BrainTree::Blackboard::Ptr myBlackboard;
};

