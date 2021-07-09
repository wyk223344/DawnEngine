#pragma once

#include "Engine/Core/Types/BaseTypes.h"
#include "Engine/Core/Memory/Memory.h"
#include <vector>

namespace DawnEngine
{
	// 暂时只是封一下std::vector

	template<typename T>
	class Array
	{
	public:

		void Add(const T& value)
		{
			m_Data.push_back(value);
		}

		void AddRange(Array<T>& array)
		{
			for (int i = 0; i < array.Count(); i++)
			{
				m_Data.push_back(array[i]);
			}
		}

		void Clear()
		{
			m_Data.clear();
		}

		bool Contains(const T& value)
		{
			for (int i = 0; i < Count(); i++)
			{
				if (m_Data[i] == value)
				{
					return true;
				}
			}
			return false;
		}

		int32 Count() const
		{
			return m_Data.size();
		}

		T& AddOne()
		{
			m_Data.push_back(new T());
			return m_Data[Count() - 1];
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