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

		StateType GetState() { return m_ResourceState; }

	private:

		StateType m_ResourceState;
	};
}