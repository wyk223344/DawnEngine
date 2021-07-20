#include "InputComponent.h"
#include "TransformComponent.h"
#include "Engine/Engine/Base/EntityBase.h"
#include "Engine/Core/Include.h"
#include "Engine/Input/Input.h"
#include "Engine/Input/Mouse.h"
#include "Engine/Input/Keyboard.h"
#include "Engine/Input/Enums.h"
#include "Engine/Engine/Globals.h"

using namespace DawnEngine;
using namespace DawnEngine::Math;


InputComponent::InputComponent(EntityBase* entity)
	: ComponentBase(entity)
	, m_PrePosition(0.0f)
{
}


void InputComponent::Update()
{
	/*if (Input::Mouse->GetButtonDown(MouseButton::Left))
	{
		m_PrePosition = Input::GetMousePosition();
	}
	else if (Input::Mouse->GetButton(MouseButton::Left))
	{
		Vector2 curPosition = Input::GetMousePosition();
		Vector2 deltaPosition = curPosition - m_PrePosition;
		m_PrePosition = curPosition;

		m_Pitch += deltaPosition.X * 0.01;
		m_Yaw += deltaPosition.Y * 0.01;

		auto transformComp = GetEntity()->GetComponent<TransformComponent>();
		Vector3 newPosition(
			Math::Sin(m_Pitch) * Globals::Distance2Center,
			Math::Sin(m_Yaw) * Math::Cos(m_Pitch) * Globals::Distance2Center,
			Math::Cos(m_Yaw) * Math::Cos(m_Pitch) * Globals::Distance2Center
		);
		transformComp->SetPosition(newPosition);
		transformComp->LookAt(Vector3::Zero);
	}*/

	if (Input::Mouse->GetButtonDown(MouseButton::Middle))
	{
		m_PrePosition = Input::GetMousePosition();
	}
	else if (Input::Mouse->GetButton(MouseButton::Middle))
	{
		Vector2 curPosition = Input::GetMousePosition();
		Vector2 deltaPosition = curPosition - m_PrePosition;
		m_PrePosition = curPosition;

		Transform& transform = GetEntity()->GetComponent<TransformComponent>()->Transform;
		transform.Translation += transform.GetRight() * deltaPosition.X * -0.01f;
		transform.Translation += transform.GetUp() * deltaPosition.Y * 0.01f;
	}

	if (Input::Mouse->GetButtonDown(MouseButton::Right))
	{
		m_PrePosition = Input::GetMousePosition();
	}
	else if (Input::Mouse->GetButton(MouseButton::Right))
	{
		Vector2 curPosition = Input::GetMousePosition();
		Vector2 deltaPosition = curPosition - m_PrePosition;
		m_PrePosition = curPosition;

		Transform& transform = GetEntity()->GetComponent<TransformComponent>()->Transform;
		Vector3 lookAtPos = transform.Translation + transform.GetForward();
		lookAtPos += transform.GetRight() * deltaPosition.X * 0.003f;
		lookAtPos += transform.GetUp() * deltaPosition.Y * -0.003f;
		transform.LookAt(lookAtPos);
	}
}