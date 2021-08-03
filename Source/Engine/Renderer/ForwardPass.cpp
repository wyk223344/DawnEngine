#include "ForwardPass.h"
#include "Engine/Engine/Engine.h"
#include "Engine/Engine/Scene.h"
#include "Engine/Engine/Globals.h"
// #include "Engine/Graphics/GPUSwapChain.h"
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
#include "Engine/Graphics/Materials/MaterialBase.h"
// #include "Engine/Graphics/Textures/GPUTextureDescription.h"
//#include "Engine/Engine/Entities/CameraEntity.h"
//#include "Engine/Engine/Components/MeshRendererComponent.h"
#include "RenderContext.h"
#include "ThirdParty/stb_image/stb_image.h"
#include <assert.h>


using namespace DawnEngine;


namespace ForwardPassImpl
{
	//Mesh* BoxMesh = nullptr;
	//GPUPipelineState* PipelineState = nullptr;
	//GPUShader* Shader = nullptr;
	//GPUTexture* Texture = nullptr;
	//CameraEntity* Camera = nullptr;

	//GlobalConstants ConstanInfo;
	//GPUConstantBuffer* ConstantBuffer = nullptr;

	//GPUTexture* DepthTexture = nullptr;
}


void ForwardPass::Init()
{
	//auto constantBuffer = GPUDevice::Instance->CreateConstantBuffer(sizeof(GlobalConstants));
	//ForwardPassImpl::ConstantBuffer = constantBuffer;

	//GPUTexture* depthTexture = GPUDevice::Instance->CreateTexture();
	//GPUTextureDescription descTexture = GPUTextureDescription::New2D(Globals::Width, Globals::Height, PixelFormat::D24_UNorm_S8_UInt, GPUTextureFlags::DepthStencil);
	//depthTexture->Init(descTexture);
	//ForwardPassImpl::DepthTexture = depthTexture;

	//// mesh
	//auto boxMesh = New<Mesh>();
	//boxMesh->Init(GeometryGenerator::CreateBox(1, 1, 1, 3));
	//// shader
	//auto shader = GPUDevice::Instance->CreateShader();
	//// pso
	//auto pipelineState = GPUDevice::Instance->CreatePipelineState();
	//auto psoDesc = GPUPipelineState::Description::Default;
	//psoDesc.VS = shader->CreateShaderProgramVS(std::string("Shaders\\TempShader.hlsl"));
	//psoDesc.PS = shader->CreateShaderProgramPS(std::string("Shaders\\TempShader.hlsl"));
	//pipelineState->Init(psoDesc);
	//// texture
	//auto texture = GPUDevice::Instance->CreateTexture();
	//int texWidth, texHeight, texChannels;
	//unsigned char* data = stbi_load("Assets/Textures/Crate.png", &texWidth, &texHeight, &texChannels, 0);
	//LOG_WARNING("Load Texture %d %d %d", texWidth, texHeight, texChannels);
	//auto texDesc = GPUTextureDescription::New2D(texWidth, texHeight, PixelFormat::R8G8B8A8_UNorm);
	//texture->Init(texDesc);
	//GPUDevice::Instance->GetMainContext()->UpdateTexture(texture, 1, 1, data, 0, 0);
	//// camera
	//auto cameraEntity = New<CameraEntity>(45.0f, (float)Globals::Width / Globals::Height);
	//Vector3 startPosition(0.0f, 0.0f, Globals::Distance2Center);
	//cameraEntity->GetComponent<TransformComponent>()->SetPosition(startPosition);
	//cameraEntity->GetComponent<TransformComponent>()->LookAt(Vector3::Zero);
	//// constant buffer
	//auto constantBuffer = GPUDevice::Instance->CreateConstantBuffer(sizeof(GlobalConstants));
	//
	//ForwardPassImpl::BoxMesh = boxMesh;
	//ForwardPassImpl::PipelineState = pipelineState;
	//ForwardPassImpl::Shader = shader;
	//ForwardPassImpl::Camera = cameraEntity;
	//ForwardPassImpl::ConstantBuffer = constantBuffer;
	//ForwardPassImpl::Texture = texture;
}

void ForwardPass::Render(RenderContext* renderContext)
{
	GPUContext* context = GPUDevice::Instance->GetMainContext();

	renderContext->GlobalConstant.ViewProjMatrix = renderContext->CameraViewProjMatrix;
	context->UpdateCB(renderContext->GlobalConstantBuffer, &renderContext->GlobalConstant);

	auto renderTarget = renderContext->ForwardPassRT;
	auto depthTexture = renderContext->DepthTexture;

	//auto rootEntity = Engine::MainScene->GetRootEntity();
	//auto cameraComponent = rootEntity->GetComponentInChildren<CameraComponent>();
	//Matrix4x4 viewMatrix = cameraComponent->GetViewMatrix();
	//Matrix4x4 projMatrix = cameraComponent->GetProjectionMatrix();
	//Matrix4x4 viewProjMatrix = viewMatrix * projMatrix;
	//ForwardPassImpl::ConstanInfo.ViewProjMatrix = viewProjMatrix;

	context->SetViewportAndScissors(renderContext->Width, renderContext->Height);
	context->Clear(renderTarget, Color::Gray);
	context->ClearDepth(depthTexture);
	context->SetRenderTarget(renderTarget, depthTexture);

	for (auto drawCall : renderContext->DrawCallList)
	{
		renderContext->MeshConstant.WorldMatrix = drawCall.WorldMatrix;
		context->UpdateCB(renderContext->MeshConstantBuffer, &renderContext->MeshConstant);
		drawCall.Material->Draw(context);
		drawCall.Mesh->Draw(context);
	}
	Engine::MainScene->DrawSkybox(context);
	/*context->UpdateCB(ForwardPassImpl::ConstantBuffer, &ForwardPassImpl::ConstanInfo);
	context->BindCB(0, ForwardPassImpl::ConstantBuffer);

	auto renderComponents = rootEntity->GetComponentsInChildren<MeshRendererComponent>();

	for (int i = 0; i < renderComponents.size(); i++)
	{
		renderComponents[i]->Render(context);
	}

	Engine::MainScene->DrawSkybox(context);*/

	// context->FlushState();

	/*Window* window = Engine::MainWindow;
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
	context->SetRenderTarget(backBuffer);
	
	context->SetState(ForwardPassImpl::PipelineState);

	context->UpdateCB(ForwardPassImpl::ConstantBuffer, &ForwardPassImpl::ConstanInfo);
	context->BindCB(0, ForwardPassImpl::ConstantBuffer);

	context->BindSR(0, ForwardPassImpl::Texture);

	context->BindVB(ForwardPassImpl::BoxMesh->GetVertexBuffer());
	context->BindIB(ForwardPassImpl::BoxMesh->GetIndexBuffer());

	context->DrawIndexedInstanced(ForwardPassImpl::BoxMesh->GetIndicesCount(), 1);
	context->FlushState();*/
}

void ForwardPass::Dispose()
{
}