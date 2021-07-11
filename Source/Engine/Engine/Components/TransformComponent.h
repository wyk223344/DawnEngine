#pragma once

#include "Engine/Core/Include.h"
#include "Engine/Engine/Base/ComponentBase.h"

namespace DawnEngine
{
	using namespace DawnEngine::Math;

	class EntityBase;

	class TransformComponent : public ComponentBase
	{
	public:

		TransformComponent(EntityBase* entity);

		void SetPosition(Vector3& position)
		{
			Transform.Translation = position;
			LOG_INFO("SetPosition: (%d,%d,%d)", position.X, position.Y, position.Z);
		}

		void LookAt(const Vector3& target)
		{
			Transform.LookAt(target);
		}

	public:

		Transform Transform;
	};
}