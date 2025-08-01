#pragma once

#include "Controller.h"

class SeekController : public AI::Controller
{
public:
	SeekController();

	Tga2D::Vector2f Update(const Tga2D::Vector2f& aPosition);

	float Lerp(const float a, const float b, const float aTime);

private:
	float myAngleToPlayer = 0;
};