#pragma once


#include "Vector3.h"
#include "Quaternion.h"


namespace DawnEngine::Math
{
	struct Matrix4x4;

	struct Transform
	{
	public:

		Vector3 Translation;
		Quaternion Rotation;
		Vector3 Scale;

	public:

		static Transform Identity;

	public:

		Transform()
		{
		}

		Transform(const Vector3& position)
			: Translation(position)
			, Rotation(0.0f, 0.0f, 0.0f, 1.0f)
			, Scale(1.0f)
		{
		}

		Transform(const Vector3& position, const Quaternion& rotation)
			: Translation(position)
			, Rotation(rotation)
			, Scale(1.0f)
		{
		}

		Transform(const Vector3& position, const Quaternion& rotation, const Vector3& scale)
			: Translation(position)
			, Rotation(rotation)
			, Scale(scale)
		{
		}

	public:

		Matrix4x4 Transform::GetWorldMatrix() const;

	};
}