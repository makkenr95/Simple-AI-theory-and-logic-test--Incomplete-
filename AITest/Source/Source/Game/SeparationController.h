#pragma once

#include "Controller.h"

class SeparationController : public AI::Controller
{
public:
	SeparationController();

	Tga2D::Vector2f Update(const Tga2D::Vector2f& aPosition);

private:
	float myThreshhold = 0.1f * 0.1f;
};