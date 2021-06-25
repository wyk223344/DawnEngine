#pragma once


#include "Engine/Core/Types/BaseTypes.h"

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

    public:

        static Color Transparent;
        static Color AliceBlue;
        static Color AntiqueWhite;
        static Color Aqua;
        static Color Aquamarine;
        static Color Azure;
        static Color Beige;
        static Color Bisque;
        static Color Black;
        static Color BlanchedAlmond;
        static Color Blue;
        static Color BlueViolet;
        static Color Brown;
        static Color BurlyWood;
        static Color CadetBlue;
        static Color Chartreuse;
        static Color Chocolate;
        static Color Coral;
        static Color CornflowerBlue;
        static Color Cornsilk;
        static Color Crimson;
        static Color Cyan;
        static Color DarkBlue;
        static Color DarkCyan;
        static Color DarkGoldenrod;
        static Color DarkGray;
        static Color DarkGreen;
        static Color DarkKhaki;
        static Color DarkMagenta;
        static Color DarkOliveGreen;
        static Color DarkOrange;
        static Color DarkOrchid;
        static Color DarkRed;
        static Color DarkSalmon;
        static Color DarkSeaGreen;
        static Color DarkSlateBlue;
        static Color DarkSlateGray;
        static Color DarkTurquoise;
        static Color DarkViolet;
        static Color DeepPink;
        static Color DeepSkyBlue;
        static Color DimGray;
        static Color DodgerBlue;
        static Color Firebrick;
        static Color FloralWhite;
        static Color ForestGreen;
        static Color Fuchsia;
        static Color Gainsboro;
        static Color GhostWhite;
        static Color Gold;
        static Color Goldenrod;
        static Color Gray;
        static Color Green;
        static Color GreenYellow;
        static Color Honeydew;
        static Color HotPink;
        static Color IndianRed;
        static Color Indigo;
        static Color Ivory;
        static Color Khaki;
        static Color Lavender;
        static Color LavenderBlush;
        static Color LawnGreen;
        static Color LemonChiffon;
        static Color LightBlue;
        static Color LightCoral;
        static Color LightCyan;
        static Color LightGoldenrodYellow;
        static Color LightGreen;
        static Color LightGray;
        static Color LightPink;
        static Color LightSalmon;
        static Color LightSeaGreen;
        static Color LightSkyBlue;
        static Color LightSlateGray;
        static Color LightSteelBlue;
        static Color LightYellow;
        static Color Lime;
        static Color LimeGreen;
        static Color Linen;
        static Color Magenta;
        static Color Maroon;
        static Color MediumAquamarine;
        static Color MediumBlue;
        static Color MediumOrchid;
        static Color MediumPurple;
        static Color MediumSeaGreen;
        static Color MediumSlateBlue;
        static Color MediumSpringGreen;
        static Color MediumTurquoise;
        static Color MediumVioletRed;
        static Color MidnightBlue;
        static Color MintCream;
        static Color MistyRose;
        static Color Moccasin;
        static Color NavajoWhite;
        static Color Navy;
        static Color OldLace;
        static Color Olive;
        static Color OliveDrab;
        static Color Orange;
        static Color OrangeRed;
        static Color Orchid;
        static Color PaleGoldenrod;
        static Color PaleGreen;
        static Color PaleTurquoise;
        static Color PaleVioletRed;
        static Color PapayaWhip;
        static Color PeachPuff;
        static Color Peru;
        static Color Pink;
        static Color Plum;
        static Color PowderBlue;
        static Color Purple;
        static Color Red;
        static Color RosyBrown;
        static Color RoyalBlue;
        static Color SaddleBrown;
        static Color Salmon;
        static Color SandyBrown;
        static Color SeaGreen;
        static Color SeaShell;
        static Color Sienna;
        static Color Silver;
        static Color SkyBlue;
        static Color SlateBlue;
        static Color SlateGray;
        static Color Snow;
        static Color SpringGreen;
        static Color SteelBlue;
        static Color Tan;
        static Color Teal;
        static Color Thistle;
        static Color Tomato;
        static Color Turquoise;
        static Color Violet;
        static Color Wheat;
        static Color White;
        static Color WhiteSmoke;
        static Color Yellow;
        static Color YellowGreen;
	};
}