#include "RenderContext.h"
#include "Engine/Core/Include.h"
#include "Engine/Engine/Globals.h"
#include "Engine/Graphics/Enums.h"
#include "Engine/Graphics/Textures/GPUTexture.h"
#include "Engine/Graphics/Textures/GPUTextureDescription.h"
#include "Engine/Graphics/Models/Model.h"
#include "Engine/Graphics/Models/Mesh.h"
#include "Engine/Graphics/Materials/MaterialBase.h"
#include "Engine/Graphics/Lights/DirectionalLight.h"
#include "Engine/Graphics/GPUDevice.h"
#include "Engine/Engine/Engine.h"
#include "Engine/Engine/Scene.h"
#include "Engine/Engine/Base/EntityBase.h"
#include "Engine/Engine/Components/MeshRendererComponent.h"
#include "Engine/Engine/Components/LightComponent.h"
#include "Engine/Engine/Components/TransformComponent.h"
#include "Engine/Engine/Components/CameraComponent.h"


using namespace DawnEngine;


void RenderContext::Init(int32 width, int32 height)
{
	Width = width;
	Height = height;

	auto device = GPUDevice::Instance;

	GlobalConstantBuffer = device->CreateConstantBuffer(sizeof(GlobalConstants));
	MeshConstantBuffer = device->CreateConstantBuffer(sizeof(MeshConstants));

	GPUTexture* depthTexture = device->CreateTexture();
	auto depthDesc = GPUTextureDescription::New2D(width, height, PixelFormat::D24_UNorm_S8_UInt, GPUTextureFlags::DepthStencil);
	depthTexture->Init(depthDesc);
	DepthTexture = depthTexture;

	GPUTexture* forwardPassRT = device->CreateTexture();
	auto rtDesc = GPUTextureDescription::New2D(width, height, PixelFormat::R8G8B8A8_UNorm);
	forwardPassRT->Init(rtDesc);
	ForwardPassRT = forwardPassRT;


}

void RenderContext::BeforeDraw()
{
	DrawCallList.clear();
	DirectionalLightList.clear();

	EntityBase* rootEntity = Engine::MainScene->GetRootEntity();

	auto cameraComponent = rootEntity->GetComponentInChildren<CameraComponent>();
	Matrix4x4 viewMatrix = cameraComponent->GetViewMatrix();
	Matrix4x4 projMatrix = cameraComponent->GetProjectionMatrix();
	Matrix4x4 viewProjMatrix = viewMatrix * projMatrix;
	GlobalConstant.ViewProjMatrix = viewProjMatrix;
	GlobalConstant.CameraPosition = cameraComponent->GetEntity()->GetComponent<TransformComponent>()->Transform.Translation;

	int index = 0;
	for (auto lightComponent : rootEntity->GetComponentsInChildren<LightComponent>())
	{
		auto directionalLight = lightComponent->GetDirectionalLight();
		DirectionalLightList.push_back(directionalLight);
		GlobalConstant.LightDatas[index].Direction = directionalLight->Transform.GetForward();
		GlobalConstant.LightDatas[index].ViewProjMatrix = directionalLight->GetViewMatrix() * directionalLight->GetProjectionMatrix();
		index++;
	}
	GlobalConstant.DirectionalLightCount = index;

	for (auto meshRenderComponent : rootEntity->GetComponentsInChildren<MeshRendererComponent>())
	{
		auto transformComponent = meshRenderComponent->GetEntity()->GetComponent<TransformComponent>();
		Matrix4x4 worldMatrix = transformComponent->Transform.GetWorldMatrix();

		Model* model = meshRenderComponent->GetModel();
		auto meshes = model->GetMeshes();
		auto materials = model->GetMaterials();

		for (int i = 0; i < meshes.size(); i++)
		{
			DrawCall drawCall;
			drawCall.WorldMatrix = worldMatrix;
			drawCall.Mesh = meshes[i];
			drawCall.Material = materials[i];

			DrawCallList.push_back(drawCall);
		}
	}
}