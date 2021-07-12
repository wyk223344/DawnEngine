
#include "CameraComponent.h"
#include "TransformComponent.h"
#include "Engine/Engine/Base/EntityBase.h"


using namespace DawnEngine;
using namespace DawnEngine::Math;


CameraComponent::CameraComponent(EntityBase* entity, float fov, float aspect, float zNear, float zFar)
	: ComponentBase(entity)
	, m_FOV(fov)
	, m_AspectRatio(aspect)
	, m_NearClip(zNear)
	, m_FarClip(zFar)
{
}

Matrix4x4& CameraComponent::GetProjectionMatrix()
{
	Matrix4x4 result;
	Matrix4x4::PerspectiveFov(m_FOV, m_AspectRatio, m_NearClip, m_FarClip, result);
	//Matrix4x4::Ortho(8.0f, 8.0f, m_NearClip, m_FarClip, result);
	return result;
}

Matrix4x4& CameraComponent::GetViewMatrix()
{
	auto transformComponent = GetEntity()->GetComponent<TransformComponent>();
	auto result = transformComponent->Transform.GetWorldMatrix();
	result.Invert();
	 
	return result;
}