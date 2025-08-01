#pragma once

#include "Controller.h"

// Pontus was never here.
class PontusController : public AI::Controller
{
public:
	PontusController();

	Tga2D::Vector2f Update(const Tga2D::Vector2f& aPosition);

private:
	Tga2D::Vector2f Separation();
	Tga2D::Vector2f Cohesion();
	Tga2D::Vector2f VMatching();
	Tga2D::Vector2f Wandering();
private:
	Tga2D::Vector2f myPosition;
	Tga2D::Vector2f myPreviousVelocity;
	Tga2D::Vector2f myPrevPrevVelocity;
	Tga2D::Vector2f myPreferedDirection;

	float myBeforeAngle;
	float myToAngle;
	float myRandomizeDelay = 0.5f;
	float myRandomizeProgress = 0;

	float myAngle = 0;
};