
#include "Transform.h"
#include "Matrix4x4.h"
#include "Vector3.h"
#include "Quaternion.h"

using namespace DawnEngine::Math;


void Transform::LookAt(const Vector3& target)
{
	Matrix4x4 matrix;
	Matrix4x4::LookAt(Translation, target, Vector3::Up, matrix);
	Quaternion::RotationMatrix(matrix, Rotation);

}

Matrix4x4 Transform::GetWorldMatrix() const
{
	Matrix4x4 result;
	Matrix4x4::Transformation(Translation, Rotation, Scale, result);
	return result;
}