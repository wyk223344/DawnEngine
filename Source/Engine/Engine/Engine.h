#pragma once

#include "Engine/Core/Types/BaseTypes.h"
#include "Engine/Core/Delegate.h"
#include "Engine/Platform/Window.h"



namespace DawnEngine
{
	class Scene;

	class Engine
	{
	public:

		static bool Init();

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

		// ��ʼ��������
		static void InitMainScene();
	};

}