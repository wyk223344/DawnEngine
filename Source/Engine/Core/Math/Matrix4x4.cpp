#include "Matrix4x4.h"
#include "Vector3.h"

using namespace DawnEngine;

const Matrix4x4 Matrix4x4::Zero(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
const Matrix4x4 Matrix4x4::Identity(
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f);

Matrix4x4 Matrix4x4::Transpose(const Matrix4x4& value)
{
    Matrix4x4 result;
    result.M11 = value.M11;
    result.M12 = value.M21;
    result.M13 = value.M31;
    result.M14 = value.M41;
    result.M21 = value.M12;
    result.M22 = value.M22;
    result.M23 = value.M32;
    result.M24 = value.M42;
    result.M31 = value.M13;
    result.M32 = value.M23;
    result.M33 = value.M33;
    result.M34 = value.M43;
    result.M41 = value.M14;
    result.M42 = value.M24;
    result.M43 = value.M34;
    result.M44 = value.M44;
    return result;
}

void Matrix4x4::Transpose(const Matrix4x4& value, Matrix4x4& result)
{
    Matrix4x4 temp;
    temp.M11 = value.M11;
    temp.M12 = value.M21;
    temp.M13 = value.M31;
    temp.M14 = value.M41;
    temp.M21 = value.M12;
    temp.M22 = value.M22;
    temp.M23 = value.M32;
    temp.M24 = value.M42;
    temp.M31 = value.M13;
    temp.M32 = value.M23;
    temp.M33 = value.M33;
    temp.M34 = value.M43;
    temp.M41 = value.M14;
    temp.M42 = value.M24;
    temp.M43 = value.M34;
    temp.M44 = value.M44;
    result = temp;
}

void Matrix4x4::Invert(const Matrix4x4& value, Matrix4x4& result)
{
    const float b0 = value.M31 * value.M42 - value.M32 * value.M41;
    const float b1 = value.M31 * value.M43 - value.M33 * value.M41;
    const float b2 = value.M34 * value.M41 - value.M31 * value.M44;
    const float b3 = value.M32 * value.M43 - value.M33 * value.M42;
    const float b4 = value.M34 * value.M42 - value.M32 * value.M44;
    const float b5 = value.M33 * value.M44 - value.M34 * value.M43;

    const float d11 = value.M22 * b5 + value.M23 * b4 + value.M24 * b3;
    const float d12 = value.M21 * b5 + value.M23 * b2 + value.M24 * b1;
    const float d13 = value.M21 * -b4 + value.M22 * b2 + value.M24 * b0;
    const float d14 = value.M21 * b3 + value.M22 * -b1 + value.M23 * b0;

    float det = value.M11 * d11 - value.M12 * d12 + value.M13 * d13 - value.M14 * d14;
    if (Math::Abs(det) <= 1e-12f)
    {
        result = Zero;
        return;
    }

    det = 1.0f / det;

    const float a0 = value.M11 * value.M22 - value.M12 * value.M21;
    const float a1 = value.M11 * value.M23 - value.M13 * value.M21;
    const float a2 = value.M14 * value.M21 - value.M11 * value.M24;
    const float a3 = value.M12 * value.M23 - value.M13 * value.M22;
    const float a4 = value.M14 * value.M22 - value.M12 * value.M24;
    const float a5 = value.M13 * value.M24 - value.M14 * value.M23;

    const float d21 = value.M12 * b5 + value.M13 * b4 + value.M14 * b3;
    const float d22 = value.M11 * b5 + value.M13 * b2 + value.M14 * b1;
    const float d23 = value.M11 * -b4 + value.M12 * b2 + value.M14 * b0;
    const float d24 = value.M11 * b3 + value.M12 * -b1 + value.M13 * b0;

    const float d31 = value.M42 * a5 + value.M43 * a4 + value.M44 * a3;
    const float d32 = value.M41 * a5 + value.M43 * a2 + value.M44 * a1;
    const float d33 = value.M41 * -a4 + value.M42 * a2 + value.M44 * a0;
    const float d34 = value.M41 * a3 + value.M42 * -a1 + value.M43 * a0;

    const float d41 = value.M32 * a5 + value.M33 * a4 + value.M34 * a3;
    const float d42 = value.M31 * a5 + value.M33 * a2 + value.M34 * a1;
    const float d43 = value.M31 * -a4 + value.M32 * a2 + value.M34 * a0;
    const float d44 = value.M31 * a3 + value.M32 * -a1 + value.M33 * a0;

    result.M11 = +d11 * det;
    result.M12 = -d21 * det;
    result.M13 = +d31 * det;
    result.M14 = -d41 * det;
    result.M21 = -d12 * det;
    result.M22 = +d22 * det;
    result.M23 = -d32 * det;
    result.M24 = +d42 * det;
    result.M31 = +d13 * det;
    result.M32 = -d23 * det;
    result.M33 = +d33 * det;
    result.M34 = -d43 * det;
    result.M41 = -d14 * det;
    result.M42 = +d24 * det;
    result.M43 = -d34 * det;
    result.M44 = +d44 * det;
}

void Matrix4x4::Transformation(const Vector3& translation, const Quaternion& rotation, const Vector3& scale, Matrix4x4& result)
{
    // Rotation
    const float xx = rotation.X * rotation.X;
    const float yy = rotation.Y * rotation.Y;
    const float zz = rotation.Z * rotation.Z;
    const float xy = rotation.X * rotation.Y;
    const float zw = rotation.Z * rotation.W;
    const float zx = rotation.Z * rotation.X;
    const float yw = rotation.Y * rotation.W;
    const float yz = rotation.Y * rotation.Z;
    const float xw = rotation.X * rotation.W;
    result.M11 = 1.0f - 2.0f * (yy + zz);
    result.M12 = 2.0f * (xy + zw);
    result.M13 = 2.0f * (zx - yw);
    result.M21 = 2.0f * (xy - zw);
    result.M22 = 1.0f - 2.0f * (zz + xx);
    result.M23 = 2.0f * (yz + xw);
    result.M31 = 2.0f * (zx + yw);
    result.M32 = 2.0f * (yz - xw);
    result.M33 = 1.0f - 2.0f * (yy + xx);

    // Position
    result.M41 = translation.X;
    result.M42 = translation.Y;
    result.M43 = translation.Z;

    // Scale
    result.M11 *= scale.X;
    result.M12 *= scale.X;
    result.M13 *= scale.X;
    result.M21 *= scale.Y;
    result.M22 *= scale.Y;
    result.M23 *= scale.Y;
    result.M31 *= scale.Z;
    result.M32 *= scale.Z;
    result.M33 *= scale.Z;

    result.M14 = 0.0f;
    result.M24 = 0.0f;
    result.M34 = 0.0f;
    result.M44 = 1.0f;

}

void Matrix4x4::LookAt(const Vector3& eye, const Vector3& target, const Vector3& up, Matrix4x4& result)
{
    Vector3 xaxis, yaxis, zaxis;
    Vector3::Subtract(target, eye, zaxis);
    zaxis.Normalize();
    Vector3::Cross(up, zaxis, xaxis);
    xaxis.Normalize();
    Vector3::Cross(zaxis, xaxis, yaxis);

    result = Identity;

    result.M11 = xaxis.X;
    result.M21 = xaxis.Y;
    result.M31 = xaxis.Z;

    result.M12 = yaxis.X;
    result.M22 = yaxis.Y;
    result.M32 = yaxis.Z;

    result.M13 = zaxis.X;
    result.M23 = zaxis.Y;
    result.M33 = zaxis.Z;

    result.M41 = -Vector3::Dot(xaxis, eye);
    result.M42 = -Vector3::Dot(yaxis, eye);
    result.M43 = -Vector3::Dot(zaxis, eye);
}

void Matrix4x4::PerspectiveFov(float fov, float aspect, float zNear, float zFar, Matrix4x4& result)
{
    const float yScale = 1.0f / Math::Tan(fov * 0.5f);
    const float xScale = yScale / aspect;

    const float halfWidth = zNear / xScale;
    const float halfHeight = zNear / yScale;

    PerspectiveOffCenter(-halfWidth, halfWidth, -halfHeight, halfHeight, zNear, zFar, result);
}

void Matrix4x4::PerspectiveOffCenter(float left, float right, float bottom, float top, float zNear, float zFar, Matrix4x4& result)
{
    const float zRange = zFar / (zFar - zNear);

    result = Zero;
    result.M11 = 2.0f * zNear / (right - left);
    result.M22 = 2.0f * zNear / (top - bottom);
    result.M31 = (left + right) / (left - right);
    result.M32 = (top + bottom) / (bottom - top);
    result.M33 = zRange;
    result.M34 = 1.0f;
    result.M43 = -zNear * zRange;

}


void Matrix4x4::OrthoOffCenter(float left, float right, float bottom, float top, float zNear, float zFar, Matrix4x4& result)
{
    const float zRange = 1.0f / (zFar - zNear);

    result = Identity;
    result.M11 = 2.0f / (right - left);
    result.M22 = 2.0f / (top - bottom);
    result.M33 = zRange;
    result.M41 = (left + right) / (left - right);
    result.M42 = (top + bottom) / (bottom - top);
    result.M43 = -zNear * zRange;
}