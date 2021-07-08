
#include "EntityBase.h"
#include "ComponentBase.h"
#include "Engine/Engine/Engine.h"
#include "Engine/Core/Include.h"

using namespace DawnEngine;

EntityBase::EntityBase()
{
	auto rootEntity = Engine::MainScene->GetRootEntity();
	if (rootEntity && rootEntity != this)
	{
		SetParent(rootEntity);
	}
}

EntityBase::EntityBase(EntityBase* parent)
	: Node(parent)
{
}

template<typename T, typename ...Args, typename>
T* EntityBase::AddComponent(Args&&...args)
{
	if (GetComponent<T>() != nullptr)
	{
		return;
	}
	T* component = New<T>(this, Forward<Args>(args)...);
	m_Components[typeid(T)] = component;
	component->Awake();
	return componet;
}

template<typename T, typename>
void EntityBase::DelComponent()
{
	auto iter = m_Components.find(typeid(T));
	if (iter != m_Components.end())
	{
		m_Components.erase(iter);
	}
	iter->second->DeleteSelf();
}

template<typename T, typename>
T* EntityBase::GetComponent()
{
	auto iter = m_Components.find(typeid(T));
	if (iter == m_Components.end())
	{
		return nullptr;
	}
	return iter->second;
}

template<typename T, typename>
T* EntityBase::GetComponentInChildren()
{
	T* result = GetComponent<T>();
	if (result)
	{
		return result;
	}
	for (auto child : GetChildren())
	{
		result = child->GetComponent();
		if (result)
		{
			return result;
		}
	}
	return nullptr;
}

template<typename T, typename>
std::vector<T*> EntityBase::GetComponentsInChildren()
{
	std::vector<T*> result;

	return result;
}

void EntityBase::Update()
{
	for (auto iter = m_Components.begin(); iter != m_Components.end(); iter++)
	{
		if (!iter->second->IsStarted())
		{
			iter->second->Start();
		}
		iter->second->Update();
	}
	for (auto iter = m_Children.begin(); iter != m_Children.end(); iter++)
	{
		(*iter)->Update();
	}
}

void EntityBase::LateUpdate()
{
	for (auto iter = m_Components.begin(); iter != m_Components.end(); iter++)
	{
		iter->second->LateUpdate();
	}
	for (auto iter = m_Children.begin(); iter != m_Children.end(); iter++)
	{
		(*iter)->LateUpdate();
	}
}