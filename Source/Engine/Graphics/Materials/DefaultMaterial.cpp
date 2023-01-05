#include "DefaultMaterial.h"
#include "DefaultVS.h"
#include "DefaultPS.h"
#include "Engine/Graphics/GPUDevice.h"
#include "Engine/Graphics/GPUPipelineState.h"
#include "Engine/Graphics/Shaders/GPUShader.h"
#include "Engine/Graphics/GPUConstantBuffer.h"

using namespace DawnEngine;


DefaultMaterial::DefaultMaterial(Color color)
{
	m_ConstantInfo.Color = color;
}

bool DefaultMaterial::InitGPUResource()
{
	GPUDevice* device = GPUDevice::Instance;
	GPUContext* context = device->GetMainContext();
	// init shader
	GPUShader* shader = device->CreateShader();
	m_Shader = shader;
	// init constant buffer
	GPUConstantBuffer* constantBuffer = device->CreateConstantBuffer(sizeof(m_ConstantInfo));
	context->UpdateCB(constantBuffer, &m_ConstantInfo);
	m_ConstantBuffer = constantBuffer;
	// init texutres
	
	// init pso
	GPUPipelineState* pipelineState = device->CreatePipelineState();
	auto psoDesc = GPUPipelineState::Description::Default;
	psoDesc.VS = shader->CreateShaderProgramVS(g_ShaderDefaultVS, sizeof(g_ShaderDefaultVS));
	psoDesc.PS = shader->CreateShaderProgramPS(g_ShaderDefaultPS, sizeof(g_ShaderDefaultPS));
	pipelineState->Init(psoDesc);
	m_PipelineState = pipelineState;
	return true;
}

void DefaultMaterial::Draw(GPUContext* context)
{
	context->SetState(m_PipelineState);
	context->BindCB((int32)GPUConstantBufferSlot::Material, m_ConstantBuffer);
}