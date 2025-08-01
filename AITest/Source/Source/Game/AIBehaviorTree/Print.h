#pragma once
#include <iostream>
#include "BrainTree.h"
#include "../PollingStation.h"

class Print : public BrainTree::Leaf
{
public:
	Print(std::string aText, bool aISSuccess) { myText = aText; myIsSuccess = aISSuccess; };

	Status update() override
	{
		std::cout << myText << std::endl;
		return  myIsSuccess ? Status::Success : Status::Failure;
	}

private:
	std::string myText = "";
	bool myIsSuccess = false;
};

