#pragma once

#include "Engine/Core/Meta/Reflection/Reflection.h"
#include "Common.h"

namespace DawnEngine
{
	struct Vector2;
	struct Vector4;
    struct Quaternion;
    struct Matrix4x4;

    REFLECTION_TYPE(Vector3)
	STRUCT(Vector3, Fields)
	{
        REFLECTION_BODY(Vector3);

	public:
		union
		{
			struct
			{
				float X;
				float Y;
				float Z;
			};
			float Raw[3];
		};

	public:

        Vector3()
            : X(0)
            , Y(0)
            , Z(0)
        {
        }

		Vector3(float xyz)
			: X(xyz)
			, Y(xyz)
			, Z(xyz)
		{
		}

		Vector3(float x, float y, float z)
			: X(x)
			, Y(y)
			, Z(z)
		{
		}

    public:  // 对外函数

        void Normalize()
        {
            const float length = Length();
            if (!Math::IsZero(length))
            {
                const float inv = 1.0f / length;
                X *= inv;
                Y *= inv;
                Z *= inv;
            }
        }

        float Length() const
        {
            return Math::Sqrt(X * X + Y * Y + Z * Z);
        }

        float LengthSquared() const
        {
            return X * X + Y * Y + Z * Z;
        }

        bool IsZero() const
        {
            return Math::IsZero(X) && Math::IsZero(Y) && Math::IsZero(Z);
        }

        bool IsOne() const
        {
            return Math::IsOne(X) && Math::IsOne(Y) && Math::IsOne(Z);
        }

        bool IsNaN() const
        {
            return isnan(X) || isnan(Y) || isnan(Z);
        }

        bool IsInfinity() const
        {
            return isinf(X) || isinf(Y) || isinf(Z);
        }

        bool IsNanOrInfinity() const
        {
            return IsInfinity() || IsNaN();
        }

	public:  // 操作符重写

        Vector3 operator+(const Vector3& b) const
        {
            return Add(*this, b);
        }

        Vector3 operator-(const Vector3& b) const
        {
            return Subtract(*this, b);
        }

        Vector3 operator*(const Vector3& b) const
        {
            return Multiply(*this, b);
        }

        Vector3 operator/(const Vector3& b) const
        {
            return Divide(*this, b);
        }

        Vector3 operator-() const
        {
            return Vector3(-X, -Y, -Z);
        }

        Vector3 operator^(const Vector3& b) const
        {
            return Cross(*this, b);
        }

        float operator|(const Vector3& b) const
        {
            return Dot(*this, b);
        }

        Vector3& operator+=(const Vector3& b)
        {
            *this = Add(*this, b);
            return *this;
        }

        Vector3& operator-=(const Vector3& b)
        {
            *this = Subtract(*this, b);
            return *this;
        }

        Vector3& operator*=(const Vector3& b)
        {
            *this = Multiply(*this, b);
            return *this;
        }

        Vector3& operator/=(const Vector3& b)
        {
            *this = Divide(*this, b);
            return *this;
        }

        Vector3 operator+(float b) const
        {
            return Add(*this, b);
        }

        Vector3 operator-(float b) const
        {
            return Subtract(*this, b);
        }

        Vector3 operator*(float b) const
        {
            return Multiply(*this, b);
        }

        Vector3 operator/(float b) const
        {
            return Divide(*this, b);
        }

        Vector3& operator+=(float b)
        {
            *this = Add(*this, b);
            return *this;
        }

        Vector3& operator-=(float b)
        {
            *this = Subtract(*this, b);
            return *this;
        }

        Vector3& operator*=(float b)
        {
            *this = Multiply(*this, b);
            return *this;
        }

        Vector3& operator/=(float b)
        {
            *this = Divide(*this, b);
            return *this;
        }

        bool operator==(const Vector3& b) const
        {
            return X == b.X && Y == b.Y && Z == b.Z;
        }

        bool operator!=(const Vector3& b) const
        {
            return X != b.X || Y != b.Y || Z != b.Z;
        }

        bool operator>(const Vector3& b) const
        {
            return X > b.X && Y > b.Y && Z > b.Z;
        }

        bool operator>=(const Vector3& b) const
        {
            return X >= b.X && Y >= b.Y && Z >= b.Z;
        }

        bool operator<(const Vector3& b) const
        {
            return X < b.X&& Y < b.Y&& Z < b.Z;
        }

        bool operator<=(const Vector3& b) const
        {
            return X <= b.X && Y <= b.Y && Z <= b.Z;
        }

	public:  // 静态函数

        static float Dot(const Vector3& a, const Vector3& b)
        {
            return a.X * b.X + a.Y * b.Y + a.Z * b.Z;
        }

        static Vector3 Cross(const Vector3& a, const Vector3& b)
        {
            return Vector3(
                a.Y * b.Z - a.Z * b.Y,
                a.Z * b.X - a.X * b.Z,
                a.X * b.Y - a.Y * b.X);
        }

        static void Cross(const Vector3& a, const Vector3& b, Vector3& result)
        {
            result = Vector3(
                a.Y * b.Z - a.Z * b.Y,
                a.Z * b.X - a.X * b.Z,
                a.X * b.Y - a.Y * b.X);
        }

        static void Add(const Vector3& a, const Vector3& b, Vector3& result)
        {
            result.X = a.X + b.X;
            result.Y = a.Y + b.Y;
            result.Z = a.Z + b.Z;
        }

        static Vector3 Add(const Vector3& a, const Vector3& b)
        {
            Vector3 result;
            Add(a, b, result);
            return result;
        }

        static void Subtract(const Vector3& a, const Vector3& b, Vector3& result)
        {
            result.X = a.X - b.X;
            result.Y = a.Y - b.Y;
            result.Z = a.Z - b.Z;
        }

        static Vector3 Subtract(const Vector3& a, const Vector3& b)
        {
            Vector3 result;
            Subtract(a, b, result);
            return result;
        }

        static Vector3 Multiply(const Vector3& a, const Vector3& b)
        {
            return Vector3(a.X * b.X, a.Y * b.Y, a.Z * b.Z);
        }

        static void Multiply(const Vector3& a, const Vector3& b, Vector3& result)
        {
            result = Vector3(a.X * b.X, a.Y * b.Y, a.Z * b.Z);
        }

        static Vector3 Multiply(const Vector3& a, float b)
        {
            return Vector3(a.X * b, a.Y * b, a.Z * b);
        }

        static Vector3 Divide(const Vector3& a, const Vector3& b)
        {
            return Vector3(a.X / b.X, a.Y / b.Y, a.Z / b.Z);
        }

        static void Divide(const Vector3& a, const Vector3& b, Vector3& result)
        {
            result = Vector3(a.X / b.X, a.Y / b.Y, a.Z / b.Z);
        }

        static Vector3 Divide(const Vector3& a, float b)
        {
            return Vector3(a.X / b, a.Y / b, a.Z / b);
        }

    public:

        // Transforms a 3D vector by the given Quaternion rotation
        // @param vector The vector to rotate
        // @param rotation The Quaternion rotation to apply
        // @returns The transformed Vector4
        static Vector3 Transform(const Vector3& vector, const Quaternion& rotation);

	public:

		static const Vector3 Zero;
		static const Vector3 One;
        static const Vector3 Up;
        static const Vector3 Down;
        static const Vector3 Left;
        static const Vector3 Right;
        static const Vector3 Forward;
        static const Vector3 Backward;
	};
}
