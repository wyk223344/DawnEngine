#pragma once

#include "Engine/Engine/EngineService.h"

namespace DawnEngine
{
	class Graphics
	{
	public:
		static void Render();
	};


	class GraphicsService : public EngineService
	{
	public:
		GraphicsService();
		bool Init() override;
		void Draw() override;
		void BeforeExit() override;
		void Dispose() override;
	};

}