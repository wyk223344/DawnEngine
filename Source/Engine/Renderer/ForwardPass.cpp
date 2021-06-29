#include "ForwardPass.h"
#include "Engine/Engine/Engine.h"
#include "Engine/Graphics/GPUSwapChain.h"
#include "Engine/Graphics/GPUDevice.h"
#include "Engine/Graphics/GPUContext.h"

using namespace DawnEngine;

void ForwardPass::Render(GPUContext* context)
{
	Window* window = Engine::MainWindow;
	auto swapChain = window->GetSwapChain();

	auto backBuffer = swapChain->GetBackBuffer();

	context->Clear(backBuffer, Color::Red);
	context->SetRenderTarget(backBuffer);
	context->FlushState();
}