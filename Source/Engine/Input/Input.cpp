
#include "Input.h"
#include "InputDevice.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Engine/Engine/EngineService.h"

using namespace DawnEngine;
using namespace DawnEngine::Math;

#pragma region Input成员初始化

Mouse* Input::Mouse = nullptr;
Keyboard* Input::Keyboard = nullptr;
Input::KeyboardDelegate Input::KeyDown;
Input::KeyboardDelegate Input::KeyUp;
Input::MouseButtonDelegate Input::MouseDown;
Input::MouseButtonDelegate Input::MouseUp;
Input::MouseWheelDelegate Input::MouseWheel;
Input::MouseDelegate Input::MouseMove;

#pragma endregion


#pragma region InputServices

namespace InputImpl
{
    InputDevice::EventQueue InputEvents;
}


InputService::InputService() : EngineService(TEXT("Input"), -60)
{
}


void InputService::Update()
{
    InputImpl::InputEvents.Clear();
    if (Input::Mouse)
    {
        Input::Mouse->Update(InputImpl::InputEvents);
    }
    if (Input::Keyboard)
    {
        Input::Keyboard->Update(InputImpl::InputEvents);
    }
    for (int32 i = 0; i < InputImpl::InputEvents.Count(); i++)
    {
        const InputDevice::Event& e = InputImpl::InputEvents[i];
        switch (e.Type)
        {
        case InputEventType::KeyDown:
        {
            Input::KeyDown(e.KeyData.Key);
            break;
        }
        case InputEventType::KeyUp:
        {
            Input::KeyUp(e.KeyData.Key);
            break;
        }
        case InputEventType::MouseDown:
        {
            Input::MouseDown(e.MouseData.Position, e.MouseData.Button);
            break;
        }
        case InputEventType::MouseUp:
        {
            Input::MouseUp(e.MouseData.Position, e.MouseData.Button);
            break;
        }
        case InputEventType::MouseWheel:
        {
            Input::MouseWheel(e.MouseWheelData.Position, e.MouseWheelData.WheelDelta);
            break;
        }
        case InputEventType::MouseMove:
        {
            Input::MouseMove(e.MouseData.Position);
            break;
        }
        default:
            break;
        }
    }
}

#pragma endregion

#pragma region Input

Vector2 Input::GetMousePosition()
{
    return Mouse ? Mouse->GetPosition() : Vector2::Zero;
}

#pragma endregion
