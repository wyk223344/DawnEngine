
#include "Engine/Platform/Base/WindowBase.h"
#include "Engine/Platform/WindowsManager.h"


WindowBase::WindowBase(const CreateWindowSettings& settings)
{
	WindowsManager::Register((Window*)this);
}

WindowBase::~WindowBase()
{
}