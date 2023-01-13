#include "Editor.h"
#include "EditorUI.h"
#include "Engine/Engine/Globals.h"
#include "Engine/Core/Include.h"
#include "Engine/Engine/Engine.h"
#include "Engine/Engine/Scene.h"
#include "Engine/Engine/Entities/CameraEntity.h"
#include "Engine/Engine/Entities/RenderEntity.h"
#include "Engine/Engine/Entities/LightEntity.h"
#include "Engine/Engine/Components/TransformComponent.h"
#include "Engine/Engine/Globals.h"
#include "Engine/Graphics/Models/Model.h"
#include "Engine/Graphics/Models/Mesh.h"
#include "Engine/Graphics/Models/GeometryGenerator.h"
#include "Engine/Graphics/Materials/DefaultMaterial.h"
#include "Engine/Graphics/Materials/PBRMaterial.h"
#include "Engine/Graphics/Materials/SkyboxMaterial.h"
#include "Engine/Resource/Resource.h"
#include "Engine/Graphics/Textures/TextureData.h"
#include "Engine/Renderer/Renderer.h"
#include "Engine/Gui/ImGuiHelper.h"
using namespace DawnEngine;


void InitCamera()
{
	// init camera
	auto cameraEntity = New<CameraEntity>(45.0f, (float)Globals::Width / Globals::Height);
	Vector3 startPosition(5.0f, 5.0f, 5.0f);
	cameraEntity->GetComponent<TransformComponent>()->SetPosition(startPosition);
	cameraEntity->GetComponent<TransformComponent>()->LookAt(Vector3::Zero);
}

void InitSkyBox()
{
	TextureData* textureData = Resource::LoadCubeMap("Assets/Textures/Skybox/");
	SkyboxMaterial* material = New<SkyboxMaterial>();
	material->CubeMap = textureData;
	Engine::MainScene->SetSkyboxMaterial(material);
	material->PreIntegrateCubemap(Renderer::GetRenderContext(), Engine::MainScene->m_SkyboxMesh);
}


// pbr≤‚ ‘≥°æ∞
void InitTestScene3()
{
	// init sphere
	MeshData* sphereMesh = GeometryGenerator::CreateSphere(1.0f, 100, 100);
	PBRMaterial* sphereMaterial = New<PBRMaterial>(Color::White);
	sphereMaterial->AlbedoTexture = Resource::LoadTexture("Assets/Textures/PBR/rusted_iron/albedo.png");
	sphereMaterial->NormalTexture = Resource::LoadTexture("Assets/Textures/PBR/rusted_iron/normal.png");
	sphereMaterial->MetallicTexture = Resource::LoadTexture("Assets/Textures/PBR/rusted_iron/metallic.png");
	sphereMaterial->RoughnessTexture = Resource::LoadTexture("Assets/Textures/PBR/rusted_iron/roughness.png");
	sphereMaterial->AOTexture = Resource::LoadTexture("Assets/Textures/PBR/rusted_iron/ao.png");
	Model* sphereModel = New<Model>();
	sphereModel->AddMeshAndMaterial(sphereMesh, sphereMaterial);
	auto sphereEntity = New<RenderEntity>(sphereModel);
	sphereEntity->GetComponent<TransformComponent>()->SetPosition(Vector3(0.0f, 1.0f, 0.0f));
	// init plane
	//MeshData* planeMesh = GeometryGenerator::CreatePlane(5.0f, 5.0f, 5, 5);
	//DefaultMaterial* planeMaterial = New<DefaultMaterial>(Color::White);
	//Model* planeModel = New<Model>();
	//planeModel->AddMeshAndMaterial(planeMesh, planeMaterial);
	//auto planeEntity = New<RenderEntity>(planeModel);
	// init light
	auto lightEntity = New<LightEntity>();
	lightEntity->GetComponent<LightComponent>()->CreateDirectionalLight();
	lightEntity->GetComponent<TransformComponent>()->SetPosition(Vector3(5.0f, 3.0f, 5.0f));
	lightEntity->GetComponent<TransformComponent>()->LookAt(Vector3::Zero);
}


bool Editor::Init()
{
	Globals::Width = 1280;
	Globals::Height = 720;
	if (!Application::Init())
		return false;
	InitCamera();
	InitSkyBox();
	InitTestScene3();

	m_EditorUI = New<EditorUI>();
	ImGuiHelper::Instance()->AddUI(m_EditorUI);

	return true;
}


int32 Editor::Main()
{



	return Application::Main();
}

