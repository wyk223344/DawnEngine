#pragma once

#include <set>

#include "Engine/Core/Object.h"

namespace DawnEngine
{
	class Node : Object
	{
	public:

		Node()
			: m_Parent(nullptr)
		{
		}

		Node(Node* parent)
		{
			SetParent(parent);
		}

		void SetParent(Node* parent)
		{
			if (parent == m_Parent)
			{
				return;
			}
			if (m_Parent != nullptr)
			{
				m_Parent->InternalDelChild(this);
			}
			parent->InternalAddChild(this);
			m_Parent = parent;
		}

		Node* GetParent() const { return m_Parent; }

		void AddChild(Node* child)
		{
			if (child->GetParent() == this)
			{
				return;
			}
			child->SetParent(this);
		}

		void DelChild(Node* child)
		{
			if (child->GetParent() != this)
			{
				return;
			}
			InternalDelChild(child);
			DeleteObject();
		}

	private:

		void InternalAddChild(Node* child)
		{
			m_Children.insert(child);
		}

		void InternalDelChild(Node* child)
		{
			m_Children.erase(child);
		}

	private:

		Node* m_Parent;
		std::set<Node*> m_Children;
	};
}