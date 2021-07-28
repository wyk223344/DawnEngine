#include "LightComponent.h"
#include "Engine/Graphics/Lights/DirectionalLight.h"

using namespace DawnEngine;


void LightComponent::CreateDirectionalLight()
{
	m_DirectionalLight = New<DirectionalLight>();
}


DirectionalLight* LightComponent::GetDirectionalLight()
{
	return m_DirectionalLight;
}