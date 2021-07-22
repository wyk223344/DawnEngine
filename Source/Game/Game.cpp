
#include "Game.h"
#include "Engine/Core/Include.h"
#include "Engine/Engine/Engine.h"
#include "Engine/Engine/Scene.h"
#include "Engine/Engine/Entities/CameraEntity.h"
#include "Engine/Engine/Entities/RenderEntity.h"
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

using namespace DawnEngine;

namespace GameImpl
{

}


void InitCamera()
{
	// init camera
	auto cameraEntity = New<CameraEntity>(45.0f, (float)Globals::Width / Globals::Height);
	Vector3 startPosition(0.0f, 0.0f, Globals::Distance2Center);
	cameraEntity->GetComponent<TransformComponent>()->SetPosition(startPosition);
	cameraEntity->GetComponent<TransformComponent>()->LookAt(Vector3::Zero);
}

void InitSkyBox()
{
	TextureData* textureData = Resource::LoadCubeMap("Assets/Textures/Skybox/");
	SkyboxMaterial* material = New<SkyboxMaterial>();
	material->CubeMap = textureData;
	Engine::MainScene->SetSkyboxMaterial(material);
}

void InitTestScene1()
{
	// init cube
	MeshData* cubeMesh = GeometryGenerator::CreateBox(1.0f, 1.0f, 1.0f);
	DefaultMaterial* material = New<DefaultMaterial>(Color::Black);
	Model* model = New<Model>();
	model->AddMeshAndMaterial(cubeMesh, material);
	auto cubeEntity = New<RenderEntity>(model);
}


void InitTestScene2()
{
	// init model
	Model* model = Resource::LoadModel("Assets/Models/dragon/dragon.obj");
	auto modelEntity = New<RenderEntity>(model);
}


bool Game::Init()
{
	InitCamera();
	InitSkyBox();
	InitTestScene1();
	// InitTestScene2();

	return true;
}