#pragma once

#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"
#include <assert.h>


namespace DawnEngine::Math
{
	struct Transform;

	struct Matrix4x4
	{
	public:

		union
		{
			struct
			{
				float M11;
				float M12;
				float M13;
				float M14;
				float M21;
				float M22;
				float M23;
				float M24;
				float M31;
				float M32;
				float M33;
				float M34;
				float M41;
				float M42;
				float M43;
				float M44;
			};
			float Values[4][4];
			float Raw[16];
		};

	public:

		static const Matrix4x4 Zero;

		static const Matrix4x4 Identity;

	public:

		Matrix4x4()
			: M11(0)
			, M12(0)
			, M13(0)
			, M14(0)
			, M21(0)
			, M22(0)
			, M23(0)
			, M24(0)
			, M31(0)
			, M32(0)
			, M33(0)
			, M34(0)
			, M41(0)
			, M42(0)
			, M43(0)
			, M44(0)
		{
		}

		Matrix4x4(float m11, float m12, float m13, float m14,
			float m21, float m22, float m23, float m24,
			float m31, float m32, float m33, float m34,
			float m41, float m42, float m43, float m44)
			: M11(m11)
			, M12(m12)
			, M13(m13)
			, M14(m14)
			, M21(m21)
			, M22(m22)
			, M23(m23)
			, M24(m24)
			, M31(m31)
			, M32(m32)
			, M33(m33)
			, M34(m34)
			, M41(m41)
			, M42(m42)
			, M43(m43)
			, M44(m44)
		{
		}
    
    public:

        void Invert()
        {
            Invert(*this, *this);
        }

        void Transpose()
        {
            Transpose(*this, *this);
        }

    public:

        Matrix4x4 operator*(const float scale) const
        {
            Matrix4x4 result;
            Multiply(*this, scale, result);
            return result;
        }

        Matrix4x4 operator*(const Matrix4x4& other) const
        {
            Matrix4x4 result;
            Multiply(*this, other, result);
            return result;
        }

        Matrix4x4& operator+=(const Matrix4x4& other)
        {
            Add(*this, other, *this);
            return *this;
        }

        Matrix4x4& operator-=(const Matrix4x4& other)
        {
            Subtract(*this, other, *this);
            return *this;
        }

        Matrix4x4& operator*=(const Matrix4x4& other)
        {
            const Matrix4x4 tmp = *this;
            Multiply(tmp, other, *this);
            return *this;
        }

        Matrix4x4& operator*=(const float scale)
        {
            Multiply(*this, scale, *this);
            return *this;
        }

        bool operator==(const Matrix4x4& other) const
        {
            for (int32 i = 0; i < 16; i++)
            {
                if (Math::NotNearEqual(other.Raw[i], Raw[i]))
                    return false;
            }
            return true;
        }

        bool operator!=(const Matrix4x4& other) const
        {
            for (int32 i = 0; i < 16; i++)
            {
                if (Math::NotNearEqual(other.Raw[i], Raw[i]))
                    return true;
            }
            return false;
        }

	public:

        static void Add(const Matrix4x4& left, const Matrix4x4& right, Matrix4x4& result)
        {
            result.M11 = left.M11 + right.M11;
            result.M12 = left.M12 + right.M12;
            result.M13 = left.M13 + right.M13;
            result.M14 = left.M14 + right.M14;
            result.M21 = left.M21 + right.M21;
            result.M22 = left.M22 + right.M22;
            result.M23 = left.M23 + right.M23;
            result.M24 = left.M24 + right.M24;
            result.M31 = left.M31 + right.M31;
            result.M32 = left.M32 + right.M32;
            result.M33 = left.M33 + right.M33;
            result.M34 = left.M34 + right.M34;
            result.M41 = left.M41 + right.M41;
            result.M42 = left.M42 + right.M42;
            result.M43 = left.M43 + right.M43;
            result.M44 = left.M44 + right.M44;
        }

        static void Subtract(const Matrix4x4& left, const Matrix4x4& right, Matrix4x4& result)
        {
            result.M11 = left.M11 - right.M11;
            result.M12 = left.M12 - right.M12;
            result.M13 = left.M13 - right.M13;
            result.M14 = left.M14 - right.M14;
            result.M21 = left.M21 - right.M21;
            result.M22 = left.M22 - right.M22;
            result.M23 = left.M23 - right.M23;
            result.M24 = left.M24 - right.M24;
            result.M31 = left.M31 - right.M31;
            result.M32 = left.M32 - right.M32;
            result.M33 = left.M33 - right.M33;
            result.M34 = left.M34 - right.M34;
            result.M41 = left.M41 - right.M41;
            result.M42 = left.M42 - right.M42;
            result.M43 = left.M43 - right.M43;
            result.M44 = left.M44 - right.M44;
        }

