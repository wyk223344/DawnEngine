
#include "Engine/Graphics/GPUDevice.h"
#include "Engine/Renderer/Renderer.h"
#include "Engine/Engine/Engine.h"

using namespace DawnEngine;


GPUDevice* GPUDevice::Instance = nullptr;


bool GPUDevice::Init()
{
	return true;
}

void GPUDevice::DrawBegin()
{
	m_IsRendering = true;
}

void GPUDevice::Draw()
{
	DrawBegin();

	auto context = GetMainContext();
	Window* window = Engine::MainWindow;
	auto swapChain = window->GetSwapChain();

	context->FrameBegin();

	Renderer::Render(context);

	context->FrameEnd();

	swapChain->Present();

	DrawEnd();
}

void GPUDevice::DrawEnd()
{
	m_IsRendering = false;
}

void GPUDevice::Dispose()
{

}
