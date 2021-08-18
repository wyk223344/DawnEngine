#include "CopyLinearMaterial.h"
#include "Engine/Graphics/GPUDevice.h"
#include "Engine/Graphics/GPUPipelineState.h"
#include "Engine/Graphics/Shaders/GPUShader.h"
#include "Engine/Graphics/Textures/GPUTexture.h"
#include "CompiledShaders/CopyLinearVS.h"
#include "CompiledShaders/CopyLinearPS.h"

using namespace DawnEngine;


CopyLinearMaterial::CopyLinearMaterial()
	: SrcTexture(nullptr)
{

}

bool CopyLinearMaterial::InitGPUResource()
{
	GPUDevice* device = GPUDevice::Instance;
	GPUContext* context = device->GetMainContext();
	// init shader
	GPUShader* shader = device->CreateShader();
	m_Shader = shader;
	// init pso
	GPUPipelineState* pipelineState = device->CreatePipelineState();
	auto psoDesc = GPUPipelineState::Description::DefaultFullscreenTriangle;
	psoDesc.VS = shader->CreateShaderProgramVS(g_ShaderCopyLinearVS, sizeof(g_ShaderCopyLinearVS));
	psoDesc.PS = shader->CreateShaderProgramPS(g_ShaderCopyLinearPS, sizeof(g_ShaderCopyLinearPS));
	pipelineState->Init(psoDesc);
	m_PipelineState = pipelineState;
	return true;
}

void CopyLinearMaterial::Draw(GPUContext* context)
{
	if (SrcTexture == nullptr)
	{
		LOG_ERROR("[CopyLinearMaterial] SrcTexture is null.");
		return;
	}
	context->SetState(m_PipelineState);
	context->BindSR(0, SrcTexture->View());
}