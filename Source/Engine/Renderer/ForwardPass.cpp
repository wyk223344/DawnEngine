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
#include "Engine/Graphics/Textures/GPUTexture.h"
#include "Engine/Graphics/Textures/GPUTextureDescription.h"
#include "Engine/Engine/Entities/CameraEntity.h"
#include "ThirdParty/stb_image/stb_image.h"
#include <assert.h>


using namespace DawnEngine;


namespace ForwardPassImpl
{
	Mesh* BoxMesh = nullptr;
	GPUPipelineState* PipelineState = nullptr;
	GPUShader* Shader = nullptr;
	GPUConstantBuffer* ConstantBuffer = nullptr;
	GPUTexture* Texture = nullptr;
	CameraEntity* Camera = nullptr;
	GlobalConstants ConstanInfo;
}


void ForwardPass::Init()
{
	// mesh
	auto boxMesh = New<Mesh>();
	boxMesh->Init(GeometryGenerator::CreateBox(1, 1, 1));
	// shader
	auto shader = GPUDevice::Instance->CreateShader();
	// pso
	auto pipelineState = GPUDevice::Instance->CreatePipelineState();
	auto psoDesc = GPUPipelineState::Description::Default;
	psoDesc.VS = shader->CreateShaderProgramVS("Shaders\\TempShader.hlsl");
	psoDesc.PS = shader->CreateShaderProgramPS("Shaders\\TempShader.hlsl");
	pipelineState->Init(psoDesc);
	// texture
	auto texture = GPUDevice::Instance->CreateTexture();
	int texWidth, texHeight, texChannels;
	unsigned char* data = stbi_load("Assets/Textures/Crate.png", &texWidth, &texHeight, &texChannels, 0);
	auto texDesc = GPUTextureDescription::New2D(texWidth, texHeight, PixelFormat::R8G8B8A8_Typeless);
	texture->Init(texDesc);
	// GPUDevice::Instance->GetMainContext()->UpdateTexture(texture, 1, 1, data, 0, 0);
	// camera
	auto cameraEntity = New<CameraEntity>(45.0f, (float)Globals::Width / Globals::Height);
	Vector3 startPosition(0.0f, 0.0f, Globals::Distance2Center);
	cameraEntity->GetComponent<TransformComponent>()->SetPosition(startPosition);
	cameraEntity->GetComponent<TransformComponent>()->LookAt(Vector3::Zero);
	// constant buffer
	auto constantBuffer = GPUDevice::Instance->CreateConstantBuffer(sizeof(GlobalConstants));
	
	ForwardPassImpl::BoxMesh = boxMesh;
	ForwardPassImpl::PipelineState = pipelineState;
	ForwardPassImpl::Shader = shader;
	ForwardPassImpl::Camera = cameraEntity;
	ForwardPassImpl::ConstantBuffer = constantBuffer;
	ForwardPassImpl::Texture = texture;
}

void ForwardPass::Render(GPUContext* context)
{
	Window* window = Engine::MainWindow;
	auto swapChain = window->GetSwapChain();

	auto backBuffer = swapChain->GetBackBuffer();

	auto cameraComponent = ForwardPassImpl::Camera->GetComponent<CameraComponent>();
	auto transformComponent = ForwardPassImpl::Camera->GetComponent<TransformComponent>();
	auto cameraPosition = transformComponent->Transform.Translation;
	Matrix4x4 viewMatrix = cameraComponent->GetViewMatrix();
	Matrix4x4 projMatrix = cameraComponent->GetProjectionMatrix();
	Matrix4x4 viewProjMatrix = viewMatrix * projMatrix;
	ForwardPassImpl::ConstanInfo.ViewProjMatrix = viewProjMatrix;

	context->SetViewportAndScissors(Globals::Width, Globals::Height);
	context->Clear(backBuffer, Color::Gray);
	
	context->BindVB(ForwardPassImpl::BoxMesh->GetVertexBuffer());
	context->BindIB(ForwardPassImpl::BoxMesh->GetIndexBuffer());

	context->SetRenderTarget(backBuffer);
	context->SetState(ForwardPassImpl::PipelineState);

	context->UpdateCB(ForwardPassImpl::ConstantBuffer, &ForwardPassImpl::ConstanInfo);
	context->BindCB(0, ForwardPassImpl::ConstantBuffer);

	// context->BindSR(0, ForwardPassImpl::Texture);

	context->DrawIndexedInstanced(ForwardPassImpl::BoxMesh->GetIndicesCount(), 1);
	context->FlushState();
}

void ForwardPass::Dispose()
{
}