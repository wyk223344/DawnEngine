
#include "Engine/Core/Log.h"
#include "Engine/Engine/Engine.h"
#include "Engine/Engine/EngineService.h"
#include "Engine/Engine/Globals.h"
#include "Engine/Platform/Platform.h"





int32 Engine::Main(const Char* cmdLine)
{
	// Main message loop:
	
	if (!Platform::Init())
	{
		LOG_ERROR("Fail to init platform!!!");
		return 0;
	}

	EngineService::OnInit();
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