#pragma once

#include "Engine/Core/Types/BaseTypes.h"
#include "Engine/Core/Delegate.h"
#include "Engine/Platform/Window.h"
#include "Engine/Engine/Scene.h"


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

		// ������
		static Scene* MainScene;

		// ����Ϸ��ʼ��ĵڼ�֡
		static uint64 FrameCount;

	private:
		
		// ��ʼ��������
		static void InitMainWindow();
	};

}