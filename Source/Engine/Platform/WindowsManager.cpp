
#include "Engine/Platform/Define.h"
#include "Engine/Platform/WindowsManager.h"
#include "Engine/Engine/EngineService.h"

using namespace DawnEngine;

std::vector<Window*> WindowsManager::Windows;


Window* WindowsManager::GetByNativePtr(void* handle)
{
	Window* result = nullptr;
	for (int32 i = 0; i < Windows.size(); i++)
	{
		if (Windows[i]->GetNativePtr() == handle)
		{
			result = Windows[i];
			break;
		}
	}
	return result;
}

void WindowsManager::Register(Window* win)
{
	Windows.push_back(win);
}

void WindowsManager::Unregister(Window* win)
{
	
}


WindowsManagerService::WindowsManagerService() : EngineService(TEXT("Windows Manager"), -30)
{
}

void WindowsManagerService::Update()
{
}

void WindowsManagerService::Dispose()
{
}