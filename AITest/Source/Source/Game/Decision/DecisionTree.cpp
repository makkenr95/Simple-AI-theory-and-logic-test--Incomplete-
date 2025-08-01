#include "stdafx.h"
#include "DecisionTree.h"

DecisionNode* DecisionNode::Decide()
{
	if (myTransition) {
		if (myTransition()) {
			if (myTrueNode == nullptr)
			{
				return this;
			}

			return myTrueNode->Decide();
		}

		if (myFalseNode == nullptr)
		{
			return this;
		}

		return myFalseNode->Decide();
	}

	return this;
}

void DecisionTree::Update(float aDeltaTime)
{
	auto* decided = myNode->Decide();
	if (decided) 
	{
		if (decided->myUpdate) 
		{
			decided->myUpdate(aDeltaTime);
		}
	}
}

void DecisionTree::SetNode(DecisionNode* aNode)
{
	myNode = aNode;
}
