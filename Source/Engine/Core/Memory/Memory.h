#pragma once

#include "Engine/Core/Templates.h"
#include "Engine/Core/Memory/Allocator.h"
#include "Engine/Platform/Platform.h"
#include <new>


namespace DawnEngine
{
	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <typeparam name="MemoryAllocator"></typeparam>
	/// <typeparam name="...Args"></typeparam>
	/// <param name="...args"></param>
	/// <returns></returns>
	template<class T, class MemoryAllocator = Allocator, class... Args>
	inline T* New(Args&&...args)
	{
		T* ptr = (T*)MemoryAllocator::Allocate(sizeof(T));
		new(ptr) T(Forward<Args>(args)...);
		return ptr;
	}


	template<class T, class MemoryAllocator = Allocator>
	inline void Delete(T* ptr)
	{
		// Memory::DestructItem(ptr);
		MemoryAllocator::Free(ptr);
	}

}