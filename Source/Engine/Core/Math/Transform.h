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
			: Translation(0.0f)
			, Rotation(0.0f, 0.0f, 0.0f, 1.0f)
			, Scale(1.0f)
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

		void LookAt(const Vector3& target);

		Matrix4x4 Transform::GetWorldMatrix() const;

	public:

		Vector3 GetRight() const
		{
			return Vector3::Transform(Vector3::Right, Rotation);
		}

		Vector3 GetLeft() const
		{
			return Vector3::Transform(Vector3::Left, Rotation);
		}

		Vector3 GetUp() const
		{
			return Vector3::Transform(Vector3::Up, Rotation);
		}

		Vector3 GetDown() const
		{
			return Vector3::Transform(Vector3::Down, Rotation);
		}

		Vector3 GetForward() const
		{
			return Vector3::Transform(Vector3::Forward, Rotation);
		}

		Vector3 GetBackward() const
		{
			return Vector3::Transform(Vector3::Backward, Rotation);
		}
	};
}