        static void Multiply(const Matrix4x4& left, float right, Matrix4x4& result)
        {
            result.M11 = left.M11 * right;
            result.M12 = left.M12 * right;
            result.M13 = left.M13 * right;
            result.M14 = left.M14 * right;
            result.M21 = left.M21 * right;
            result.M22 = left.M22 * right;
            result.M23 = left.M23 * right;
            result.M24 = left.M24 * right;
            result.M31 = left.M31 * right;
            result.M32 = left.M32 * right;
            result.M33 = left.M33 * right;
            result.M34 = left.M34 * right;
            result.M41 = left.M41 * right;
            result.M42 = left.M42 * right;
            result.M43 = left.M43 * right;
            result.M44 = left.M44 * right;
        }

        static Matrix4x4 Multiply(const Matrix4x4& left, const Matrix4x4& right)
        {
            Matrix4x4 result;
            Multiply(left, right, result);
            return result;
        }

        static void Multiply(const Matrix4x4& left, const Matrix4x4& right, Matrix4x4& result)
        {
            result.M11 = left.M11 * right.M11 + left.M12 * right.M21 + left.M13 * right.M31 + left.M14 * right.M41;
            result.M12 = left.M11 * right.M12 + left.M12 * right.M22 + left.M13 * right.M32 + left.M14 * right.M42;
            result.M13 = left.M11 * right.M13 + left.M12 * right.M23 + left.M13 * right.M33 + left.M14 * right.M43;
            result.M14 = left.M11 * right.M14 + left.M12 * right.M24 + left.M13 * right.M34 + left.M14 * right.M44;
            result.M21 = left.M21 * right.M11 + left.M22 * right.M21 + left.M23 * right.M31 + left.M24 * right.M41;
            result.M22 = left.M21 * right.M12 + left.M22 * right.M22 + left.M23 * right.M32 + left.M24 * right.M42;
            result.M23 = left.M21 * right.M13 + left.M22 * right.M23 + left.M23 * right.M33 + left.M24 * right.M43;
            result.M24 = left.M21 * right.M14 + left.M22 * right.M24 + left.M23 * right.M34 + left.M24 * right.M44;
            result.M31 = left.M31 * right.M11 + left.M32 * right.M21 + left.M33 * right.M31 + left.M34 * right.M41;
            result.M32 = left.M31 * right.M12 + left.M32 * right.M22 + left.M33 * right.M32 + left.M34 * right.M42;
            result.M33 = left.M31 * right.M13 + left.M32 * right.M23 + left.M33 * right.M33 + left.M34 * right.M43;
            result.M34 = left.M31 * right.M14 + left.M32 * right.M24 + left.M33 * right.M34 + left.M34 * right.M44;
            result.M41 = left.M41 * right.M11 + left.M42 * right.M21 + left.M43 * right.M31 + left.M44 * right.M41;
            result.M42 = left.M41 * right.M12 + left.M42 * right.M22 + left.M43 * right.M32 + left.M44 * right.M42;
            result.M43 = left.M41 * right.M13 + left.M42 * right.M23 + left.M43 * right.M33 + left.M44 * right.M43;
            result.M44 = left.M41 * right.M14 + left.M42 * right.M24 + left.M43 * right.M34 + left.M44 * right.M44;
        }

        static void Divide(const Matrix4x4& left, float right, Matrix4x4& result)
        {
            assert(!Math::IsZero(right));
            const float inv = 1.0f / right;

            result.M11 = left.M11 * inv;
            result.M12 = left.M12 * inv;
            result.M13 = left.M13 * inv;
            result.M14 = left.M14 * inv;
            result.M21 = left.M21 * inv;
            result.M22 = left.M22 * inv;
            result.M23 = left.M23 * inv;
            result.M24 = left.M24 * inv;
            result.M31 = left.M31 * inv;
            result.M32 = left.M32 * inv;
            result.M33 = left.M33 * inv;
            result.M34 = left.M34 * inv;
            result.M41 = left.M41 * inv;
            result.M42 = left.M42 * inv;
            result.M43 = left.M43 * inv;
            result.M44 = left.M44 * inv;
        }

