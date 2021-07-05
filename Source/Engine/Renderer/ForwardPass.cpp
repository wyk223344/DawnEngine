#include "ForwardPass.h"
#include "Engine/Engine/Engine.h"
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


using namespace DawnEngine;


namespace ForwardPassImpl
{
	Mesh* BoxMesh = nullptr;
	GPUPipelineState* PipelineState = nullptr;
	GPUShader* Shader = nullptr;
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
	ForwardPassImpl::BoxMesh = boxMesh;
	ForwardPassImpl::PipelineState = pipelineState;
	ForwardPassImpl::Shader = shader;
}

void ForwardPass::Render(GPUContext* context)
{
	Window* window = Engine::MainWindow;
	auto swapChain = window->GetSwapChain();

	auto backBuffer = swapChain->GetBackBuffer();

	//context->SetState(ForwardPassImpl::PipelineState);
	context->SetViewportAndScissors(800.0f, 600.0f);
	context->Clear(backBuffer, Color::Gray);
	context->BindVB(ForwardPassImpl::BoxMesh->GetVertexBuffer());
	context->BindIB(ForwardPassImpl::BoxMesh->GetIndexBuffer());
	context->SetRenderTarget(backBuffer);
	context->SetState(ForwardPassImpl::PipelineState);
	context->DrawIndexedInstanced(36, 1);
	context->FlushState();
}

void ForwardPass::Dispose()
{
}