
#include "EntityBase.h"
#include "ComponentBase.h"
#include "Engine/Engine/Engine.h"
#include "Engine/Engine/Scene.h"
#include "Engine/Core/Include.h"


using namespace DawnEngine;

EntityBase::EntityBase()
{
	if (Engine::MainScene == nullptr)
	{
		return;
	}
	auto rootEntity = Engine::MainScene->GetRootEntity();
	if (rootEntity != nullptr && rootEntity != this)
	{
		SetParent(rootEntity);
	}
}

EntityBase::EntityBase(EntityBase* parent)
	: Node(parent)
{
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
