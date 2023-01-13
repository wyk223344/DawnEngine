#pragma once

#include "Engine/Engine/EngineService.h"


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

	class SceneService : public EngineService
	{
	public:

		SceneService();

		bool Init() override;
		void Update() override;
		void LateUpdate() override;
		void Dispose() override;
	};
}