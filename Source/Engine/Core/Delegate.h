#pragma once

#include "Engine/Core/Types/BaseTypes.h"
#include "Engine/Core/Memory/Allocator.h"

namespace DawnEngine
{
	template<typename ReturnType, typename... Params>
	class Function<ReturnType(Params ...)>
	{
	};
}