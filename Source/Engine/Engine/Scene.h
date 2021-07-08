#pragma once

#include "Engine/Engine/Base/EntityBase.h"

namespace DawnEngine
{

	class Scene
	{
	public:

		static Scene* CreateScene();

	public:

		Scene();

		// 获取根节点
		EntityBase* GetRootEntity() const { return m_RootEntity; }

	private:

		EntityBase* m_RootEntity;
	};
}