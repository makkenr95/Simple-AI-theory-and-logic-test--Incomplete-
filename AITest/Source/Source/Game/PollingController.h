#pragma once

#include "Controller.h"
#include <tga2d/math/vector2.h>
#include "Statemachine/AI1.h"

class PollingController : public AI::Controller
{
public:
	PollingController();

	Tga2D::Vector2f Update(const Tga2D::Vector2f& aPosition);

private:
	float myComputerHackRange = 0.05f;

};