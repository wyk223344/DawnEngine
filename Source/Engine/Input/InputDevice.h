#pragma once

#include "Enums.h"

namespace DawnEngine
{
	class InputDevice
	{
	public:

        struct Event
        {
            InputEventType Type;
            Window* Target;

            union
            {

                struct
                {
                    KeyboardKeys Key;
                } KeyData;

                struct
                {
                    MouseButton Button;
                    Vector2 Position;
                } MouseData;

                struct
                {
                    float WheelDelta;
                    Vector2 Position;
                } MouseWheelData;
            };

            Event()
            {
            }

            Event(const Event& e)
            {
                Platform::MemoryCopy(this, &e, sizeof(Event));
            }
        };

        typedef Array<Event> EventQueue;

    public:

        virtual void ResetState()
        {
            m_EventQueue.Clear();
        }

        virtual void Update(EventQueue& queue)
        {
            queue.AddRange(m_EventQueue);
            m_EventQueue.Clear();
        }

    protected:

        EventQueue m_EventQueue;
	};
}