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

		// 主函数
		static int32 Main();

	public:

		// 主窗口
		static Window* MainWindow;

		// 主场景
		static Scene* MainScene;

		// 从游戏开始后的第几帧
		static uint64 FrameCount;

	private:
		
		// 初始化主窗口
		static void InitMainWindow();

		// 初始化主场景
		static void InitMainScene();
	};

}