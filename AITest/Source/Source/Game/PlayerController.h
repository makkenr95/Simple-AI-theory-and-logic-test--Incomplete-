#pragma once

#include "Controller.h"
#include <tga2d/math/vector2.h>

class PlayerController : public AI::Controller
{
public:
	PlayerController();

	Tga2D::Vector2f Update(const Tga2D::Vector2f& aPosition) override;

private:
	void DoMouseInput();

private:
	Tga2D::Vector2f myTargetPosition = { 0.5f, 0.5f };
	float myDistanceEpsilon = 0.00005f;
	float myComputerHackingDist = 0.05f;
};