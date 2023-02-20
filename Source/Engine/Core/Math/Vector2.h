#pragma once

#include "Common.h"

namespace DawnEngine
{
	struct Vector3;
	struct Vector4;

	struct Vector2
	{
	public:
		union
		{
			struct
			{
				float X;
				float Y;
			};
			float Raw[2];
		};

	public:

        Vector2()
            : X(0)
            , Y(0)
        {
        }

		Vector2(float xy)
			: X(xy)
			, Y(xy)
		{
		}

		Vector2(float x, float y)
			: X(x)
			, Y(y)
		{
		}

    public:  // ²Ù×÷·ûÖØÐ´

        Vector2 operator+(const Vector2& b) const
        {
            return Add(*this, b);
        }

        Vector2 operator-(const Vector2& b) const
        {
            return Subtract(*this, b);
        }

        Vector2 operator*(const Vector2& b) const
        {
            return Multiply(*this, b);
        }

        Vector2 operator/(const Vector2& b) const
        {
            return Divide(*this, b);
        }

        Vector2 operator-() const
        {
            return Vector2(-X, -Y);
        }

        Vector2& operator+=(const Vector2& b)
        {
            *this = Add(*this, b);
            return *this;
        }

        Vector2& operator-=(const Vector2& b)
        {
            *this = Subtract(*this, b);
            return *this;
        }

        Vector2& operator*=(const Vector2& b)
        {
            *this = Multiply(*this, b);
            return *this;
        }

        Vector2& operator/=(const Vector2& b)
        {
            *this = Divide(*this, b);
            return *this;
        }

        Vector2 operator+(float b) const
        {
            return Add(*this, b);
        }

        Vector2 operator-(float b) const
        {
            return Subtract(*this, b);
        }

        Vector2 operator*(float b) const
        {
            return Multiply(*this, b);
        }

        Vector2 operator/(float b) const
        {
            return Divide(*this, b);
        }

        Vector2& operator+=(float b)
        {
            *this = Add(*this, b);
            return *this;
        }

        Vector2& operator-=(float b)
        {
            *this = Subtract(*this, b);
            return *this;
        }

        Vector2& operator*=(float b)
        {
            *this = Multiply(*this, b);
            return *this;
        }

        Vector2& operator/=(float b)
        {
            *this = Divide(*this, b);
            return *this;
        }

        bool operator==(const Vector2& b) const
        {
            return X == b.X && Y == b.Y;
        }

        bool operator!=(const Vector2& b) const
        {
            return X != b.X || Y != b.Y;
        }

        bool operator>(const Vector2& b) const
        {
            return X > b.X && Y > b.Y;
        }

        bool operator>=(const Vector2& b) const
        {
            return X >= b.X && Y >= b.Y;
        }

        bool operator<(const Vector2& b) const
        {
            return X < b.X&& Y < b.Y;
        }

        bool operator<=(const Vector2& b) const
        {
            return X <= b.X && Y <= b.Y;
        }

	public: // ¾²Ì¬º¯Êý

        static float Dot(const Vector2& a, const Vector2& b)
        {
            return a.X * b.X + a.Y * b.Y;
        }

        static float Cross(const Vector2& a, const Vector2& b)
        {
            return a.X * b.Y - a.Y * b.X;
        }

        static void Add(const Vector2& a, const Vector2& b, Vector2& result)
        {
            result.X = a.X + b.X;
            result.Y = a.Y + b.Y;
        }

        static Vector2 Add(const Vector2& a, const Vector2& b)
        {
            Vector2 result;
            Add(a, b, result);
            return result;
        }

        static void Subtract(const Vector2& a, const Vector2& b, Vector2& result)
        {
            result.X = a.X - b.X;
            result.Y = a.Y - b.Y;
        }

        static Vector2 Subtract(const Vector2& a, const Vector2& b)
        {
            Vector2 result;
            Subtract(a, b, result);
            return result;
        }

        static Vector2 Multiply(const Vector2& a, const Vector2& b)
        {
            return Vector2(a.X * b.X, a.Y * b.Y);
        }

        static Vector2 Multiply(const Vector2& a, float b)
        {
            return Vector2(a.X * b, a.Y * b);
        }

        static Vector2 Divide(const Vector2& a, const Vector2& b)
        {
            return Vector2(a.X / b.X, a.Y / b.Y);
        }

        static Vector2 Divide(const Vector2& a, float b)
        {
            return Vector2(a.X / b, a.Y / b);
        }

	public:

		static const Vector2 Zero;
		static const Vector2 One;
	};
}