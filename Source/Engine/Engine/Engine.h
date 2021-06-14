#pragma once

#include "Engine/Core/Types/BaseTypes.h"
#include "Engine/Core/Delegate.h"
#include "Engine/Platform/Window.h"

class Engine
{
public:

	/// <summary>
	/// main function
	/// </summary>
	/// <returns></returns>
	static int32 Main();

public:
	/// <summary>
	/// 主窗口
	/// </summary>
	static Window* MainWindow;

private:
	/// <summary>
	/// 初始化主窗口
	/// </summary>
	static void InitMainWindow();
};
