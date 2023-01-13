#pragma once

#include "Window.h"
#include "Engine/Engine/EngineService.h"
#include <vector>

namespace DawnEngine
{
	class WindowsManager
	{
	public:
		static std::vector<Window*> Windows;

	public:

		static Window* GetByNativePtr(void* handle);

	public:
		// Used by WindowBase
		static void Register(Window* win);
		static void Unregister(Window* win);
	};

	class WindowsManagerService : public EngineService
	{
	public:
		WindowsManagerService();

		void Update() override;
		void Dispose() override;
	};
}