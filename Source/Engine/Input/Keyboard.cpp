
#include "Keyboard.h"

using namespace DawnEngine;


void Keyboard::OnKeyDown(KeyboardKeys key, Window* target)
{
	Event& e = m_EventQueue.AddOne();
	e.Type = InputEventType::KeyDown;
	e.Target = target;
	e.KeyData.Key = key;
}

void Keyboard::OnKeyUp(KeyboardKeys key, Window* target)
{
	Event& e = m_EventQueue.AddOne();
	e.Type = InputEventType::KeyUp;
	e.Target = target;
	e.KeyData.Key = key;
}

void Keyboard::ResetState()
{
	InputDevice::ResetState();
	m_CurState.Clear();
	m_PreState.Clear();
}

void Keyboard::Update(EventQueue& queue)
{
	Platform::MemoryCopy(&m_PreState, &m_CurState, sizeof(State));

	for (int32 i = 0; i < m_EventQueue.Count(); i++)
	{
		const Event& e = m_EventQueue[i];
		switch (e.Type)
		{
		case InputEventType::KeyDown:
		{
			m_CurState.Keys[static_cast<int32>(e.KeyData.Key)] = true;
			break;
		}
		case InputEventType::KeyUp:
		{
			m_CurState.Keys[static_cast<int32>(e.KeyData.Key)] = false;
			break;
		}
		default:
			break;
		}
	}

	queue.AddRange(m_EventQueue);
	m_EventQueue.Clear();
}