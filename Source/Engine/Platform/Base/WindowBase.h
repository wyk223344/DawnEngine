#pragma once

#include "Engine/Platform/CreateWindowSettings.h"

class WindowBase
{
protected:
	explicit WindowBase(const CreateWindowSettings& settings);
	virtual ~WindowBase();

public:

	virtual void* GetNativePtr() const = 0;
};