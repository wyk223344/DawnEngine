

#include "Engine/Engine/Engine.h"
#include "Engine/Engine/EngineService.h"
#include "Scene.h"
#include "Engine/Core/Include.h"
#include "Engine/Engine/Base/EntityBase.h"
#include "Engine/Graphics/Models/GeometryGenerator.h"
#include "Engine/Graphics/Models/Mesh.h"
#include "Engine/Graphics/Materials/SkyboxMaterial.h"

using namespace DawnEngine;

#pragma region SceneService

class SceneService : public EngineService
{
public:

    SceneService()
        : EngineService(TEXT("Scene"), 40)
    {
    }

    bool Init() override;
    void Update() override;
    void LateUpdate() override;
    void Dispose() override;
};

SceneService SceneServiceInstance;

bool SceneService::Init()
{
    
    return true;
}

void SceneService::Update()
{
    auto rootEntity = Engine::MainScene->GetRootEntity();
    rootEntity->Update();
}

void SceneService::LateUpdate()
{
    auto rootEntity = Engine::MainScene->GetRootEntity();
    rootEntity->LateUpdate();
}

void SceneService::Dispose()
{
}

#pragma endregion


#pragma region Scene

Scene* Scene::CreateScene()
{
    return New<Scene>();
}

Scene::Scene()
{
    m_RootEntity = New<EntityBase>();
    MeshData* meshData = GeometryGenerator::CreateSphere(0.5f, 20, 20);
    m_SkyboxMesh = New<Mesh>();
    m_SkyboxMesh->Init(*meshData);
    Delete(meshData);
    m_SkyboxMaterial = nullptr;
}


void Scene::SetSkyboxMaterial(MaterialBase* material)
{
    m_SkyboxMaterial = material;
    material->InitGPUResource();
}


void Scene::DrawSkybox(GPUContext* context)
{
    if (m_SkyboxMaterial == nullptr)
    {
        return;
    }
    m_SkyboxMaterial->Draw(context);
    m_SkyboxMesh->Draw(context);
}

#pragma endregion