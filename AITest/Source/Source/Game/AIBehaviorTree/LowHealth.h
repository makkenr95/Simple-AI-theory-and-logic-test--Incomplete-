#pragma once
#include <iostream>

#include "BrainTree.h"
#include "../PollingStation.h"

class LowHealth : public BrainTree::Decorator
{
public:;
	  LowHealth(BrainTree::Blackboard::Ptr blackboard) { myBlackboard = blackboard; };

	  Status update() override
	  {
		  std::cout << myBlackboard->GetOwner()->GetHp() << std::endl;

		  if (myBlackboard->GetOwner()->GetHp() < 20)
		  {
			  return Status::Success;
		  }
		  return Status::Failure;
	  }

private:
	BrainTree::Blackboard::Ptr myBlackboard = nullptr;
};

