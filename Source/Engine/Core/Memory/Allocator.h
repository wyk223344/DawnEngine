#pragma once

#include "Engine/Core/Types/BaseTypes.h"
#include "Engine/Platform/Platform.h"

class Allocator
{
public:
	static void* Allocate(uint64 size, uint64 alignment = 16)
	{
		return Platform::Allocate(size, alignment);
	}

	static void Free(void* ptr)
	{
		Platform::Free(ptr);
	}
};