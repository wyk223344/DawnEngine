#pragma once

#include "Common.h"

namespace DawnEngine
{
	struct Matrix4x4;

	struct Quaternion
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

		static Quaternion Zero;

		static Quaternion One;

		static Quaternion Identity;

	public:

        Quaternion()
			: X(0)
			, Y(0)
			, Z(0)
			, W(0)
        {
        }

        Quaternion(const float xyzw)
            : X(xyzw)
            , Y(xyzw)
            , Z(xyzw)
            , W(xyzw)
        {
        }

        Quaternion(const float x, const float y, const float z, const float w)
            : X(x)
            , Y(y)
            , Z(z)
            , W(w)
        {
        }

	public:

		void Normalize()
		{
			const float length = Length();
			if (!Math::IsZero(length))
			{
				const float inv = 1.0f / length;
				X *= inv;
				Y *= inv;
				Z *= inv;
				W *= inv;
			}
		}

		float Length() const
		{
			return Math::Sqrt(X * X + Y * Y + Z * Z + W * W);
		}

	public:

		static void RotationMatrix(const Matrix4x4& matrix, Quaternion& result);
	};
}