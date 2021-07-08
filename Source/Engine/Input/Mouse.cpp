
#include "Mouse.h"

using namespace DawnEngine;


void Mouse::OnMouseDown(const Vector2& position, const MouseButton button, Window* target = nullptr)
{

}

void Mouse::OnMouseUp(const Vector2& position, const MouseButton button, Window* target = nullptr)
{

}

void Mouse::OnMouseMove(const Vector2& position, Window* target = nullptr)
{

}

void Mouse::OnMouseWheel(const Vector2& position, float delta, Window* target = nullptr)
{

}

void Mouse::ResetState()
{
	InputDevice::ResetState();
	m_CurState.Clear();
	m_PreState.Clear();
}

void Mouse::Update(EventQueue& queue)
{
	Platform::MemoryCopy(&m_PreState, &m_CurState, sizeof(State));

	m_CurState.MouseWheelDelta = 0;

	for (int32 i = 0; i < m_EventQueue.Count(); i++)
	{
		const Event& e = m_EventQueue[i];
		switch (e.Type)
		{
		case InputEventType::MouseDown:
		{
			m_CurState.MouseButtons[static_cast<int32>(e.MouseData.Button)] = true;
			break;
		}
		case InputEventType::MouseUp:
		{
			m_CurState.MouseButtons[static_cast<int32>(e.MouseData.Button)] = false;
			break;
		}
		case InputEventType::MouseMove:
		{
			m_CurState.MousePosition = e.MouseData.Position;
			break;
		}
		case InputEventType::MouseWheel:
		{
			m_CurState.MouseWheelDelta += e.MouseWheelData.WheelDelta;
		}
		default:
			break;
		}
	}

	queue.AddRange(m_EventQueue);
	m_EventQueue.Clear();
}