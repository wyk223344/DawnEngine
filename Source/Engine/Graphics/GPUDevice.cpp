
#include "Engine/Graphics/GPUDevice.h"
#include "Engine/Renderer/Renderer.h"
#include "Engine/Engine/Engine.h"

using namespace DawnEngine;


GPUDevice* GPUDevice::Instance = nullptr;


bool GPUDevice::Init()
{
	return true;
}

void GPUDevice::Draw()
{
	auto context = GetMainContext();
	Window* window = Engine::MainWindow;
	auto swapChain = window->GetSwapChain();

	context->FrameBegin();

	Renderer::Render(context);



	context->FrameEnd();

	swapChain->Present();

}

void GPUDevice::Dispose()
{

}
