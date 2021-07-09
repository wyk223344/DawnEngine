#pragma once

#include "Engine/Core/Include.h"
#include "Enums.h"
#include "InputDevice.h"

namespace DawnEngine
{
	using namespace Math;

	class Keyboard : public InputDevice
	{
	public:

		struct State
		{
			bool Keys[(int32)KeyboardKeys::MAX];

			void Clear()
			{
				Platform::MemoryClear(this, sizeof(State));
			}
		};

	protected:

		State m_CurState;
		State m_PreState;

	public:

		Keyboard()
		{
			m_CurState.Clear();
			m_PreState.Clear();
		}

	public:

		bool GetKey(KeyboardKeys key) const
		{
			return m_CurState.Keys[static_cast<int32>(key)];
		}

		bool GetKeyDown(KeyboardKeys key) const
		{
			return m_CurState.Keys[static_cast<int32>(key)] && !m_PreState.Keys[static_cast<int32>(key)];
		}

		bool GetKeyUp(KeyboardKeys key) const
		{
			return !m_CurState.Keys[static_cast<int32>(key)] && m_PreState.Keys[static_cast<int32>(key)];
		}

	public:

		void OnKeyDown(KeyboardKeys key, Window* target = nullptr);

		void OnKeyUp(KeyboardKeys key, Window* target = nullptr);

	public:

		void ResetState() override;
		void Update(EventQueue& queue) override;
	};
}