#include "Color.h"

using namespace DawnEngine;

#pragma region Ԥ����ɫ

Color Color::Transparent = Color(0, 0, 0, 0);
Color Color::AliceBlue = FromRGB(0xF0F8FF);
Color Color::AntiqueWhite = FromRGB(0xFAEBD7);
Color Color::Aqua = FromRGB(0x00FFFF);
Color Color::Aquamarine = FromRGB(0x7FFFD4);
Color Color::Azure = FromRGB(0xF0FFFF);
Color Color::Beige = FromRGB(0xF5F5DC);
Color Color::Bisque = FromRGB(0xFFE4C4);
Color Color::Black = FromRGB(0x000000);
Color Color::BlanchedAlmond = FromRGB(0xFFEBCD);
Color Color::Blue = FromRGB(0x0000FF);
Color Color::BlueViolet = FromRGB(0x8A2BE2);
Color Color::Brown = FromRGB(0xA52A2A);
Color Color::BurlyWood = FromRGB(0xDEB887);
Color Color::CadetBlue = FromRGB(0x5F9EA0);
Color Color::Chartreuse = FromRGB(0x7FFF00);
Color Color::Chocolate = FromRGB(0xD2691E);
Color Color::Coral = FromRGB(0xFF7F50);
Color Color::CornflowerBlue = FromRGB(0x6495ED);
Color Color::Cornsilk = FromRGB(0xFFF8DC);
Color Color::Crimson = FromRGB(0xDC143C);
Color Color::Cyan = FromRGB(0x00FFFF);
Color Color::DarkBlue = FromRGB(0x00008B);
Color Color::DarkCyan = FromRGB(0x008B8B);
Color Color::DarkGoldenrod = FromRGB(0xB8860B);
Color Color::DarkGray = FromRGB(0xA9A9A9);
Color Color::DarkGreen = FromRGB(0x006400);
Color Color::DarkKhaki = FromRGB(0xBDB76B);
Color Color::DarkMagenta = FromRGB(0x8B008B);
Color Color::DarkOliveGreen = FromRGB(0x556B2F);
Color Color::DarkOrange = FromRGB(0xFF8C00);
Color Color::DarkOrchid = FromRGB(0x9932CC);
Color Color::DarkRed = FromRGB(0x8B0000);
Color Color::DarkSalmon = FromRGB(0xE9967A);
Color Color::DarkSeaGreen = FromRGB(0x8FBC8F);
Color Color::DarkSlateBlue = FromRGB(0x483D8B);
Color Color::DarkSlateGray = FromRGB(0x2F4F4F);
Color Color::DarkTurquoise = FromRGB(0x00CED1);
Color Color::DarkViolet = FromRGB(0x9400D3);
Color Color::DeepPink = FromRGB(0xFF1493);
Color Color::DeepSkyBlue = FromRGB(0x00BFFF);
Color Color::DimGray = FromRGB(0x696969);
Color Color::DodgerBlue = FromRGB(0x1E90FF);
Color Color::Firebrick = FromRGB(0xB22222);
Color Color::FloralWhite = FromRGB(0xFFFAF0);
Color Color::ForestGreen = FromRGB(0x228B22);
Color Color::Fuchsia = FromRGB(0xFF00FF);
Color Color::Gainsboro = FromRGB(0xDCDCDC);
Color Color::GhostWhite = FromRGB(0xF8F8FF);
Color Color::Gold = FromRGB(0xFFD700);
Color Color::Goldenrod = FromRGB(0xDAA520);
Color Color::Gray = FromRGB(0x808080);
Color Color::Green = FromRGB(0x008000);
Color Color::GreenYellow = FromRGB(0xADFF2F);
Color Color::Honeydew = FromRGB(0xF0FFF0);
Color Color::HotPink = FromRGB(0xFF69B4);
Color Color::IndianRed = FromRGB(0xCD5C5C);
Color Color::Indigo = FromRGB(0x4B0082);
Color Color::Ivory = FromRGB(0xFFFFF0);
Color Color::Khaki = FromRGB(0xF0E68C);
Color Color::Lavender = FromRGB(0xE6E6FA);
Color Color::LavenderBlush = FromRGB(0xFFF0F5);
Color Color::LawnGreen = FromRGB(0x7CFC00);
Color Color::LemonChiffon = FromRGB(0xFFFACD);
Color Color::LightBlue = FromRGB(0xADD8E6);
Color Color::LightCoral = FromRGB(0xF08080);
Color Color::LightCyan = FromRGB(0xE0FFFF);
Color Color::LightGoldenrodYellow = FromRGB(0xFAFAD2);
Color Color::LightGreen = FromRGB(0x90EE90);
Color Color::LightGray = FromRGB(0xD3D3D3);
Color Color::LightPink = FromRGB(0xFFB6C1);
Color Color::LightSalmon = FromRGB(0xFFA07A);
Color Color::LightSeaGreen = FromRGB(0x20B2AA);
Color Color::LightSkyBlue = FromRGB(0x87CEFA);
Color Color::LightSlateGray = FromRGB(0x778899);
Color Color::LightSteelBlue = FromRGB(0xB0C4DE);
Color Color::LightYellow = FromRGB(0xFFFFE0);
Color Color::Lime = FromRGB(0x00FF00);
Color Color::LimeGreen = FromRGB(0x32CD32);
Color Color::Linen = FromRGB(0xFAF0E6);
Color Color::Magenta = FromRGB(0xFF00FF);
Color Color::Maroon = FromRGB(0x800000);
Color Color::MediumAquamarine = FromRGB(0x66CDAA);
Color Color::MediumBlue = FromRGB(0x0000CD);
Color Color::MediumOrchid = FromRGB(0xBA55D3);
Color Color::MediumPurple = FromRGB(0x9370DB);
Color Color::MediumSeaGreen = FromRGB(0x3CB371);
Color Color::MediumSlateBlue = FromRGB(0x7B68EE);
Color Color::MediumSpringGreen = FromRGB(0x00FA9A);
Color Color::MediumTurquoise = FromRGB(0x48D1CC);
Color Color::MediumVioletRed = FromRGB(0xC71585);
Color Color::MidnightBlue = FromRGB(0x191970);
Color Color::MintCream = FromRGB(0xF5FFFA);
Color Color::MistyRose = FromRGB(0xFFE4E1);
Color Color::Moccasin = FromRGB(0xFFE4B5);
Color Color::NavajoWhite = FromRGB(0xFFDEAD);
Color Color::Navy = FromRGB(0x000080);
Color Color::OldLace = FromRGB(0xFDF5E6);
Color Color::Olive = FromRGB(0x808000);
Color Color::OliveDrab = FromRGB(0x6B8E23);
Color Color::Orange = FromRGB(0xFFA500);
Color Color::OrangeRed = FromRGB(0xFF4500);
Color Color::Orchid = FromRGB(0xDA70D6);
Color Color::PaleGoldenrod = FromRGB(0xEEE8AA);
Color Color::PaleGreen = FromRGB(0x98FB98);
Color Color::PaleTurquoise = FromRGB(0xAFEEEE);
Color Color::PaleVioletRed = FromRGB(0xDB7093);
Color Color::PapayaWhip = FromRGB(0xFFEFD5);
Color Color::PeachPuff = FromRGB(0xFFDAB9);
Color Color::Peru = FromRGB(0xCD853F);
Color Color::Pink = FromRGB(0xFFC0CB);
Color Color::Plum = FromRGB(0xDDA0DD);
Color Color::PowderBlue = FromRGB(0xB0E0E6);
Color Color::Purple = FromRGB(0x800080);
Color Color::Red = FromRGB(0xFF0000);
Color Color::RosyBrown = FromRGB(0xBC8F8F);
Color Color::RoyalBlue = FromRGB(0x4169E1);
Color Color::SaddleBrown = FromRGB(0x8B4513);
Color Color::Salmon = FromRGB(0xFA8072);
Color Color::SandyBrown = FromRGB(0xF4A460);
Color Color::SeaGreen = FromRGB(0x2E8B57);
Color Color::SeaShell = FromRGB(0xFFF5EE);
Color Color::Sienna = FromRGB(0xA0522D);
Color Color::Silver = FromRGB(0xC0C0C0);
Color Color::SkyBlue = FromRGB(0x87CEEB);
Color Color::SlateBlue = FromRGB(0x6A5ACD);
Color Color::SlateGray = FromRGB(0x708090);
Color Color::Snow = FromRGB(0xFFFAFA);
Color Color::SpringGreen = FromRGB(0x00FF7F);
Color Color::SteelBlue = FromRGB(0x4682B4);
Color Color::Tan = FromRGB(0xD2B48C);
Color Color::Teal = FromRGB(0x008080);
Color Color::Thistle = FromRGB(0xD8BFD8);
Color Color::Tomato = FromRGB(0xFF6347);
Color Color::Turquoise = FromRGB(0x40E0D0);
Color Color::Violet = FromRGB(0xEE82EE);
Color Color::Wheat = FromRGB(0xF5DEB3);
Color Color::White = FromRGB(0xFFFFFF);
Color Color::WhiteSmoke = FromRGB(0xF5F5F5);
Color Color::Yellow = FromRGB(0xFFFF00);
Color Color::YellowGreen = FromRGB(0x9ACD32);


#pragma endregion


uint32 Color::ToRGBA() const
{
    // return 0xFFFFFFFF;
    return (static_cast<uint32>(R * 255)) +
        (static_cast<uint32>(G * 255) << 8) +
        (static_cast<uint32>(B * 255) << 16) +
        (static_cast<uint32>(A * 255) << 24);
}


uint32 Color::GetHashCode() const
{
    const int32 range = 100000;
    int32 hashCode = (int32)R * range;
    hashCode = hashCode * 397 ^ (int32)(G * range);
    hashCode = hashCode * 397 ^ (int32)(B * range);
    hashCode = hashCode * 397 ^ (int32)(A * range);
    return hashCode;
}