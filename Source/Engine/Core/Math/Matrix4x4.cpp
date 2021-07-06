#include "Matrix4x4.h"
#include "Vector3.h"

using namespace DawnEngine::Math;


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