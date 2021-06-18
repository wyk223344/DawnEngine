#pragma once


namespace DawnEngine
{
	struct Color
	{
	public:
		union
		{
			struct
			{
				float R;
				float G;
				float B;
				float A;
			};
			float Raw[4];
		};
	public:

        Color(float r, float g, float b, float a = 1)
            : R(r)
            , G(g)
            , B(b)
            , A(a)
        {
        }

        Color(const Color& rgb, float a)
            : R(rgb.R)
            , G(rgb.G)
            , B(rgb.B)
            , A(a)
        {
        }

	public:
        // Initializes from values in range [0;255].
        static Color FromBytes(byte r, byte g, byte b, byte a = 255)
        {
            return Color((float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f, (float)a / 255.0f);
        }

        // Initializes from packed RGB value of the color and separate alpha channel value.
        static Color FromRGB(uint32 rgb, float a = 1.0f)
        {
            return Color(static_cast<float>(rgb >> 16 & 0xff) / 255.0f, static_cast<float>(rgb >> 8 & 0xff) / 255.0f, static_cast<float>(rgb & 0xff) / 255.0f, a);
        }
	};
}