        static void Divide(const Matrix4x4& left, const Matrix4x4& right, Matrix4x4& result)
        {
            result.M11 = left.M11 / right.M11;
            result.M12 = left.M12 / right.M12;
            result.M13 = left.M13 / right.M13;
            result.M14 = left.M14 / right.M14;
            result.M21 = left.M21 / right.M21;
            result.M22 = left.M22 / right.M22;
            result.M23 = left.M23 / right.M23;
            result.M24 = left.M24 / right.M24;
            result.M31 = left.M31 / right.M31;
            result.M32 = left.M32 / right.M32;
            result.M33 = left.M33 / right.M33;
            result.M34 = left.M34 / right.M34;
            result.M41 = left.M41 / right.M41;
            result.M42 = left.M42 / right.M42;
            result.M43 = left.M43 / right.M43;
            result.M44 = left.M44 / right.M44;
        }

        static void Negate(const Matrix4x4& value, Matrix4x4& result)
        {
            result.M11 = -value.M11;
            result.M12 = -value.M12;
            result.M13 = -value.M13;
            result.M14 = -value.M14;
            result.M21 = -value.M21;
            result.M22 = -value.M22;
            result.M23 = -value.M23;
            result.M24 = -value.M24;
            result.M31 = -value.M31;
            result.M32 = -value.M32;
            result.M33 = -value.M33;
            result.M34 = -value.M34;
            result.M41 = -value.M41;
            result.M42 = -value.M42;
            result.M43 = -value.M43;
            result.M44 = -value.M44;
        }

        static void Lerp(const Matrix4x4& start, const Matrix4x4& end, float amount, Matrix4x4& result)
        {
            result.M11 = Math::Lerp(start.M11, end.M11, amount);
            result.M12 = Math::Lerp(start.M12, end.M12, amount);
            result.M13 = Math::Lerp(start.M13, end.M13, amount);
            result.M14 = Math::Lerp(start.M14, end.M14, amount);
            result.M21 = Math::Lerp(start.M21, end.M21, amount);
            result.M22 = Math::Lerp(start.M22, end.M22, amount);
            result.M23 = Math::Lerp(start.M23, end.M23, amount);
            result.M24 = Math::Lerp(start.M24, end.M24, amount);
            result.M31 = Math::Lerp(start.M31, end.M31, amount);
            result.M32 = Math::Lerp(start.M32, end.M32, amount);
            result.M33 = Math::Lerp(start.M33, end.M33, amount);
            result.M34 = Math::Lerp(start.M34, end.M34, amount);
            result.M41 = Math::Lerp(start.M41, end.M41, amount);
            result.M42 = Math::Lerp(start.M42, end.M42, amount);
            result.M43 = Math::Lerp(start.M43, end.M43, amount);
            result.M44 = Math::Lerp(start.M44, end.M44, amount);
        }

        static void SmoothStep(const Matrix4x4& start, const Matrix4x4& end, float amount, Matrix4x4& result)
        {
            amount = Math::SmoothStep(amount);
            Lerp(start, end, amount, result);
        }

        static Matrix4x4 Transpose(const Matrix4x4& value);

        static void Transpose(const Matrix4x4& value, Matrix4x4& result);

        static Matrix4x4 Invert(const Matrix4x4& value)
        {
            Matrix4x4 result;
            Invert(value, result);
            return result;
        }

        static void Invert(const Matrix4x4& value, Matrix4x4& result);

	public:

		// 通过transform中的坐标、角度、缩放构建转换矩阵
		static void Transformation(const Vector3& translation, const Quaternion& rotation, const Vector3& scale, Matrix4x4& result);

        // 根据Look At信息构建矩阵
        static void LookAt(const Vector3& eye, const Vector3& target, const Vector3& up, Matrix4x4& result);
	
        // 构建透视矩阵
        static void PerspectiveFov(float fov, float aspect, float zNear, float zFar, Matrix4x4& result);
    
        // 构建透视矩阵
        static void PerspectiveOffCenter(float left, float right, float bottom, float top, float zNear, float zFar, Matrix4x4& result);
    
        // 构建正交矩阵
        static void Ortho(float width, float height, float zNear, float zFar, Matrix4x4& result)
        {
            const float halfWidth = width * 0.5f;
            const float halfHeight = height * 0.5f;
            OrthoOffCenter(-halfWidth, halfWidth, -halfHeight, halfHeight, zNear, zFar, result);
        }

        // 构建正交矩阵
        static void OrthoOffCenter(float left, float right, float bottom, float top, float zNear, float zFar, Matrix4x4& result);
    };
}