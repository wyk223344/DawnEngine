
#include "ThirdParty/imgui/imgui.h"
#include "ImGuiHelper.h"

#include "Engine/Graphics/Textures/GPUTextureDescription.h"
#include "Engine/Graphics/Textures/GPUTexture.h"
#include "Engine/Graphics/GPUDevice.h"
#include "Engine/Graphics/GPUContext.h"


using namespace DawnEngine;


ImGuiHelper::ImGuiHelper()
	: m_RenderMaterial(nullptr)
	, m_FontTexture(nullptr)
{
}


bool ImGuiHelper::Init()
{
	GPUDevice* device = GPUDevice::Instance;
	GPUContext* context = device->GetMainContext();

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsDark();

	unsigned char* pixels;
	int width, height;
	io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);
	size_t size = (size_t)(width * height * 4);
	LOG_ERROR("[ImGuiHelper] init %d %d %d", pixels, width, height);
	auto texDesc = GPUTextureDescription::New2D(width, height, PixelFormat::R8G8B8A8_UNorm);
	GPUTexture* fontTexture = device->CreateTexture();
	fontTexture->Init(texDesc);
	context->UpdateTexture(fontTexture, 0, 0, pixels, 4 * width, 4 * width * height);

	m_FontTexture = fontTexture;

	return true;
}

void ImGuiHelper::Draw(GPUContext* context)
{
	context->Draw(m_FontTexture);
}