#include "PBRMaterial.h"
#include "Engine/Graphics/GPUDevice.h"
#include "Engine/Graphics/GPUContext.h"
#include "Engine/Graphics/GPUPipelineState.h"
#include "Engine/Graphics/Shaders/GPUShader.h"
#include "Engine/Graphics/GPUConstantBuffer.h"
#include "Engine/Graphics/Textures/GPUTexture.h"
#include "Engine/Graphics/Textures/GPUTextureDescription.h"
#include "Engine/Graphics/Textures/TextureData.h"
#include "PBRVS.h"
#include "PBRPS.h"

using namespace DawnEngine;


PBRMaterial::PBRMaterial(Color color)
	: m_AlbedoTexture(nullptr)
	, m_NormalTexture(nullptr)
	, m_MetallicTexture(nullptr)
	, m_RoughnessTexture(nullptr)
	, m_AOTexture(nullptr)
	, AlbedoTexture(nullptr)
	, NormalTexture(nullptr)
	, MetallicTexture(nullptr)
	, RoughnessTexture(nullptr)
	, AOTexture(nullptr)
	, Metallic(1.0f)
	, Roughness(1.0f)
{
	m_ConstantInfo.Color = color;
}

bool PBRMaterial::InitGPUResource()
{
	GPUDevice* device = GPUDevice::Instance;
	GPUContext* context = device->GetMainContext();
	// init shader
	GPUShader* shader = device->CreateShader();
	m_Shader = shader;
	// init constant buffer
	GPUConstantBuffer* constantBuffer = device->CreateConstantBuffer(sizeof(m_ConstantInfo));
	m_ConstantInfo.Metallic = Metallic;
	m_ConstantInfo.Roughness = Roughness;
	context->UpdateCB(constantBuffer, &m_ConstantInfo);
	m_ConstantBuffer = constantBuffer;
	// init texutres
	// init albedo
	if (AlbedoTexture != nullptr)
	{
		GPUTexture* albedoTexture = device->CreateTexture();
		auto albedoDesc = GPUTextureDescription::New2D(AlbedoTexture->Width, AlbedoTexture->Height, PixelFormat::R8G8B8A8_UNorm);
		albedoTexture->Init(albedoDesc);
		context->UpdateTexture(albedoTexture, 0, 0, AlbedoTexture->Data, AlbedoTexture->Channel * AlbedoTexture->Width, AlbedoTexture->Channel * AlbedoTexture->Width * AlbedoTexture->Height);
		m_AlbedoTexture = albedoTexture;
	}
	// init normal
	if (NormalTexture != nullptr)
	{
		GPUTexture* normalTexture = device->CreateTexture();
		auto normalDesc = GPUTextureDescription::New2D(NormalTexture->Width, NormalTexture->Height, PixelFormat::R8G8B8A8_UNorm);
		normalTexture->Init(normalDesc);
		context->UpdateTexture(normalTexture, 0, 0, NormalTexture->Data, NormalTexture->Channel * NormalTexture->Width, NormalTexture->Channel * NormalTexture->Width * NormalTexture->Height);
		m_NormalTexture = normalTexture;
	}
	// init metallic
	if (MetallicTexture != nullptr)
	{
		GPUTexture* metallicTexture = device->CreateTexture();
		auto metallicDesc = GPUTextureDescription::New2D(MetallicTexture->Width, MetallicTexture->Height, PixelFormat::R8G8B8A8_UNorm);
		metallicTexture->Init(metallicDesc);
		context->UpdateTexture(metallicTexture, 0, 0, MetallicTexture->Data, MetallicTexture->Channel * MetallicTexture->Width, MetallicTexture->Channel * MetallicTexture->Width * MetallicTexture->Height);
		m_MetallicTexture = metallicTexture;
	}
	// init roughness
	if (RoughnessTexture != nullptr)
	{
		GPUTexture* roughnessTexture = device->CreateTexture();
		auto roughnessDesc = GPUTextureDescription::New2D(RoughnessTexture->Width, RoughnessTexture->Height, PixelFormat::R8G8B8A8_UNorm);
		roughnessTexture->Init(roughnessDesc);
		context->UpdateTexture(roughnessTexture, 0, 0, RoughnessTexture->Data, RoughnessTexture->Channel * RoughnessTexture->Width, RoughnessTexture->Channel * RoughnessTexture->Width * RoughnessTexture->Height);
		m_RoughnessTexture = roughnessTexture;
	}
	// init ao
	if (AOTexture != nullptr)
	{
		GPUTexture* aoTexture = device->CreateTexture();
		auto aoDesc = GPUTextureDescription::New2D(AOTexture->Width, AOTexture->Height, PixelFormat::R8G8B8A8_UNorm);
		aoTexture->Init(aoDesc);
		context->UpdateTexture(aoTexture, 0, 0, AOTexture->Data, AOTexture->Channel * AOTexture->Width, AOTexture->Channel * AOTexture->Width * AOTexture->Height);
		m_AOTexture = aoTexture;
	}
	// init pso
	GPUPipelineState* pipelineState = device->CreatePipelineState();
	auto psoDesc = GPUPipelineState::Description::Default;
	psoDesc.VS = shader->CreateShaderProgramVS(g_ShaderPBRVS, sizeof(g_ShaderPBRVS));
	psoDesc.PS = shader->CreateShaderProgramPS(g_ShaderPBRPS, sizeof(g_ShaderPBRPS));
	pipelineState->Init(psoDesc);
	m_PipelineState = pipelineState;
	return true;
}

void PBRMaterial::Draw(GPUContext* context)
{
	context->SetState(m_PipelineState);
	auto whiteTexture = GPUDevice::Instance->GetColorTexture(Color::White);
	context->BindSR(0, m_AlbedoTexture ? m_AlbedoTexture->View() : whiteTexture->View());
	context->BindSR(1, m_NormalTexture ? m_NormalTexture->View() : whiteTexture->View());
	context->BindSR(2, m_MetallicTexture ? m_MetallicTexture->View() : whiteTexture->View());
	context->BindSR(3, m_RoughnessTexture ? m_RoughnessTexture->View() : whiteTexture->View());
	context->BindSR(4, m_AOTexture ? m_AOTexture->View() : whiteTexture->View());
	context->BindCB((int32)GPUConstantBufferSlot::Material, m_ConstantBuffer);
}