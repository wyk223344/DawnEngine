#pragma once

#include "Engine/Core/Include.h"
#include "Engine/Engine/Base/ComponentBase.h"

namespace DawnEngine
{
	class CameraComponent : ComponentBase
	{
	public:



	private:

		float m_FOV;
		float m_AspectRatio;
		float m_NearClip;
		float m_FarClip;

		Math::Matrix4x4 m_ViewMatrix;
		Math::Matrix4x4 m_ProjMatrix;
	};
}