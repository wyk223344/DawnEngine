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


InputComponent::InputComponent(EntityBase* entity)
	: ComponentBase(entity)
	, m_PrePosition(0.0f)
{
}


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

		m_Pitch += deltaPosition.X * 0.01;
		m_Yaw += -deltaPosition.Y * 0.01;

		auto transformComp = GetEntity()->GetComponent<TransformComponent>();
		Vector3 newPosition(
			Math::Sin(m_Pitch) * 10.0f,
			Math::Sin(m_Yaw) * Math::Cos(m_Pitch) * 10.0f,
			Math::Cos(m_Yaw) * Math::Cos(m_Pitch) * 10.0f
		);
		transformComp->SetPosition(newPosition);
		transformComp->LookAt(Vector3::Zero);
	}
}