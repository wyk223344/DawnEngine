
#include "Game.h"
#include "Engine/Core/Include.h"
#include "Engine/Engine/Entities/CameraEntity.h"
#include "Engine/Engine/Entities/RenderEntity.h"
#include "Engine/Engine/Components/TransformComponent.h"
#include "Engine/Engine/Globals.h"
#include "Engine/Graphics/Models/Model.h"
#include "Engine/Graphics/Models/Mesh.h"
#include "Engine/Graphics/Models/GeometryGenerator.h"
#include "Engine/Graphics/Materials/DefaultMaterial.h"
#include "Engine/Graphics/Materials/PBRMaterial.h"
#include "Engine/Resource/Resource.h"

using namespace DawnEngine;

namespace GameImpl
{
	MeshData cubeMesh;
}

void InitTestScene1()
{
	// init camera
	auto cameraEntity = New<CameraEntity>(45.0f, (float)Globals::Width / Globals::Height);
	Vector3 startPosition(0.0f, 0.0f, Globals::Distance2Center);
	cameraEntity->GetComponent<TransformComponent>()->SetPosition(startPosition);
	cameraEntity->GetComponent<TransformComponent>()->LookAt(Vector3::Zero);
	// init cube
	GameImpl::cubeMesh = GeometryGenerator::CreateBox(1.0f, 1.0f, 1.0f);
	DefaultMaterial* material = New<DefaultMaterial>(Color::Black);
	Model* model = New<Model>();
	model->AddMeshAndMaterial(&GameImpl::cubeMesh, material);
	auto cubeEntity = New<RenderEntity>(model);
}


void InitTestScene2()
{
	// init camera
	auto cameraEntity = New<CameraEntity>(45.0f, (float)Globals::Width / Globals::Height);
	Vector3 startPosition(0.0f, 0.0f, Globals::Distance2Center);
	cameraEntity->GetComponent<TransformComponent>()->SetPosition(startPosition);
	cameraEntity->GetComponent<TransformComponent>()->LookAt(Vector3::Zero);
	// init model
	Model* model = Resource::LoadModel("Assets/Models/dragon/dragon.obj");
	auto modelEntity = New<RenderEntity>(model);
}


bool Game::Init()
{

	// InitTestScene1();
	InitTestScene2();

	return true;
}