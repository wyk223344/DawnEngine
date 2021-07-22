#pragma once



namespace DawnEngine
{
	class EntityBase;
	class MaterialBase;
	class Mesh;
	class GPUContext;

	class Scene
	{
	public:

		static Scene* CreateScene();

	public:

		Scene();

		// ��ȡ���ڵ�
		EntityBase* GetRootEntity() const { return m_RootEntity; }

		// ������պв���
		void SetSkyboxMaterial(MaterialBase* material);

		// ������պ�
		void DrawSkybox(GPUContext* context);

	private:

		EntityBase* m_RootEntity;

		Mesh* m_SkyboxMesh;
		MaterialBase* m_SkyboxMaterial;
	};
}