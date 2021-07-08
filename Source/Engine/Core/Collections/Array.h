#pragma once

#include "Engine/Core/Types/BaseTypes.h"
#include <vector>

namespace DawnEngine
{
	template<typename T>
	class Array
	{
	public:

		void Add(const T& value)
		{
			m_Data.push_back(value);
		}

		void AddRange(const Array<T>& array)
		{

		}

		void Clear()
		{
			m_Data.clear();
		}

		bool Contains(const T& value)
		{

		}

		int32 Count()
		{
			return m_Data.size();
		}

	public:

		T& operator[](int32 index)
		{
			return m_Data[index];
		}

	private:

		int32 m_Count;
		std::vector<T> m_Data;
	};
}