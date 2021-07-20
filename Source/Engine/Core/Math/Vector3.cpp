
#include "Vector3.h"
#include "Quaternion.h"


using namespace DawnEngine::Math;

const Vector3 Vector3::Zero(0.0f);
const Vector3 Vector3::One(1.0f);
const Vector3 Vector3::Up(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::Down(0.0f, -1.0f, 0.0f);
const Vector3 Vector3::Left(-1.0f, 0.0f, 0.0f);
const Vector3 Vector3::Right(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::Forward(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::Backward(0.0f, 0.0f, -1.0f);


Vector3 Vector3::Transform(const Vector3& vector, const Quaternion& rotation)
{
	const float x = rotation.X + rotation.X;
	const float y = rotation.Y + rotation.Y;
	const float z = rotation.Z + rotation.Z;
    const float wx = rotation.W * x;
    const float wy = rotation.W * y;
    const float wz = rotation.W * z;
    const float xx = rotation.X * x;
    const float xy = rotation.X * y;
    const float xz = rotation.X * z;
    const float yy = rotation.Y * y;
    const float yz = rotation.Y * z;
    const float zz = rotation.Z * z;

    return Vector3(
        vector.X * (1.0f - yy - zz) + vector.Y * (xy - wz) + vector.Z * (xz + wy),
        vector.X * (xy + wz) + vector.Y * (1.0f - xx - zz) + vector.Z * (yz - wx),
        vector.X * (xz - wy) + vector.Y * (yz + wx) + vector.Z * (1.0f - xx - yy));
}