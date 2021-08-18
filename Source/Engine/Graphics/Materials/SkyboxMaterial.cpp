
#include "Engine/Core/Include.h"
#include "SkyboxMaterial.h"
#include "CompiledShaders/SkyboxVS.h"
#include "CompiledShaders/SkyboxPS.h"
#include "CompiledShaders/IrradianceCubemapPS.h"
#include "CompiledShaders/PrefilterCubemapPS.h"
#include "Engine/Graphics/GPUDevice.h"
#include "Engine/Graphics/GPUPipelineState.h"
#include "Engine/Graphics/Shaders/GPUShader.h"
#include "Engine/Graphics/GPUConstantBuffer.h"
#include "Engine/Graphics/Textures/GPUTexture.h"
#include "Engine/Graphics/Textures/GPUTextureDescription.h"
#include "Engine/Graphics/Textures/TextureData.h"
#include "Engine/Graphics/Models/Mesh.h"

#include "Engine/Renderer/RenderContext.h"

using namespace DawnEngine;

SkyboxMaterial::SkyboxMaterial()
	: CubeMap(nullptr)
	, m_GPUTexture(nullptr)
{
}


bool SkyboxMaterial::InitGPUResource()
{
	if (m_IsInit)
	{
		return true;
	}
	m_IsInit = true;
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

	// init irradiance texture
	GPUTexture* irradianceTexture = device->CreateTexture();
	cubeMapDesc.Flags = GPUTextureFlags::RenderTarget | GPUTextureFlags::ShaderResource;
	irradianceTexture->Init(cubeMapDesc);
	m_IrradianceTexture = irradianceTexture;

	// init irradiance pso
	GPUPipelineState* irradiancePSO = device->CreatePipelineState();
	auto irradiancePSODesc = GPUPipelineState::Description::Default;
	irradiancePSODesc.VS = shader->CreateShaderProgramVS(g_ShaderSkyboxVS, sizeof(g_ShaderSkyboxVS));
	irradiancePSODesc.PS = shader->CreateShaderProgramPS(g_ShaderIrradianceCubemapPS, sizeof(g_ShaderIrradianceCubemapPS));
	irradiancePSODesc.CullMode = CullMode::TwoSided;
	irradiancePSODesc.DepthFunc = ComparisonFunc::LessEqual;
	irradiancePSO->Init(irradiancePSODesc);
	m_IrradiancePSO = irradiancePSO;
	return true;
}

void SkyboxMaterial::Draw(GPUContext* context)
{
	context->SetState(m_PipelineState);
	// context->BindSR(0, m_GPUTexture->ViewArray());
	context->BindSR(0, m_IrradianceTexture->ViewArray());
}


void SkyboxMaterial::PreIntegrateCubemap(RenderContext* renderContext, Mesh* skyMesh)
{
	GPUDevice* device = GPUDevice::Instance;
	GPUContext* context = device->GetMainContext();

	context->FrameBegin();

	// draw irradiance texture
	Transform tempTransform;
	std::vector<Math::Vector3> lookAtPositions = {
		Math::Vector3::Right,
		Math::Vector3::Left,
		Math::Vector3::Up,
		Math::Vector3::Down,
		Math::Vector3::Forward,
		Math::Vector3::Backward
	};
	Matrix4x4 projMatrix;
	Matrix4x4::Ortho(1.0f, 1.0f, 0.01f, 1000.0f, projMatrix);
	//context->SetState(m_IrradiancePSO);
	//context->BindSR(0, m_GPUTexture->ViewArray());
	int index = 0;
	for each (Math::Vector3 dir in lookAtPositions)
	{
		tempTransform.LookAt(dir);
		// auto viewMatrix = tempTransform.GetWorldMatrix();
		//viewMatrix.Invert();
		//renderContext->GlobalConstant.ViewProjMatrix = viewMatrix * projMatrix;
		// context->UpdateCB(renderContext->GlobalConstantBuffer, &renderContext->GlobalConstant);
		context->SetRenderTarget(m_IrradianceTexture->View(index));

		context->Draw(GPUDevice::Instance->GetColorTexture(Color::White));

		// skyMesh->Draw(context);

		index++;
	}

	context->FrameEnd();
	context->FrameBegin();
}