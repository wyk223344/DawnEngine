#pragma once

#include "Engine/Core/Memory/Memory.h"

namespace DawnEngine
{
	class Object
	{
	public:

		void DeleteSelf()
		{
			Delete(this);
		}
	};
}