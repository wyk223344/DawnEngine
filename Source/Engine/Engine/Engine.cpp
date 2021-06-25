
#include "Engine/Core/Log.h"
#include "Engine/Engine/Engine.h"
#include "Engine/Engine/EngineService.h"
#include "Engine/Engine/Globals.h"
#include "Engine/Platform/Platform.h"
#include "Engine/Platform/CreateWindowSettings.h"

using namespace DawnEngine;

Window* Engine::MainWindow = nullptr;


int32 Engine::Main()
{
	if (!Platform::Init())
	{
		LOG_ERROR("Fail to init platform!!!");
		return 0;
	}

	EngineService::OnInit();
	InitMainWindow();
	Platform::BeforeRun();

	while (!Globals::IsRequestingExit)
	{
		Platform::Tick();
		EngineService::OnUpdate();
		EngineService::OnLateUpdate();
		EngineService::OnDraw();
	}
	return 0;
}


void Engine::InitMainWindow()
{
	LOG_INFO("Start init main window");
	CreateWindowSettings settings;
	settings.Width = 800;
	settings.Height = 600;
	Engine::MainWindow = Platform::CreateWindow(settings);
	if (!Engine::MainWindow->InitSwapChain())
	{
		LOG_ERROR("Fail init swap chain");
	}
	LOG_INFO("Finish init main window");
}