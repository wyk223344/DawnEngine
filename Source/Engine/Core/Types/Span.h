#pragma once

#include "BaseTypes.h"

#include <assert.h>

namespace DawnEngine
{
	template<typename T>
	class Span
	{
	protected:
		
		T* m_Data;
		int32 m_Length;

	public:

		Span()
			: m_Data(nullptr)
			, m_Length(0)
		{
		}

		Span(const T* data, int32 length)
			: m_Data(data)
			, m_Length(length)
		{
		}

	public:

		bool IsValid() const { return m_Data != nullptr; }

		bool IsInvalid() const { return m_Data == nullptr; }

		int32 Lenght() const { return m_Length; }

		T* Get() { return m_Data; }

		const T* Get() const { return m_Data; }

	public:

		T& operator[](int32 index)
		{
			assert(index >= 0 && index < m_Length);
			return m_Data[index];
		}

		const T& operator[](int32 index) const
		{
			assert(index >= 0 && index < m_Length);
			return m_Data[index];
		}

	};

	template<typename T>
	inline Span<T> ToSpan(const T* ptr, int32 length)
	{
		return Span<T>(ptr, length);
	}
}