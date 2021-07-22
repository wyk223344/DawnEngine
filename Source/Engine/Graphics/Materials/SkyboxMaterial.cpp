
#include "Engine/Core/Include.h"
#include "SkyboxMaterial.h"
#include "CompiledShaders/SkyboxVS.h"
#include "CompiledShaders/SkyboxPS.h"
#include "Engine/Graphics/GPUDevice.h"
#include "Engine/Graphics/GPUPipelineState.h"
#include "Engine/Graphics/Shaders/GPUShader.h"
#include "Engine/Graphics/GPUConstantBuffer.h"
#include "Engine/Graphics/Textures/GPUTexture.h"
#include "Engine/Graphics/Textures/GPUTextureDescription.h"
#include "Engine/Graphics/Textures/TextureData.h"

using namespace DawnEngine;

SkyboxMaterial::SkyboxMaterial()
	: CubeMap(nullptr)
	, m_GPUTexture(nullptr)
{
}


bool SkyboxMaterial::InitGPUResource()
{
	if (CubeMap == nullptr)
	{
		LOG_ERROR("[SkyboxMaterial] Don't have cubemap.");
		return false;
	}
	GPUDevice* device = GPUDevice::Instance;
	GPUContext* context = device->GetMainContext();
	// init shader
	GPUShader* shader = device->CreateShader();
	m_Shader = shader;
	// init constant buffer

	// init texutres
	GPUTexture* texture = device->CreateTexture();
	GPUTextureDescription cubeMapDesc = GPUTextureDescription::NewCube(CubeMap->Width, PixelFormat::R8G8B8A8_UNorm);
	texture->Init(cubeMapDesc);
	for (int i = 0; i < CubeMap->Subresources.size(); i++)
	{
		TextureData* subTexture = CubeMap->Subresources[i];
		context->UpdateTexture(texture, i, 0, subTexture->Data, subTexture->Channel * subTexture->Width, subTexture->Channel * subTexture->Width * subTexture->Height);
	}
	m_GPUTexture = texture;
	// init pso
	GPUPipelineState* pipelineState = device->CreatePipelineState();
	auto psoDesc = GPUPipelineState::Description::Default;
	psoDesc.VS = shader->CreateShaderProgramVS(g_ShaderSkyboxVS, sizeof(g_ShaderSkyboxVS));
	psoDesc.PS = shader->CreateShaderProgramPS(g_ShaderSkyboxPS, sizeof(g_ShaderSkyboxPS));
	psoDesc.CullMode = CullMode::TwoSided;
	psoDesc.DepthFunc = ComparisonFunc::LessEqual;
	pipelineState->Init(psoDesc);
	m_PipelineState = pipelineState;
	return true;
}

void SkyboxMaterial::Draw(GPUContext* context)
{
	context->SetState(m_PipelineState);
	context->BindSR(0, m_GPUTexture);
}