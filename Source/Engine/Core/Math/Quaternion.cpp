#include "Quaternion.h"
#include "Matrix4x4.h"

using namespace DawnEngine::Math;

Quaternion Quaternion::Zero(0);
Quaternion Quaternion::One(1);
Quaternion Quaternion::Identity(0, 0, 0, 1);


void Quaternion::RotationMatrix(const Matrix4x4& matrix, Quaternion& result)
{
    float sqrtV;
    float half;
    const float scale = matrix.M11 + matrix.M22 + matrix.M33;

    if (scale > 0.0f)
    {
        sqrtV = Math::Sqrt(scale + 1.0f);
        result.W = sqrtV * 0.5f;
        sqrtV = 0.5f / sqrtV;

        result.X = (matrix.M23 - matrix.M32) * sqrtV;
        result.Y = (matrix.M31 - matrix.M13) * sqrtV;
        result.Z = (matrix.M12 - matrix.M21) * sqrtV;
    }
    else if (matrix.M11 >= matrix.M22 && matrix.M11 >= matrix.M33)
    {
        sqrtV = Math::Sqrt(1.0f + matrix.M11 - matrix.M22 - matrix.M33);
        half = 0.5f / sqrtV;

        result = Quaternion(
            0.5f * sqrtV,
            (matrix.M12 + matrix.M21) * half,
            (matrix.M13 + matrix.M31) * half,
            (matrix.M23 - matrix.M32) * half);
    }
    else if (matrix.M22 > matrix.M33)
    {
        sqrtV = Math::Sqrt(1.0f + matrix.M22 - matrix.M11 - matrix.M33);
        half = 0.5f / sqrtV;

        result = Quaternion(
            (matrix.M21 + matrix.M12) * half,
            0.5f * sqrtV,
            (matrix.M32 + matrix.M23) * half,
            (matrix.M31 - matrix.M13) * half);
    }
    else
    {
        sqrtV = Math::Sqrt(1.0f + matrix.M33 - matrix.M11 - matrix.M22);
        half = 0.5f / sqrtV;

        result = Quaternion(
            (matrix.M31 + matrix.M13) * half,
            (matrix.M32 + matrix.M23) * half,
            0.5f * sqrtV,
            (matrix.M12 - matrix.M21) * half);
    }

    result.Normalize();
}