#pragma once

#include "Engine/Core/Include.h"
#include "Engine/Graphics/Enums.h"
#include "Engine/Graphics/PixelFormat.h"


namespace DawnEngine
{
	enum class GPUTextureFlags
	{
        None = 0x0000,

        ShaderResource = 0x0001,

        RenderTarget = 0x0002,

        UnorderedAccess = 0x0004,

        DepthStencil = 0x0008,

        PerMipViews = 0x0010,

        PerSliceViews = 0x0020,

        ReadOnlyDepthView = 0x0040,

        BackBuffer = 0x0080,
	};

    DECLARE_ENUM_OPERATORS(GPUTextureFlags);

    enum class TextureDimensions
    {
        // The texture (2d).
        Texture,

        // The volume texture (3d texture).
        VolumeTexture,

        // The cube texture (2d texture array of 6 items).
        CubeTexture,
    };

    struct GPUTextureDescription
    {
        // The dimensions of the texture.
        TextureDimensions Dimensions;

        // Texture width (in texels).
        int32 Width;

        // Texture height (in texels).
        int32 Height;

        // Texture depth (in texels) for Volume Textures.
        int32 Depth;

        // Number of textures in array for Texture Arrays.
        int32 ArraySize;

        // The maximum number of mipmap levels in the texture. Use 1 for a multisampled texture; or 0 to generate a full set of subtextures.
        int32 MipLevels;

        // Texture format.
        PixelFormat Format;

        // Structure that specifies multisampling parameters for the texture.
        MSAALevel MultiSampleLevel;

        // Flags for binding to pipeline stages. The flags can be combined by a logical OR.
        GPUTextureFlags Flags;

        // Default clear color for render targets
        Color DefaultClearColor;

    public:

        bool IsRenderTarget() const { return (Flags & GPUTextureFlags::RenderTarget) != 0; }

        bool IsDepthStencil() const { return (Flags & GPUTextureFlags::DepthStencil) != 0; }

        bool IsShaderResource() const { return (Flags & GPUTextureFlags::ShaderResource) != 0; }

        bool IsUnorderedAccess() const { return (Flags & GPUTextureFlags::UnorderedAccess) != 0; }

        bool IsVolume() const { return Dimensions == TextureDimensions::VolumeTexture; }

        bool IsCubeMap() const { return Dimensions == TextureDimensions::CubeTexture; }

        bool IsMultiSample() const { return MultiSampleLevel > MSAALevel::None; }

        bool IsRegularTexture() const { return Flags == GPUTextureFlags::ShaderResource; }

    public:

        void Clear();

    public:

        static GPUTextureDescription New2D(int32 width, int32 height, PixelFormat format, GPUTextureFlags textureFlags = GPUTextureFlags::ShaderResource)
        {
            return New2D(width, height, format, textureFlags, 1, 1);
        }

        static GPUTextureDescription New2D(int32 width, int32 height, PixelFormat format, GPUTextureFlags textureFlags, int32 mipCount, int32 arraySize, MSAALevel msaaLevel = MSAALevel::None);
    
        static GPUTextureDescription NewCube(int32 size, PixelFormat format, GPUTextureFlags textureFlags = GPUTextureFlags::ShaderResource)
        {
            return NewCube(size, format, textureFlags, 1);
        }

        static GPUTextureDescription NewCube(int32 size, PixelFormat format, GPUTextureFlags textureFlags, int32 mipCount);
    };
}