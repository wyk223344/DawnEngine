
#include "Engine/Core/Log.h"
#include "Engine/Engine/Engine.h"
#include "Engine/Engine/EngineService.h"
#include "Engine/Engine/Globals.h"
#include "Engine/Platform/Platform.h"
#include "Engine/Platform/CreateWindowSettings.h"
#include "Engine/Engine/Scene.h"
#include "Engine/Renderer/ForwardPass.h"

using namespace DawnEngine;

Window* Engine::MainWindow = nullptr;
Scene* Engine::MainScene = nullptr;
uint64 Engine::FrameCount = 0;

int32 Engine::Main()
{
	if (!Platform::Init())
	{
		LOG_ERROR("Fail to init platform!!!");
		return 0;
	}

	InitMainScene();
	EngineService::OnInit();
	InitMainWindow();
	Platform::BeforeRun();

	ForwardPass::Instance()->Init();

	while (!Globals::IsRequestingExit)
	{
		Platform::Tick();
		EngineService::OnUpdate();
		EngineService::OnLateUpdate();
		EngineService::OnDraw();
		FrameCount++;
	}
	return 0;
}


void Engine::InitMainScene()
{
	Engine::MainScene = Scene::CreateScene();
}

void Engine::InitMainWindow()
{
	LOG_INFO("Start init main window");
	CreateWindowSettings settings;
	settings.Width = Globals::Width;
	settings.Height = Globals::Height;
	Engine::MainWindow = Platform::CreateWindow(settings);
	if (!Engine::MainWindow->InitSwapChain())
	{
		LOG_ERROR("Fail init swap chain");
	}
	LOG_INFO("Finish init main window");
}