
#include "Scene.h"
#include "Engine/Engine/Engine.h"
#include "Engine/Engine/EngineService.h"
#include "Engine/Core/Include.h"
#include "Engine/Engine/Base/EntityBase.h"

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


Scene* Scene::CreateScene()
{
    return New<Scene>();
}

Scene::Scene()
{
    m_RootEntity = New<EntityBase>();
}