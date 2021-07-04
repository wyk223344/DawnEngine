#include "PixelFormatExtensions.h"

using namespace DawnEngine;

PixelFormat PixelFormatExtensions::FindShaderResourceFormat(const PixelFormat format, bool isSRGB)
{
    if (isSRGB)
    {
        switch (format)
        {
        case PixelFormat::B8G8R8A8_Typeless:
            return PixelFormat::B8G8R8A8_UNorm_sRGB;
        case PixelFormat::R8G8B8A8_Typeless:
            return PixelFormat::R8G8B8A8_UNorm_sRGB;
        case PixelFormat::BC1_Typeless:
            return PixelFormat::BC1_UNorm_sRGB;
        case PixelFormat::BC2_Typeless:
            return PixelFormat::BC2_UNorm_sRGB;
        case PixelFormat::BC3_Typeless:
            return PixelFormat::BC3_UNorm_sRGB;
        case PixelFormat::BC7_Typeless:
            return PixelFormat::BC7_UNorm_sRGB;
        }
    }
    else
    {
        switch (format)
        {
        case PixelFormat::B8G8R8A8_Typeless:
            return PixelFormat::B8G8R8A8_UNorm;
        case PixelFormat::R8G8B8A8_Typeless:
            return PixelFormat::R8G8B8A8_UNorm;
        case PixelFormat::BC1_Typeless:
            return PixelFormat::BC1_UNorm;
        case PixelFormat::BC2_Typeless:
            return PixelFormat::BC2_UNorm;
        case PixelFormat::BC3_Typeless:
            return PixelFormat::BC3_UNorm;
        case PixelFormat::BC7_Typeless:
            return PixelFormat::BC7_UNorm;
        }
    }
    switch (format)
    {
    case PixelFormat::R24G8_Typeless:
        return PixelFormat::R24_UNorm_X8_Typeless;
    case PixelFormat::R32_Typeless:
        return PixelFormat::R32_Float;
    case PixelFormat::R16_Typeless:
        return PixelFormat::R16_UNorm;

    case PixelFormat::D16_UNorm:
        return PixelFormat::R16_UNorm;
    case PixelFormat::D24_UNorm_S8_UInt:
        return PixelFormat::R24_UNorm_X8_Typeless;
    case PixelFormat::D32_Float:
        return PixelFormat::R32_Float;
    case PixelFormat::D32_Float_S8X24_UInt:
        return PixelFormat::R32_Float_X8X24_Typeless;
    }
    return format;
}


PixelFormat PixelFormatExtensions::FindUnorderedAccessFormat(const PixelFormat format)
{
    switch (format)
    {
    case PixelFormat::B8G8R8A8_Typeless:
        return PixelFormat::B8G8R8A8_UNorm;
    case PixelFormat::R8G8B8A8_Typeless:
        return PixelFormat::R8G8B8A8_UNorm;
    }
    return format;
}

PixelFormat PixelFormatExtensions::FindDepthStencilFormat(const PixelFormat format)
{
    switch (format)
    {
    case PixelFormat::R24G8_Typeless:
    case PixelFormat::R24_UNorm_X8_Typeless:
        return PixelFormat::D24_UNorm_S8_UInt;
    case PixelFormat::R32_Typeless:
        return PixelFormat::D32_Float;
    case PixelFormat::R16_Typeless:
        return PixelFormat::D16_UNorm;
    }
    return format;
}