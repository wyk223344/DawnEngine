#pragma once

#include "Engine/Core/Object.h"


namespace DawnEngine
{
	class EntityBase;

	class ComponentBase : Object
	{
	public:

		ComponentBase(EntityBase* entity)
			: m_Owner(entity)
		{
		}

		EntityBase* GetEntity() const { return m_Owner; }

	private:

		EntityBase* m_Owner;
	};
}