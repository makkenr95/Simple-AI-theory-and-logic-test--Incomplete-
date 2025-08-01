#pragma once

#include "Controller.h"

class WanderController : public AI::Controller
{
public:
	WanderController();

	Tga2D::Vector2f Update(const Tga2D::Vector2f& aPosition);

private:
	float myRandomizeDelay = 0.5f;
	float myRandomizeProgress = 0;

	float myAngle = 0;
};