
#include "EntityBase.h"
#include "ComponentBase.h"
#include "Engine/Engine/Engine.h"
#include "Engine/Core/Templates.h"

using namespace DawnEngine;

EntityBase::EntityBase()
{
	//SetParent(Engine::MainScene->GetRootEntity());
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
	auto component = T::New(this, Forward<Args>(args)...);
	m_Components[typeid(T)] = component;
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