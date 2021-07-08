#pragma once

#include "Engine/Core/Include.h"
#include "Enums.h"
#include "InputDevice.h"

namespace DawnEngine
{
	using namespace Math;

	class Mouse : public InputDevice
	{
	public:

		struct State
		{
			Vector2 MousePosition;

			float MouseWheelDelta;

			bool MouseButtons[(int32)MouseButton::MAX];

			void Clear()
			{
				Platform::MemoryClear(this, sizeof(State));
			}
		};

	protected:

		State m_CurState;
		State m_PreState;

	public:

		Mouse()
		{
			m_CurState.Clear();
			m_PreState.Clear();
		}

	public:

		Vector2 GetPosition() const 
		{
			return m_CurState.MousePosition;
		}

		Vector2 GetPositionDelta() const
		{
			return m_CurState.MousePosition - m_PreState.MousePosition;
		}

		float GetScrollDelta() const
		{
			return m_CurState.MouseWheelDelta;
		}

		bool GetButton(MouseButton button) const
		{
			return m_CurState.MouseButtons[static_cast<int32>(button)];
		}

		bool GetButtonDown(MouseButton button) const
		{
			return m_CurState.MouseButtons[static_cast<int32>(button)] && !m_PreState.MouseButtons[static_cast<int32>(button)];
		}

		bool GetButtonUp(MouseButton button) const
		{
			return !m_CurState.MouseButtons[static_cast<int32>(button)] && m_PreState.MouseButtons[static_cast<int32>(button)];
		}

	public:

		void OnMouseDown(const Vector2& position, const MouseButton button, Window* target = nullptr);
	
		void OnMouseUp(const Vector2& position, const MouseButton button, Window* target = nullptr);

		void OnMouseMove(const Vector2& position, Window* target = nullptr);

		void OnMouseWheel(const Vector2& position, float delta, Window* target = nullptr);
	
	public:

		void ResetState() override;
		void Update(EventQueue& queue) override;
	};
}