
#include "Engine/Platform/Base/WindowBase.h"
#include "Engine/Platform/WindowsManager.h"

using namespace DawnEngine;

WindowBase::WindowBase(const CreateWindowSettings& settings)
{
	WindowsManager::Register((Window*)this);
}

WindowBase::~WindowBase()
{
}