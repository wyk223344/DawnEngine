#pragma once

#include "LightBase.h"
#include "Engine/Core/Include.h"

namespace DawnEngine
{
	class DirectionalLight : public LightBase
	{
	public:

		Math::Matrix4x4 GetProjectionMatrix();

		Math::Matrix4x4 GetViewMatrix();

	public:

		Math::Transform Transform;
		Color LightColor;
	};
}