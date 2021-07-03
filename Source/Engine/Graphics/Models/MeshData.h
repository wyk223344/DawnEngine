#pragma once

#include "Engine/Core/Include.h"
#include "Vertex.h"
#include <vector>


namespace DawnEngine
{
	class MeshData
	{
	public:

		std::vector<Vertex> Vertices;
		std::vector<uint32> Indices;
	};
}