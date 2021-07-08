#pragma once

#include "Engine/Core/Object.h"


namespace DawnEngine
{
	class EntityBase;

	class ComponentBase : Object
	{
		friend EntityBase;

	public:

		ComponentBase(EntityBase* entity)
			: m_Owner(entity)
			, m_IsStarted(false)
		{
		}

		EntityBase* GetEntity() const { return m_Owner; }

		bool IsStarted() const{ return m_IsStarted; }

	protected:

		virtual void Awake() {}

		virtual void Start() { m_IsStarted = true; }

		virtual void Update() {}

		virtual void LateUpdate() {}

		virtual void OnDestroy() {}

	private:

		EntityBase* m_Owner;
		bool m_IsStarted;
	};
}