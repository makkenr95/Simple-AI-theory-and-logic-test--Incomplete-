#pragma once

class DecisionNode 
{
public:
	DecisionNode* Decide();
public:
	std::function<bool()> myTransition;
	std::function<void(float)> myUpdate;
	DecisionNode* myTrueNode = nullptr;
	DecisionNode* myFalseNode = nullptr;
};

class DecisionTree
{
public:
	void Update(float aDeltaTime);
	void SetNode(DecisionNode* aNode);
	DecisionNode* GetNode() { return myNode; }
private:
	DecisionNode* myNode;
};

