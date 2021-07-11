#pragma once

#include "Engine/Core/Include.h"
#include "Engine/Engine/Base/ComponentBase.h"

namespace DawnEngine
{
	using namespace Math;

	class EntityBase;

	class CameraComponent : public ComponentBase
	{
	public:

		CameraComponent(EntityBase* entity, float fov, float aspect, float zNear = 0.1f, float zFar = 10000.0f);

		Matrix4x4& GetProjectionMatrix();

		Matrix4x4& GetViewMatrix();

	private:

		float m_FOV;
		float m_AspectRatio;
		float m_NearClip;
		float m_FarClip;
	};
}