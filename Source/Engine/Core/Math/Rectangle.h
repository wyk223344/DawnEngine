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
	};
}