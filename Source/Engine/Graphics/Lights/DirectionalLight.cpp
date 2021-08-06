#include "DirectionalLight.h"

using namespace DawnEngine;


Math::Matrix4x4 DirectionalLight::GetProjectionMatrix()
{
	Math::Matrix4x4 result;
	Math::Matrix4x4::Ortho(8.0f, 8.0f, 0.01f, 1000.0f, result);
	return result;
}

Math::Matrix4x4 DirectionalLight::GetViewMatrix()
{
	auto result = Transform.GetWorldMatrix();
	result.Invert();
	return result;
}