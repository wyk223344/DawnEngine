#pragma once

#include <set>

#include "Engine/Core/Object.h"

namespace DawnEngine
{
	template<typename T>
	class Node : Object
	{
	public:

		Node()
			: m_Parent(nullptr)
		{
		}

		Node(T* parent)
		{
			SetParent(parent);
		}

		void SetParent(T* parent)
		{
			if (parent == m_Parent)
			{
				return;
			}
			if (m_Parent != nullptr)
			{
				m_Parent->InternalDelChild(static_cast<T*>(this));
			}
			parent->InternalAddChild(static_cast<T*>(this));
			m_Parent = parent;
		}

		T* GetParent() const { return m_Parent; }

		std::set<T*>& GetChildren() const { return m_Children; }

		void AddChild(T* child)
		{
			if (child->GetParent() == this)
			{
				return;
			}
			child->SetParent(this);
		}

		void DelChild(T* child)
		{
			if (child->GetParent() != this)
			{
				return;
			}
			InternalDelChild(child);
		}

	protected:

		void InternalAddChild(T* child)
		{
			m_Children.insert(child);
		}

		void InternalDelChild(T* child)
		{
			m_Children.erase(child);
		}

	protected:

		T* m_Parent;
		std::set<T*> m_Children;
	};
}