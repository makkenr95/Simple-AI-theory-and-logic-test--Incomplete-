#pragma once
#include <iostream>
#include "BrainTree.h"
#include "../PollingStation.h"

class Shoot : public BrainTree::Leaf
{
public:;
	  Shoot(BrainTree::Blackboard::Ptr blackboard) : BrainTree::Leaf(blackboard) {};

	  void Fire();
	  Status update() override
	  {
		  auto ai1 = PollingStation::GetInstance()->GetAI1();

		  auto dist = (ai1->GetPosition() - blackboard->GetOwner()->GetPosition()).Length();

		  if (dist <= 0.6f)
		  {
			  Fire();
			  return Status::Success;
		  }
		  return Status::Failure;
	  }

private:
	float myRandomizeDelay = 0.5f;
	float myRandomizeProgress = 0;

	float myAngle = 0;
};

