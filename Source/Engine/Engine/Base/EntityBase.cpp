
#include "EntityBase.h"
#include "ComponentBase.h"
#include "Engine/Engine/Engine.h"
#include "Engine/Engine/Scene.h"
#include "Engine/Core/Include.h"


using namespace DawnEngine;


namespace EntityBaseImpl
{
	std::size_t g_EntiyID = 0;

	std::size_t AllocateEntityID()
	{
		g_EntiyID++;
		return g_EntiyID;
	}
}


EntityBase::EntityBase()
{
	m_ID = EntityBaseImpl::AllocateEntityID();
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
	m_ID = EntityBaseImpl::AllocateEntityID();
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
