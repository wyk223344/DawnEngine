
#if PLATFORM_WINDOWS

#include "WindowsInput.h"
#include "Engine/Core/Include.h"
#include "Engine/Input/Enums.h"
#include "Engine/Input/Input.h"
#include "Engine/Input/Mouse.h"
#include "Engine/Input/Keyboard.h"
#include "Engine/Platform/Window.h"

using namespace DawnEngine;

#pragma region WindowsMouse

class WindowsMouse : public Mouse
{
public:
	void WndProc(Window* window, UINT msg, WPARAM wParam, LPARAM lParam);
};

void WindowsMouse::WndProc(Window* window, UINT msg, WPARAM wParam, LPARAM lParam)
{
	POINT p;
	p.x = static_cast<LONG>(WINDOWS_GET_X_LPARAM(lParam));
	p.y = static_cast<LONG>(WINDOWS_GET_Y_LPARAM(lParam));
	ClientToScreen((HWND)(window->GetNativePtr()), &p);
	const auto mousePos = Vector2(static_cast<float>(p.x), static_cast<float>(p.y));

	switch (msg)
	{
	case WM_MOUSEMOVE:
	{
		OnMouseMove(mousePos, window);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		OnMouseDown(mousePos, MouseButton::Left, window);
		break;
	}
	case WM_RBUTTONDOWN:
	{
		OnMouseDown(mousePos, MouseButton::Right, window);
		break;
	}
	case WM_MBUTTONDOWN:
	{
		OnMouseDown(mousePos, MouseButton::Middle, window);
		break;
	}
	case WM_LBUTTONUP:
	{
		OnMouseUp(mousePos, MouseButton::Left, window);
		break;
	}
	case WM_RBUTTONUP:
	{
		OnMouseUp(mousePos, MouseButton::Right, window);
		break;
	}
	case WM_MBUTTONUP:
	{
		OnMouseUp(mousePos, MouseButton::Middle, window);
		break;
	}
	case WM_MOUSEWHEEL:
	{
		const short delta = GET_WHEEL_DELTA_WPARAM(wParam);
		if (delta != 0)
		{
			const float deltaNormalized = static_cast<float>(delta) / WHEEL_DELTA;
			// Use cached mouse position, the input pos is sometimes wrong in Win32
			OnMouseWheel(m_CurState.MousePosition, deltaNormalized, window);
		}
		break;
	}
	}
}

#pragma endregion

#pragma region WindowsKeyboard

class WindowsKeyboard : public Keyboard
{
public:
	void WndProc(Window* window, UINT msg, WPARAM wParam, LPARAM lParam);
};

void WindowsKeyboard::WndProc(Window* window, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	{
		OnKeyDown(static_cast<KeyboardKeys>(wParam), window);
		break;
	}
	case WM_KEYUP:
	case WM_SYSKEYUP:
	{
		OnKeyUp(static_cast<KeyboardKeys>(wParam), window);
		break;
	}
	}
}

#pragma endregion

#pragma region WindowsInput

namespace WindowsInputImpl
{
	WindowsMouse Mouse;
	WindowsKeyboard Keyboard;
}

void WindowsInput::Init()
{
	Input::Mouse = &WindowsInputImpl::Mouse;
	Input::Keyboard = &WindowsInputImpl::Keyboard;
}

void WindowsInput::WndProc(Window* window, UINT msg, WPARAM wParam, LPARAM lParam)
{
	WindowsInputImpl::Mouse.WndProc(window, msg, wParam, lParam);
	WindowsInputImpl::Keyboard.WndProc(window, msg, wParam, lParam);
}

#pragma endregion

#endif