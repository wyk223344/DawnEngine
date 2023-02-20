
#include "Transform.h"
#include "Matrix4x4.h"
#include "Vector3.h"
#include "Quaternion.h"

using namespace DawnEngine;


void Transform::LookAt(const Vector3& target, const Vector3& up)
{
	Matrix4x4 matrix;
	Matrix4x4::LookAt(Translation, target, up, matrix);
	matrix.Invert();
	Quaternion::RotationMatrix(matrix, Rotation);

}

Matrix4x4 Transform::GetWorldMatrix() const
{
	Matrix4x4 result;
	Matrix4x4::Transformation(Translation, Rotation, Scale, result);
	return result;
}