#pragma once

#include "Engine/Platform/CreateWindowSettings.h"

namespace DawnEngine
{

	class WindowBase
	{
	protected:
		explicit WindowBase(const CreateWindowSettings& settings);
		virtual ~WindowBase();

	public:
		/// <summary>
		/// ªÒ»°œ‘ æ¥∞æ‰±˙
		/// </summary>
		/// <returns></returns>
		virtual void* GetNativePtr() const = 0;
	};

}