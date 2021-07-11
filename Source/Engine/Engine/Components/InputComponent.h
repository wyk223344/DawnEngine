#pragma once

#include "Engine/Core/Include.h"
#include "Engine/Engine/Base/ComponentBase.h"

namespace DawnEngine
{
	using namespace Math;

	class EntityBase;

	class InputComponent : public ComponentBase
	{
	public:

		InputComponent(EntityBase* entity);
		
		void Update() override;

	private:

		Vector2 m_PrePosition;
		float m_Pitch = 0.0f;
		float m_Yaw = 0.0f;
	};
}