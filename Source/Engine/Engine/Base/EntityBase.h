#pragma once

#include <typeinfo>
#include <map>
#include <vector>
#include <functional>
#include "Engine/Core/Include.h"

namespace DawnEngine
{
	class ComponentBase;

	class EntityBase : public Node<EntityBase>
	{
	private:
		template<typename T>
		using enable_if_is_component_t = std::enable_if_t<std::is_base_of_v<ComponentBase, T>>;

	public:

		EntityBase();

		EntityBase(EntityBase* parent);

	public:

		template<typename T, typename ...Args, typename = enable_if_is_component_t<T>>
		T* AddComponent(Args&&...args);

		template<typename T, typename = enable_if_is_component_t<T>>
		void DelComponent();

		template<typename T, typename = enable_if_is_component_t<T>>
		T* GetComponent();

		template<typename T, typename = enable_if_is_component_t<T>>
		T* GetComponentInChildren();

		template<typename T, typename = enable_if_is_component_t<T>>
		std::vector<T*> GetComponentsInChildren();

		void SetName(std::string name) { m_Name = name; }

		const std::string& GetName() { return m_Name; }

		std::size_t GetID() { return m_ID; }

	public: // 生命周期相关

		virtual void Update();

		virtual void LateUpdate();

	private:

		TypeMap<ComponentBase*> m_Components;

		std::string m_Name;

		std::size_t m_ID;
	};

	/*模板的声明和定义要放到一个文件里*/
	
	template<typename T, typename ...Args, typename>
	T* EntityBase::AddComponent(Args&&...args)
	{
		if (GetComponent<T>() != nullptr)
		{
			return nullptr;
		}
		T* component = New<T>(this, Forward<Args>(args)...);
		m_Components[typeid(T)] = component;
		component->Awake();
		return component;
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
		return static_cast<T*>(iter->second);
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
			result = child->GetComponent<T>();
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
		std::function<void(EntityBase*)> getComponents;
		getComponents = [&result, &getComponents](EntityBase* entity)
		{
			auto component = entity->GetComponent<T>();
			if (component)
			{
				result.push_back(component);
			}
			for (auto child : entity->GetChildren())
			{
				getComponents(child);
			}
		};
		getComponents(this);
		return result;
	}
}