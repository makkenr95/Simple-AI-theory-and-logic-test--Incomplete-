#pragma once
#include "AIBase.h"

class AI1 : public AIBase
{
public:
	AI1();
	virtual ~AI1() override;

	void Update(float aDeltaTime);

	void SetUpStates();

	void StartAnimation();
private:

};

