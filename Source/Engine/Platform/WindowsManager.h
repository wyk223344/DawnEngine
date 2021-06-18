#pragma once

#include "Window.h"
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
}