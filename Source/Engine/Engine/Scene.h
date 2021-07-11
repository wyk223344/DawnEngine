#pragma once



namespace DawnEngine
{
	class EntityBase;

	class Scene
	{
	public:

		static Scene* CreateScene();

	public:

		Scene();

		// ��ȡ���ڵ�
		EntityBase* GetRootEntity() const { return m_RootEntity; }

	private:

		EntityBase* m_RootEntity;
	};
}