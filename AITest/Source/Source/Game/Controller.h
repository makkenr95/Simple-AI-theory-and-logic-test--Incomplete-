#pragma once
namespace AI
{
	class Controller
	{
	public:
		virtual ~Controller() = default;
		virtual Tga2D::Vector2f Update(const Tga2D::Vector2f& aPosition) = 0;

	};
}