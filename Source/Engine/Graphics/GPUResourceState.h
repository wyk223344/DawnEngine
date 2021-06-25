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

	private:

		StateType m_ResourceState;
	};
}