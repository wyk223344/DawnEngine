#include "LightComponent.h"
#include "TransformComponent.h"
#include "Engine/Graphics/Lights/DirectionalLight.h"
#include "Engine/Engine/Base/EntityBase.h"

using namespace DawnEngine;


LightComponent::LightComponent(EntityBase* entity)
	: ComponentBase(entity)
{
}


void LightComponent::CreateDirectionalLight()
{
	m_DirectionalLight = New<DirectionalLight>();
	m_DirectionalLight->LightColor = Color::White;
}


DirectionalLight* LightComponent::GetDirectionalLight()
{
	auto transformComp = GetEntity()->GetComponent<TransformComponent>();
	m_DirectionalLight->Transform = transformComp->Transform;
	return m_DirectionalLight;
}