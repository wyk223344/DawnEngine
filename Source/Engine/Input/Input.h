#pragma once


#include "Engine/Core/Include.h"
#include "Engine/Engine/EngineService.h"
#include "Enums.h"

namespace DawnEngine
{
	using namespace Math;

	class Keyboard;
	class Mouse;

	class Input
	{
	public:

		static Mouse* Mouse;

		static Keyboard* Keyboard;

	public:

		typedef Delegate<KeyboardKeys> KeyboardDelegate;
		typedef Delegate<const Vector2&> MouseDelegate;
		typedef Delegate<const Vector2&, MouseButton> MouseButtonDelegate;
		typedef Delegate<const Vector2&, float> MouseWheelDelegate;
		typedef Delegate<const Vector2&, int32> TouchDelegate;

		static KeyboardDelegate KeyDown;

		static KeyboardDelegate KeyUp;

		static MouseButtonDelegate MouseDown;

		static MouseButtonDelegate MouseUp;

		static MouseWheelDelegate MouseWheel;

		static MouseDelegate MouseMove;

	public:

		static Vector2 GetMousePosition();
	};


	class InputService : public EngineService
	{
	public:

		InputService();

		void Update() override;
	};
}