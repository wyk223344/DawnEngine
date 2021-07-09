#include "InputComponent.h"
#include "TransformComponent.h"
#include "Engine/Engine/Base/EntityBase.h"
#include "Engine/Core/Include.h"
#include "Engine/Input/Input.h"
#include "Engine/Input/Mouse.h"
#include "Engine/Input/Keyboard.h"
#include "Engine/Input/Enums.h"


using namespace DawnEngine;
using namespace DawnEngine::Math;

void InputComponent::Update()
{
	if (Input::Mouse->GetButtonDown(MouseButton::Left))
	{
		m_PrePosition = Input::GetMousePosition();
	}
	else if (Input::Mouse->GetButton(MouseButton::Left))
	{
		Vector2 curPosition = Input::GetMousePosition();
		Vector2 deltaPosition = curPosition - m_PrePosition;
		m_PrePosition = curPosition;

		auto transformComp = GetEntity()->GetComponent<TransformComponent>();

	}
}