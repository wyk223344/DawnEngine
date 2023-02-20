#pragma once

#include "Common.h"


namespace DawnEngine
{
	struct Vector2;
	struct Vector3;

	struct Vector4
	{
	public:
		union
		{
			struct
			{
				float X;
				float Y;
				float Z;
				float W;
			};
			float Raw[4];
		};

	public:

		Vector4(float xyzw)
			: X(xyzw)
			, Y(xyzw)
			, Z(xyzw)
			, W(xyzw)
		{
		}

		Vector4(float x, float y, float z, float w)
			: X(x)
			, Y(y)
			, Z(z)
			, W(w)
		{
		}

	public:

		static const Vector4 Zero;
		static const Vector4 One;
	};
}