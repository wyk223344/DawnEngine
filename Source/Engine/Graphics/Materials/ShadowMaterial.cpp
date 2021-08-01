#include "ShadowMaterial.h"
#include "Engine/Graphics/GPUDevice.h"
#include "Engine/Graphics/GPUContext.h"
#include "Engine/Graphics/GPUPipelineState.h"
#include "Engine/Graphics/Shaders/GPUShader.h"
#include "CompiledShaders/ShadowCasterVS.h"
#include "CompiledShaders/ShadowCasterPS.h"

using namespace DawnEngine;


bool ShadowMaterial::InitGPUResource()
{
	GPUDevice* device = GPUDevice::Instance;
	GPUContext* context = device->GetMainContext();
	// init shader
	GPUShader* shader = device->CreateShader();
	m_Shader = shader;
	// init pso
	GPUPipelineState* pipelineState = device->CreatePipelineState();
	auto psoDesc = GPUPipelineState::Description::Default;
	psoDesc.VS = shader->CreateShaderProgramVS(g_ShaderShadowCasterVS, sizeof(g_ShaderShadowCasterVS));
	psoDesc.PS = shader->CreateShaderProgramPS(g_ShaderShadowCasterPS, sizeof(g_ShaderShadowCasterPS));
	pipelineState->Init(psoDesc);
	m_PipelineState = pipelineState;
}

void ShadowMaterial::Draw(GPUContext* context)
{
	context->SetState(m_PipelineState);
}