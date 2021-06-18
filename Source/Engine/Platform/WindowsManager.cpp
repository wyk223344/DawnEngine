
#include "Engine/Platform/Define.h"
#include "Engine/Platform/WindowsManager.h"
#include "Engine/Engine/EngineService.h"

using namespace DawnEngine;

class WindowsManagerService : public EngineService
{
public:
	WindowsManagerService() : EngineService(TEXT("Windows Manager"), -30)
	{
	}

	void Update() override;
	void Dispose() override;
};


std::vector<Window*> WindowsManager::Windows;
WindowsManagerService WindowsManagerServiceInstance;

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

void WindowsManagerService::Update()
{
}

void WindowsManagerService::Dispose()
{
}