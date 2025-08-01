#pragma once
#include <iostream>
#include "BrainTree.h"
#include "../PollingStation.h"

class WalkToHeal : public BrainTree::Leaf
{
public:;
	  WalkToHeal(BrainTree::Blackboard::Ptr blackboard) : BrainTree::Leaf(blackboard) {};

	  Status update() override
	  {
		  float deltaTime = Tga2D::CEngine::GetInstance()->GetDeltaTime();

		  Tga2D::Vector2f healingPos(.6f, .3f);

		  auto dir = healingPos - blackboard->GetOwner()->GetPosition();

		  auto dist = (healingPos - blackboard->GetOwner()->GetPosition()).Length();
		  if (dist <= 0.05f)
		  {
			  INFO_PRINT("walk to heal success ")

				  return Status::Failure;
		  }
		  else
		  {
			  blackboard->GetOwner()->Move(dir.Normalize() * deltaTime);
			  INFO_PRINT("walk to heal running ")
				  return Status::Running;
		  }
	  }

private:
};

