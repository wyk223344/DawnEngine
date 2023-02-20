#pragma once

#include "LightBase.h"
#include "Engine/Core/Include.h"

namespace DawnEngine
{
	class DirectionalLight : public LightBase
	{
	public:

		Matrix4x4 GetProjectionMatrix();

		Matrix4x4 GetViewMatrix();

	public:

		Transform Transform;
		Color LightColor;
	};
}