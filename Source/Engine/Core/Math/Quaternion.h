#pragma once


namespace DawnEngine::Math
{
	struct Quaternion
	{
	public:
		union
		{
			struct
			{
				float X;
				float Y;
				float Z;
				float W;
			};
			float Raw[4];
		};

	public:

		static Quaternion Zero;

		static Quaternion One;

		static Quaternion Identity;

	public:

        Quaternion()
			: X(0)
			, Y(0)
			, Z(0)
			, W(0)
        {
        }

        Quaternion(const float xyzw)
            : X(xyzw)
            , Y(xyzw)
            , Z(xyzw)
            , W(xyzw)
        {
        }

        Quaternion(const float x, const float y, const float z, const float w)
            : X(x)
            , Y(y)
            , Z(z)
            , W(w)
        {
        }
	};
}