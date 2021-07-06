#pragma once


#include "Engine/Core/Memory/Allocator.h"


namespace DawnEngine
{
	template<typename ReturnType, typename... Params>
	class Function<ReturnType(Params ...)>
	{
	};
}