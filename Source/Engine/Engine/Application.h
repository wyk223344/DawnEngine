#pragma once

#include "Engine/Core/Types/BaseTypes.h"

namespace DawnEngine
{
    class Application
	{
	public:

		virtual bool Init();

	    virtual int32 Main();
    };
}