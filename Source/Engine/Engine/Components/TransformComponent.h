#pragma once

#include "Engine/Core/Include.h"
#include "Engine/Engine/Base/ComponentBase.h"

namespace DawnEngine
{
	using namespace Math;

	class EntityBase;

	REFLECTION_TYPE(TransformComponent)
	CLASS(TransformComponent : public ComponentBase)
	{
		REFLECTION_BODY(TransformComponent);

	public:

		TransformComponent(EntityBase* entity);

		void SetPosition(Vector3& position)
		{
			Transform.Translation = position;
		}

		void LookAt(const Vector3& target)
		{
			Transform.LookAt(target);
		}

	public:

		META(Enable)
		Transform Transform;
	};
}