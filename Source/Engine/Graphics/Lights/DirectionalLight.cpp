#include "DirectionalLight.h"

using namespace DawnEngine;


Matrix4x4 DirectionalLight::GetProjectionMatrix()
{
	Matrix4x4 result;
	Matrix4x4::Ortho(8.0f, 8.0f, 0.01f, 1000.0f, result);
	return result;
}

Matrix4x4 DirectionalLight::GetViewMatrix()
{
	auto result = Transform.GetWorldMatrix();
	result.Invert();
	return result;
}