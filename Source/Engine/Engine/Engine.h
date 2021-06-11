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
	/// <param name="cmdLine"></param>
	/// <returns></returns>
	static int32 Main(const Char* cmdLine);

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
