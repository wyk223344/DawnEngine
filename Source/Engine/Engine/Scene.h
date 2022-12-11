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

		// ????????
		EntityBase* GetRootEntity() const { return m_RootEntity; }

		// ???????§Ó???
		void SetSkyboxMaterial(MaterialBase* material);

		// ????????
		void DrawSkybox(GPUContext* context);

	public:

		EntityBase* m_RootEntity;

		Mesh* m_SkyboxMesh;
		MaterialBase* m_SkyboxMaterial;
	};
}