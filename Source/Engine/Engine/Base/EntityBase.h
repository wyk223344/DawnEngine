#pragma once

#include <typeinfo>
#include <map>
#include <vector>

#include "Engine/Core/Types/Node.h"

namespace DawnEngine
{
	class ComponentBase;

	class EntityBase : Node<EntityBase>
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

	public: // 生命周期相关

		virtual void Update();

		virtual void LateUpdate();

	private:

		std::map<std::type_info, ComponentBase*> m_Components;

	};
}