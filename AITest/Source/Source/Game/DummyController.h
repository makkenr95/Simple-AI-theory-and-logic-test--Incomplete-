#pragma once
#include "Controller.h"
#include <tga2d/math/vector2.h>

namespace AI
{
	// Random walking controller for displaying how to implementing a controller
	class DummyController : public Controller
	{
	public:
		DummyController();
		Tga2D::Vector2f Update(const Tga2D::Vector2f& aPosition) override;

	private:
		Tga2D::Vector2f	myTargetPosition;
		void CreateRandomTargetPosition();
	};
}