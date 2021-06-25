#include "Matrix4x4.h"


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