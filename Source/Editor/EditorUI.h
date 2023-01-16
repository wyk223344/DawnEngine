#pragma once


#include "Engine/Gui/UIBase.h"

class EditorUI : public DawnEngine::UIBase
{
public:

	void Draw() override;

private:

	void DrawHierachyWindow();
	void DrawInspectWindow();
	void DrawGameWindow();

private:

	std::size_t m_SelectID;

};