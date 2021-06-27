#pragma once

#include "Engine/Engine/Base/EntityBase.h"

namespace DawnEngine
{

	class Scene
	{
	public:

		// ��ȡ���ڵ�
		EntityBase* GetRootEntity() const { return m_RootEntity; }

	private:

		EntityBase* m_RootEntity;
	};
}