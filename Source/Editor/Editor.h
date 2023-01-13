#pragma once



#include "Engine/Engine/Application.h"

class EditorUI;

class Editor : public DawnEngine::Application
{

public:
	bool Init() override;

	int32 Main() override;

private:

	EditorUI* m_EditorUI;

	int m_temp;
};