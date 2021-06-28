#pragma once

#include "Vector2.h"

namespace DawnEngine::Math
{
	struct Rectangle
	{
	public:

		Vector2 Location;

		Vector2 Size;

	public:

		Rectangle()
		{
		}

		Rectangle(float x, float y, float width, float height)
			: Location(x, y)
			, Size(width, height)
		{
		}

		float GetLeft() const
		{
			return Location.X;
		}

		float GetRight() const
		{
			return Location.X + Size.X;
		}

		float GetTop() const
		{
			return Location.Y;
		}

		float GetBottom() const
		{
			return Location.Y + Size.Y;
		}
	};
}