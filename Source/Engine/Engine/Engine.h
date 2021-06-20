#pragma once

#include "Engine/Core/Types/BaseTypes.h"
#include "Engine/Core/Delegate.h"
#include "Engine/Platform/Window.h"

namespace DawnEngine
{
	class Engine
	{
	public:

		// 主函数
		static int32 Main();

	public:

		// 主窗口
		static Window* MainWindow;

	private:
		
		// 初始化主窗口
		static void InitMainWindow();
	};

}