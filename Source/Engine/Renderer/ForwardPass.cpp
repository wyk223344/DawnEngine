#include "ForwardPass.h"
#include "Engine/Engine/Engine.h"
#include "Engine/Engine/Globals.h"
#include "Engine/Graphics/GPUSwapChain.h"
#include "Engine/Graphics/GPUDevice.h"
#include "Engine/Graphics/GPUContext.h"
#include "Engine/Graphics/Models/Mesh.h"
#include "Engine/Graphics/Models/MeshData.h"
#include "Engine/Graphics/Models/GeometryGenerator.h"
#include "Engine/Graphics/Shaders/GPUShader.h"
#include "Engine/Graphics/Shaders/GPUShaderProgram.h"
#include "Engine/Graphics/GPUPipelineState.h"
#include "Engine/Graphics/GPUBuffer.h"
#include "Engine/Graphics/GPUConstantBuffer.h"
#include "Engine/Engine/Entities/CameraEntity.h"
#include <assert.h>

using namespace DawnEngine;


namespace ForwardPassImpl
{
	Mesh* BoxMesh = nullptr;
	GPUPipelineState* PipelineState = nullptr;
	GPUShader* Shader = nullptr;
	GPUConstantBuffer* ConstantBuffer = nullptr;
	CameraEntity* Camera = nullptr;
	GlobalConstants ConstanInfo;
}


void ForwardPass::Init()
{
	auto boxMesh = New<Mesh>();
	boxMesh->Init(GeometryGenerator::CreateBox(1, 1, 1));
	auto shader = GPUDevice::Instance->CreateShader();
	auto pipelineState = GPUDevice::Instance->CreatePipelineState();
	auto psoDesc = GPUPipelineState::Description::Default;
	psoDesc.VS = shader->CreateShaderProgramVS("Shaders\\TempShader.hlsl");
	psoDesc.PS = shader->CreateShaderProgramPS("Shaders\\TempShader.hlsl");
	pipelineState->Init(psoDesc);
	auto cameraEntity = New<CameraEntity>(45.0f, (float)Globals::Width / Globals::Height);
	Vector3 startPosition(0.0f, 0.0f, -3.0f);
	LOG_WARNING("Init CameraPos: X: %f  Y: %f  Z:  %f", startPosition.X, startPosition.Y, startPosition.Z);
	cameraEntity->GetComponent<TransformComponent>()->SetPosition(startPosition);
	cameraEntity->GetComponent<TransformComponent>()->LookAt(Vector3::Zero);
	auto cameraPosition = cameraEntity->GetComponent<TransformComponent>()->Transform.Translation;
	auto constantBuffer = GPUDevice::Instance->CreateConstantBuffer(sizeof(GlobalConstants));
	ForwardPassImpl::BoxMesh = boxMesh;
	ForwardPassImpl::PipelineState = pipelineState;
	ForwardPassImpl::Shader = shader;
	ForwardPassImpl::Camera = cameraEntity;
	ForwardPassImpl::ConstantBuffer = constantBuffer;
}

void ForwardPass::Render(GPUContext* context)
{
	Window* window = Engine::MainWindow;
	auto swapChain = window->GetSwapChain();

	auto backBuffer = swapChain->GetBackBuffer();

	auto cameraComponent = ForwardPassImpl::Camera->GetComponent<CameraComponent>();
	Matrix4x4 viewMatrix = cameraComponent->GetViewMatrix();
	Matrix4x4 projMatrix = cameraComponent->GetProjectionMatrix();
	ForwardPassImpl::ConstanInfo.ViewProjMatrix = viewMatrix * projMatrix;
	// ForwardPassImpl::ConstanInfo.ViewProjMatrix.Transpose();
	auto transformComponent = ForwardPassImpl::Camera->GetComponent<TransformComponent>();
	auto cameraPosition = transformComponent->Transform.Translation;

	/*ForwardPassImpl::ConstanInfo.ViewProjMatrix = Matrix4x4(\
		1.0f, 0.0f, 0.0f, 0.0f,\
		0.0f, 1.0f, 0.0f, 0.0f,\
		0.0f, 0.0f, 1.0f, 0.0f,\
		0.0f, 0.0f, 0.5f, 1.0f\
	);*/

	context->SetViewportAndScissors(Globals::Width, Globals::Height);
	context->Clear(backBuffer, Color::Gray);
	
	context->BindVB(ForwardPassImpl::BoxMesh->GetVertexBuffer());
	context->BindIB(ForwardPassImpl::BoxMesh->GetIndexBuffer());

	context->SetRenderTarget(backBuffer);
	context->SetState(ForwardPassImpl::PipelineState);

	context->UpdateCB(ForwardPassImpl::ConstantBuffer, &ForwardPassImpl::ConstanInfo);
	context->BindCB(0, ForwardPassImpl::ConstantBuffer);

	
	
	context->DrawIndexedInstanced(36, 1);
	context->FlushState();
}

void ForwardPass::Dispose()
{
}