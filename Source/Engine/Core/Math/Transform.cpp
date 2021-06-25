
#include "Transform.h"
#include "Matrix4x4.h"


using namespace DawnEngine::Math;


Matrix4x4 Transform::GetWorldMatrix() const
{
	Matrix4x4 result;
	Matrix4x4::Transformation(Translation, Rotation, Scale, result);
	return result;
}