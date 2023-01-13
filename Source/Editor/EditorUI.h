#pragma once


#include "Engine/Gui/UIBase.h"

class EditorUI : public DawnEngine::UIBase
{
public:

	void Draw() override;

private:

	void DrawHierachy();
	void DrawInspect();
};