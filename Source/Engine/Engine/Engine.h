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
	/// ������
	/// </summary>
	static Window* MainWindow;

private:
	/// <summary>
	/// ��ʼ��������
	/// </summary>
	static void InitMainWindow();
};
