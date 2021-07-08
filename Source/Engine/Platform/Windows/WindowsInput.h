#pragma once

#if PLATFORM_WINDOWS

#include "IncludeWindowsHeader.h"
#include "Engine/Platform/Types.h"

namespace DawnEngine
{
	class WindowsInput
	{
	public:

		static void Init();
		static void WndProc(Window* window, UINT msg, WPARAM wParam, LPARAM lParam);

	};
}

#endif