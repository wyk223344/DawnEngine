#pragma once


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

		StateType GetState() { return m_ResourceState; }

	private:

		StateType m_ResourceState;
	};
}