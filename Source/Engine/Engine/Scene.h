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

		// 获取根节点
		EntityBase* GetRootEntity() const { return m_RootEntity; }

		// 设置天空盒材质
		void SetSkyboxMaterial(MaterialBase* material);

		// 绘制天空盒
		void DrawSkybox(GPUContext* context);

	private:

		EntityBase* m_RootEntity;

		Mesh* m_SkyboxMesh;
		MaterialBase* m_SkyboxMaterial;
	};
}