#pragma once

#include "Engine/Core/Types/BaseTypes.h"
#include "Engine/Core/Delegate.h"
#include "Engine/Platform/Window.h"

namespace DawnEngine
{
	class Engine
	{
	public:

		// ������
		static int32 Main();

	public:

		// ������
		static Window* MainWindow;

	private:
		
		// ��ʼ��������
		static void InitMainWindow();
	};

}