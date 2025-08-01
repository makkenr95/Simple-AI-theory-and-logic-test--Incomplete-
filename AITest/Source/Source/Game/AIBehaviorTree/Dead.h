#pragma once
#include <iostream>

#include "BrainTree.h"
#include "../PollingStation.h"

class Dead : public BrainTree::Decorator
{
public:;
	  Dead(BrainTree::Blackboard::Ptr blackboard) { myBlackboard = blackboard; };

	  Status update() override
	  {
		  if (myBlackboard->GetOwner()->GetHp() <= 0)
		  {
			  return Status::Failure;
		  }
		  return Status::Success;
	  }

private:
	BrainTree::Blackboard::Ptr myBlackboard = nullptr;
};


