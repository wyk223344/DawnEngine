#pragma once

#include "Engine/Engine/Base/EntityBase.h"

namespace DawnEngine
{

	class Scene
	{
	public:

		EntityBase* GetRootEntity() const { return m_RootEntity; }

	private:

		EntityBase* m_RootEntity;
	};
}