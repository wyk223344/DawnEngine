#pragma once

#include "Engine/Core/Include.h"
#include <vector>

namespace DawnEngine
{
	class TextureData
	{
	public:

		int32 Width;
		int32 Height;
		int32 Channel;
		unsigned char* Data;

		std::vector<TextureData*> Subresources;

	};
}