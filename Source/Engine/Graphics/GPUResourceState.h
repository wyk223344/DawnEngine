#pragma once

#include <vector>

namespace DawnEngine
{
	template<typename StateType, StateType InvalidState>
	class GPUResourceState
	{
	public:

		GPUResourceState()
			: m_ResourceState(InvalidState)
		{
		}

		void Initialize(StateType initialState)
		{
			m_ResourceState = initialState;
		}

		void Initialize(uint32 subresourceCount, StateType initialState)
		{
			m_IsAllSubresourcesSame = true;
			m_ResourceState = initialState;
			if (subresourceCount > 1)
			{
				m_SubresourceStates.resize(subresourceCount, InvalidState);
			}
		}

		bool IsInitializated() const
		{
			return m_ResourceState != InvalidState || m_SubresourceStates.size() > 0;
		}

		void Release()
		{
			m_ResourceState = InvalidState;
			m_SubresourceStates.resize(0);
		}

		bool IsAllSubresourcesSame() const
		{
			return m_IsAllSubresourcesSame;
		}

		int32 GetSubresourcesCount() const
		{
			return m_SubresourceStates.size();
		}

		StateType GetState() { return m_ResourceState; }

		StateType GetSubresourceState(uint32 subresourceIndex) const
		{
			if (m_IsAllSubresourcesSame)
			{
				return m_ResourceState;
			}

			return m_SubresourceStates[subresourceIndex];
		}

		void SetResourceState(StateType state)
		{
			m_ResourceState = state;
			if (!m_IsAllSubresourcesSame)
			{
				m_IsAllSubresourcesSame = true;

				for (int32 i = 0; i < m_SubresourceStates.size(); i++)
				{
					m_SubresourceStates[i] = InvalidState;
				}
			}
		}

		void SetSubresourceState(int32 subresourceIndex, StateType state)
		{
			if (subresourceIndex < 0 || m_SubresourceStates.size() <= 1)
			{
				SetResourceState(state);
			}
			else
			{
				if (m_IsAllSubresourcesSame)
				{
					m_IsAllSubresourcesSame = false;
					for (int32 i = 0; i < m_SubresourceStates.size(); i++)
					{
						m_SubresourceStates[i] = m_ResourceState;
					}
				}
				m_SubresourceStates[subresourceIndex] = state;
			}
		}

	private:

		StateType m_ResourceState;
		std::vector<StateType> m_SubresourceStates;

		bool m_IsAllSubresourcesSame;
	};
}